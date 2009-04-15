/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PATH.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPath class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Path.hpp"
#include <stdlib.h>
#include <io.h>
#include <direct.h>
#include <commdlg.h>
#include <shlobj.h>
#include "Module.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include "Wnd.hpp"
#include "StrArray.hpp"
#include <tchar.h>
#include "Win32Exception.hpp"

// Directive to link to the Shell library.
#pragma comment(lib, "shell32")
// Directive to link to the Common Dialog library.
#pragma comment(lib, "comdlg32")

/******************************************************************************
** Method:		Constructors
**
** Description:	.
**
** Parameters:	Various.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPath::CPath()
{
}

CPath::CPath(const tchar* pszPath)
{
	ASSERT(pszPath != NULL);

	Copy(pszPath);
}

CPath::CPath(const CString& strSrc)
{
	Copy(strSrc);
}

CPath::CPath(const tchar* pszDir, const tchar* pszFile)
{
	ASSERT(pszDir  != NULL);
	ASSERT(pszFile != NULL);

	Copy(pszDir);
	operator /=(pszFile);
}

/******************************************************************************
** Method:		Exists()
**
** Description:	Determine if the path to a file or directory actually exists.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPath::Exists() const
{
	return (_taccess(m_pszData, 0) == 0);
}

/******************************************************************************
** Method:		ReadOnly()
**
** Description:	Determine if a file or directory is read-only.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPath::ReadOnly() const
{
	return (_taccess(m_pszData, 02) != 0);
}

/******************************************************************************
** Method:		IsFolder()
**
** Description:	Determine if a file or directory is a directory.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPath::IsFolder() const
{
	struct _stat oInfo = { 0 };

	int nResult = ::_tstat(m_pszData, &oInfo);

	ASSERT(nResult == 0);

	return ((nResult == 0) && (oInfo.st_mode & _S_IFDIR));
}

////////////////////////////////////////////////////////////////////////////////
//! Get the attributes for the path.

DWORD CPath::Attributes() const
{
	DWORD attributes = INVALID_FILE_ATTRIBUTES;

	if ((attributes = ::GetFileAttributes(m_pszData)) == INVALID_FILE_ATTRIBUTES)
		throw WCL::Win32Exception(::GetLastError(), Core::Fmt(TXT("Failed to query the file attributes for:-\n\n"), m_pszData));

	return attributes;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the attributes for the path.

void CPath::SetAttributes(DWORD attributes)
{
	if (::SetFileAttributes(m_pszData, attributes) == 0)
		throw WCL::Win32Exception(::GetLastError(), Core::Fmt(TXT("Failed to set the file attributes on:-\n\n"), m_pszData));
}

/******************************************************************************
** Method:		CurrentDir()
**				ApplicationDir()
**				ModuleDir()
**				WindowsDir()
**				SystemDir()
**				TempDir()
**
** Description:	Retrieves one of the standard paths.
**
** Parameters:	None.
**
** Returns:		The path.
**
*******************************************************************************
*/

CPath CPath::CurrentDir()
{
	tchar szPath[MAX_PATH+1] = { 0 };

	::GetCurrentDirectory(MAX_PATH+1, szPath);

	return CPath(szPath);
}

CPath CPath::ApplicationDir()
{
	return ModuleDir(NULL);
}

CPath CPath::ModuleDir()
{
	ASSERT(CModule::This().Handle() != NULL);

	return ModuleDir(CModule::This().Handle());
}

CPath CPath::ModuleDir(HMODULE hModule)
{
	tchar szPath[MAX_PATH+1] = { 0 };

	// Get full executable path name.
	::GetModuleFileName(hModule, szPath, MAX_PATH+1);
	
	// Strip file name.
	tchar* pszExeName = tstrrchr(szPath, TXT('\\'));

	if (pszExeName != nullptr)
		*pszExeName = TXT('\0');

	return CPath(szPath);
}

CPath CPath::WindowsDir()
{
	tchar szPath[MAX_PATH+1] = { 0 };

	::GetWindowsDirectory(szPath, MAX_PATH+1);

	return CPath(szPath);
}

CPath CPath::SystemDir()
{
	tchar szPath[MAX_PATH+1] = { 0 };

	::GetSystemDirectory(szPath, MAX_PATH+1);

	return CPath(szPath);
}

CPath CPath::TempDir()
{
	tchar szPath[MAX_PATH+1] = { 0 };

	::GetTempPath(MAX_PATH+1, szPath);
	Normalise(szPath);

	return CPath(szPath);
}

CPath CPath::Application()
{
	return Module(NULL);
}

CPath CPath::Module()
{
	ASSERT(CModule::This().Handle() != NULL);

	return Module(CModule::This().Handle());
}

CPath CPath::Module(HMODULE hModule)
{
	tchar szPath[MAX_PATH+1] = { 0 };

	// Get full executable path name.
	::GetModuleFileName(hModule, szPath, MAX_PATH+1);
	
	return CPath(szPath);
}

/******************************************************************************
** Method:		SpecialDir()
**
** Description:	Gets a path of a Special Folder indetified by its CSIDL.
**
** Parameters:	nCSIDL	The CSIDL of the folder (See SHGetSpecialFolderPath).
**
** Returns:		The directory as a path.
**
*******************************************************************************
*/

CPath CPath::SpecialDir(int csidl)
{
	tchar buffer[MAX_PATH+1] = { 0 };

	// Lookup the folder.
	BOOL result = ::SHGetSpecialFolderPath(NULL, buffer, csidl, FALSE);

	if (result)
		return buffer;

	// Try and simulate it.
	CPath path;

	// "Program Files" only available with IE 5.0 and later.
	if (csidl == CSIDL_PROGRAM_FILES)
	{
		path = WindowsDir().Root() / TXT("Program Files");
	}
	// "Application Data" only available with IE 4.0 and later.
	else if (csidl == CSIDL_APPDATA)
	{
		path = ApplicationDir();
	}

	return path;
}

/******************************************************************************
** Method:		Drive()
**
** Description:	Get the drive portion of the full path.
**
** Parameters:	None.
**
** Returns:		The drive as a path.
**
*******************************************************************************
*/

CString CPath::Drive() const
{
	tchar szDrive[MAX_PATH+1] = { 0 };

	_tsplitpath(m_pszData, szDrive, NULL, NULL, NULL);

	return CString(szDrive);
}

/******************************************************************************
** Method:		Root()
**
** Description:	Get the root of the path. Unlike Drive() which returns the
**				drive letter, this returns a valid path and handles UNCs.
**
** Parameters:	None.
**
** Returns:		The drive as a path.
**
*******************************************************************************
*/

CPath CPath::Root() const
{
	tchar szDrive[MAX_PATH+1] = { 0 };
	tchar szDirectory[MAX_PATH+1] = { 0 };
	CPath strRoot;

	_tsplitpath(m_pszData, szDrive, szDirectory, NULL, NULL);

	// Has a drive specifier?
	if (tstrlen(szDrive) > 0)
	{
		strRoot = szDrive;

		if (strRoot.Find(TXT('\\')) == -1)
			strRoot += TXT('\\');
	}
	// Counld be a UNC share? ("\\m\d" is minimum).
	else if (tstrlen(szDirectory) >= 5)
	{
		tchar* psz = szDirectory;

		// Must begin with "\\"
		if ( (psz[0] == TXT('\\')) && (psz[1] == TXT('\\')) )
		{
			psz += 2;

			// Skip the machine name.
			while ( (*psz != TXT('\0')) && (*psz != TXT('\\')) )
				++psz;

			if (*psz == TXT('\\'))
			{
				psz += 1;

				// Skip the share name.
				while ( (*psz != TXT('\0')) && (*psz != TXT('\\')) )
					++psz;

				*psz = TXT('\0');

				strRoot = szDirectory;
			}

		}
	}

	return strRoot;
}

/******************************************************************************
** Method:		Directory()
**
** Description:	Get the directory from the full path. If the path specifies a
**				a path to a file, it returns the files directory. If the path
**				is to a folder, it returns the parent folder.
**
** Parameters:	None.
**
** Returns:		The directory as a path.
**
*******************************************************************************
*/

CPath CPath::Directory() const
{
	tchar szDrive[MAX_PATH+1] = { 0 };
	tchar szDir[MAX_PATH+1] = { 0 };

	_tsplitpath(m_pszData, szDrive, szDir, NULL, NULL);

	tstrcat(szDrive, szDir);
	Normalise(szDrive);

	return CPath(szDrive);
}

/******************************************************************************
** Method:		FileName()
**
** Description:	Get just the filename + extension from the path.
**
** Parameters:	None.
**
** Returns:		The filename.
**
*******************************************************************************
*/

CString CPath::FileName() const
{
	tchar szFileName[MAX_PATH+1] = { 0 };
	tchar szExt[MAX_PATH+1] = { 0 };

	_tsplitpath(m_pszData, NULL, NULL, szFileName, szExt);

	tstrcat(szFileName, szExt);

	return CString(szFileName);
}

/******************************************************************************
** Method:		FileTitle()
**
** Description:	Get just the filename without the path or extension.
**
** Parameters:	None.
**
** Returns:		The file title.
**
*******************************************************************************
*/

CString CPath::FileTitle() const
{
	tchar szFileName[MAX_PATH+1] = { 0 };

	_tsplitpath(m_pszData, NULL, NULL, szFileName, NULL);

	return CString(szFileName);
}

/******************************************************************************
** Method:		FileExt()
**
** Description:	Get just the file extension.
**
** Parameters:	None.
**
** Returns:		The extension.
**
*******************************************************************************
*/

CString CPath::FileExt() const
{
	tchar szExt[MAX_PATH+1] = { 0 };

	_tsplitpath(m_pszData, NULL, NULL, NULL, szExt);

	return CString(szExt);
}

/******************************************************************************
** Method:		Select()
**
** Description:	Get a filename by using the common file open dialog.
**
** Parameters:	rParent		The dialogs parent.
**				eMode		One of DlgMode values.
**				pszExts		File extensions.
**				pszDefExt	Default file extension.
**				pszDir		Initial directory.
**
** Returns:		true		If user pressed OK.
**				false		If user pressed Cancel.
**
*******************************************************************************
*/

bool CPath::Select(const CWnd& rParent, DlgMode eMode, const tchar* pszExts,
					const tchar* pszDefExt, const tchar* pszDir)
{
	bool 			bOkay;
	OPENFILENAME	ofnFile = { 0 };
	tchar			szFileName[MAX_PATH+1] = { 0 };

    // Fill in structure.
	ofnFile.lStructSize       = sizeof(ofnFile);
	ofnFile.hwndOwner         = rParent.Handle();
	ofnFile.hInstance         = NULL;
	ofnFile.lpstrFilter       = pszExts;
	ofnFile.lpstrCustomFilter = NULL;
	ofnFile.nMaxCustFilter    = NULL;
	ofnFile.nFilterIndex      = NULL;
	ofnFile.lpstrFile         = szFileName;
	ofnFile.nMaxFile          = sizeof(szFileName);
	ofnFile.lpstrFileTitle    = NULL;
	ofnFile.nMaxFileTitle     = NULL;
	ofnFile.lpstrInitialDir   = pszDir;
	ofnFile.lpstrTitle        = NULL;
	ofnFile.Flags             = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofnFile.nFileOffset       = NULL;
	ofnFile.nFileExtension    = NULL;
	ofnFile.lpstrDefExt       = pszDefExt;
	ofnFile.lCustData         = NULL;
	ofnFile.lpfnHook          = NULL;
	ofnFile.lpTemplateName    = NULL;
	
	// Get the filename.
	if (eMode == OpenFile)
	{
		ofnFile.Flags |= OFN_FILEMUSTEXIST;
		bOkay = GetOpenFileName(&ofnFile);
	}
	else if (eMode == SaveFile)
	{
		bOkay = GetSaveFileName(&ofnFile);
	}
	else // SelectFile
	{
		ofnFile.lpstrTitle = TXT("Select");
		bOkay = GetOpenFileName(&ofnFile);
	}
	
	// Error or cancel?
	if (!bOkay)
		return false;
		
	// Save filename.
	Copy(szFileName);
	
	return true;
}

/******************************************************************************
** Method:		SelectDir()
**
** Description:	Get a directory by using the common dialog.
**
** Parameters:	rParent		The dialogs parent.
**				pszTitle	The hint displayed above the view.
**				pszDir		The initial directory.
**
** Returns:		true		If user pressed OK.
**				false		If user pressed Cancel.
**
*******************************************************************************
*/

bool CPath::SelectDir(const CWnd& rParent, const tchar* pszTitle, const tchar* pszDir)
{
	BROWSEINFO   oInfo;
	tchar        szDir[MAX_PATH+1] = { 0 };
	LPITEMIDLIST pItemIDList;
	LPMALLOC     pMalloc;
	HRESULT      hResult;

	// Get shell memory allocator.
	hResult = ::SHGetMalloc(&pMalloc);

	ASSERT(SUCCEEDED(hResult));

	if (FAILED(hResult))
		return false;

	// Intialise info structure to browse for only folders.
	memset(&oInfo, 0, sizeof(oInfo));
	oInfo.hwndOwner = rParent.Handle();
	oInfo.lpszTitle = pszTitle;
	oInfo.ulFlags   = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	oInfo.lpfn      = BrowseCallbackProc;
	oInfo.lParam    = reinterpret_cast<LPARAM>(pszDir);

	// Prompt the user.
	pItemIDList = ::SHBrowseForFolder(&oInfo);

	if (pItemIDList != NULL)
	{
		// Convert the standard path.
		if (::SHGetPathFromIDList(pItemIDList, szDir))
			Copy(szDir);

		pMalloc->Free(pItemIDList);
	}

	// Cleanup.
	pMalloc->Release();
     
	return pItemIDList != NULL;
}

/******************************************************************************
** Method:		BrowseCallbackProc()
**
** Description:	Callback proc used by SelectDir to set the inital directory.
**
** Parameters:	See SHBrowseForFolder().
**
** Returns:		See SHBrowseForFolder().
**
*******************************************************************************
*/

int CALLBACK CPath::BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch(uMsg)
	{
		case BFFM_INITIALIZED:
		{
			// Set initial directory, if specified.
			if (lpData != NULL)
				::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);
		}
		break;

		case BFFM_SELCHANGED:
		{
			tchar szDir[MAX_PATH+1] = { 0 };

			if (::SHGetPathFromIDList(reinterpret_cast<LPITEMIDLIST>(lParam), szDir))
				::SendMessage(hWnd, BFFM_SETSTATUSTEXT, 0, reinterpret_cast<LPARAM>(szDir));
		}
		break;
	}

	return 0;
}

/******************************************************************************
** Method:		SelectComputer()
**
** Description:	Get a computer by using the common dialog.
**
** Parameters:	rParent		The dialogs parent.
**				pszTitle	The hint displayed above the view.
**
** Returns:		true		If user pressed OK.
**				false		If user pressed Cancel.
**
*******************************************************************************
*/

bool CPath::SelectComputer(const CWnd& rParent, const tchar* pszTitle)
{
	BROWSEINFO   oInfo = { 0 };
	tchar        szComputer[MAX_PATH+1] = { 0 };
	LPITEMIDLIST pItemIDList;
	LPMALLOC     pMalloc;
	HRESULT      hResult;

	// Get shell memory allocator.
	hResult = ::SHGetMalloc(&pMalloc);

	ASSERT(SUCCEEDED(hResult));

	if (FAILED(hResult))
		return false;

	// Intialise info structure to browse for only folders.
	oInfo.hwndOwner      = rParent.Handle();
	oInfo.pszDisplayName = szComputer;
	oInfo.lpszTitle      = pszTitle;
	oInfo.ulFlags        = BIF_BROWSEFORCOMPUTER;

	// Prompt the user.
	pItemIDList = ::SHBrowseForFolder(&oInfo);

	if (pItemIDList != NULL)
	{
		// Convert the standard path.
		Copy(szComputer);

		pMalloc->Free(pItemIDList);
	}

	// Cleanup.
	pMalloc->Release();
     
	return pItemIDList != NULL;
}

/******************************************************************************
** Method:		IsPathSeparator()
**
** Description:	Helper functions to check if a character is a path separator.
**
** Parameters:	cChar	The character to test..
**
** Returns:		true or false.
**
*******************************************************************************
*/

inline bool IsPathSeparator(tchar cChar)
{
	return ((cChar == TXT('\\')) || (cChar == TXT('/')));
}

/******************************************************************************
** Method:		Normalise()
**
** Description:	Normalises the path by removing the trailing path separator if
**				it exists and it's not the root folder.
**
** Parameters:	pszPath		The path to modify.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPath::Normalise(tchar* pszPath)
{
	ASSERT(pszPath != NULL);

	size_t nLength = tstrlen(pszPath);

	// "\" or "/" is a valid root. 
	if (nLength > 1)
	{
		tchar* pszEnd = pszPath+nLength-1;

		// "C:\" is a valid root.
		if (IsPathSeparator(*pszEnd) && (*(pszEnd-1) != TXT(':')))
			*pszEnd = TXT('\0');
	}
}

/******************************************************************************
** Method:		SelectFiles()
**
** Description:	Select multiple files using the common dialog.
**
** Parameters:	rParent		The dialogs parent.
**				pszExts		File extensions.
**				pszDefExt	Default file extension.
**				pszDir		Initial directory.
**				astrFiles	The return buffer for the filenames.
**
** Returns:		true		If user pressed OK.
**				false		If user pressed Cancel.
**
*******************************************************************************
*/

bool CPath::SelectFiles(const CWnd& rParent, const tchar* pszExts, const tchar* pszDefExt, CStrArray& astrFiles)
{
	return SelectFiles(rParent, pszExts, pszDefExt, NULL, astrFiles);
}

bool CPath::SelectFiles(const CWnd& rParent, const tchar* pszExts, const tchar* pszDefExt, const tchar* pszDir, CStrArray& astrFiles)
{
	OPENFILENAME ofnFile = { 0 };
	tchar        szFileName[MAX_PATH*100] = { 0 };

	// Initialise structure.
	ofnFile.lStructSize       = sizeof(ofnFile);
	ofnFile.hwndOwner         = rParent.Handle();
	ofnFile.hInstance         = NULL;
	ofnFile.lpstrFilter       = pszExts;
	ofnFile.lpstrCustomFilter = NULL;
	ofnFile.nMaxCustFilter    = NULL;
	ofnFile.nFilterIndex      = NULL;
	ofnFile.lpstrFile         = szFileName;
	ofnFile.nMaxFile          = sizeof(szFileName);
	ofnFile.lpstrFileTitle    = NULL;
	ofnFile.nMaxFileTitle     = NULL;
	ofnFile.lpstrInitialDir   = pszDir;
	ofnFile.lpstrTitle        = TXT("Select");
	ofnFile.Flags             = OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	ofnFile.nFileOffset       = NULL;
	ofnFile.nFileExtension    = NULL;
	ofnFile.lpstrDefExt       = pszDefExt;
	ofnFile.lCustData         = NULL;
	ofnFile.lpfnHook          = NULL;
	ofnFile.lpTemplateName    = NULL;
	
	if (!::GetOpenFileName(&ofnFile))
		return false;

	// Returned path must exist to check its type.
	if (_taccess(szFileName, 0) != 0)
		return false;

	struct _stat oInfo = { 0 };

	// Get the returned paths type.
	if (::_tstat(szFileName, &oInfo) != 0)
		return false;

	// Multiple files?
	if ((oInfo.st_mode & _S_IFDIR))
	{
		// First path is the directory.
		const tchar* pszDir = szFileName;

		// Convert filename list to full paths.
		// NB: Files are separated by '\0' and the list is terminated by a "\0\0".
		const tchar *pszFileName = pszDir + tstrlen(pszDir) + 1;

		while (*pszFileName != 0)
		{ 
			astrFiles.Add(CPath(pszDir, pszFileName));

			pszFileName += tstrlen(pszFileName) + 1;
		}
	}
	// Single file.
	else
	{
		astrFiles.Add(szFileName);
	}

	return true;
}

/******************************************************************************
** Method:		operator/=()
**
** Description:	Appends the string to the end of the path, adding a separator
**				if required.
**
** Parameters:	pszPath		The path to append.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPath::operator/=(const tchar* pszPath)
{
	ASSERT(pszPath != NULL);

	// Check RHS path for leading separator.
	if ((*pszPath != TXT('\\')) && (*pszPath != TXT('/')))
	{
		size_t nLength = Length();

		// Check LHS path for trailing separator.
		if ( (nLength > 0) && (m_pszData[nLength-1] != TXT('\\')) )
			operator +=(TXT('\\'));
	}

	operator +=(pszPath);
}

/******************************************************************************
** Method:		ExpandVars()
**
** Description:	Expands any path variables such as %ProgramFiles%, %SystemRoot%
**				and %Temp% into the actual path.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPath::ExpandVars()
{
	// Do a crude search and replace on all possible matches.
	if (Find(TXT('%')) != -1)
	{
		Replace(TXT("%ProgramFiles%"), CPath::SpecialDir(CSIDL_PROGRAM_FILES));
		Replace(TXT("%SystemRoot%"),   CPath::WindowsDir());
		Replace(TXT("%Temp%"),         CPath::TempDir());
	}
}
