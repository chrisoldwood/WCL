/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PATH.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPath class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <stdlib.h>
#include <io.h>
#include <direct.h>
#include <commdlg.h>
#include <shlobj.h>

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

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

CPath::CPath(const char* pszPath)
{
	ASSERT(pszPath != NULL);

	Copy(pszPath);
}

CPath::CPath(const CString& strSrc)
{
	Copy(strSrc);
}

CPath::CPath(const char* pszDir, const char* pszFile)
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
	return (_access(m_pszData, 0) == 0);
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
	return (_access(m_pszData, 02) != 0);
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
	struct stat oInfo = { 0 };

	int nResult = ::stat(m_pszData, &oInfo);

	ASSERT(nResult == 0);

	return ((nResult == 0) && (oInfo.st_mode & _S_IFDIR));
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
	char szPath[MAX_PATH];

	::GetCurrentDirectory(sizeof(szPath), szPath);

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
	char szPath[MAX_PATH];

	// Get full executable path name.
	::GetModuleFileName(hModule, szPath, sizeof(szPath));
	
	// Strip file name.
	char* pszExeName = strrchr(szPath, '\\');
	*pszExeName = '\0';

	return CPath(szPath);
}

CPath CPath::WindowsDir()
{
	char szPath[MAX_PATH];

	::GetWindowsDirectory(szPath, sizeof(szPath));

	return CPath(szPath);
}

CPath CPath::SystemDir()
{
	char szPath[MAX_PATH];

	::GetSystemDirectory(szPath, sizeof(szPath));

	return CPath(szPath);
}

CPath CPath::TempDir()
{
	char szPath[MAX_PATH];

	::GetTempPath(sizeof(szPath), szPath);
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
	char szPath[MAX_PATH];

	// Get full executable path name.
	::GetModuleFileName(hModule, szPath, sizeof(szPath));
	
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

CPath CPath::SpecialDir(int nCSIDL)
{
	char szPath[MAX_PATH] = "";

	::SHGetSpecialFolderPath(NULL, szPath, nCSIDL, FALSE);

	CPath str = szPath;

	// "Program Files" folder is only available with IE 5.x and later.
	if ( (nCSIDL == CSIDL_PROGRAM_FILES) && (str == "") )
		str = CPath::WindowsDir().Root() / "Program Files";

	return str;
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
	char szDrive[MAX_PATH];

	_splitpath(m_pszData, szDrive, NULL, NULL, NULL);

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
	char  szDrive[MAX_PATH];
	char  szDirectory[MAX_PATH];
	CPath strRoot;

	_splitpath(m_pszData, szDrive, szDirectory, NULL, NULL);

	// Has a drive specifier?
	if (strlen(szDrive) > 0)
	{
		strRoot = szDrive;

		if (strRoot.Find('\\') == -1)
			strRoot += '\\';
	}
	// Counld be a UNC share? ("\\m\d" is minimum).
	else if (strlen(szDirectory) >= 5)
	{
		char* psz = szDirectory;

		// Must begin with "\\"
		if ( (psz[0] == '\\') && (psz[1] == '\\') )
		{
			psz += 2;

			// Skip the machine name.
			while ( (*psz != '\0') && (*psz != '\\') )
				++psz;

			if (*psz == '\\')
			{
				psz += 1;

				// Skip the share name.
				while ( (*psz != '\0') && (*psz != '\\') )
					++psz;

				*psz = '\0';

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
	char szDrive[MAX_PATH];
	char szDir[MAX_PATH];

	_splitpath(m_pszData, szDrive, szDir, NULL, NULL);

	strcat(szDrive, szDir);
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
	char szFileName[MAX_PATH];
	char szExt[MAX_PATH];

	_splitpath(m_pszData, NULL, NULL, szFileName, szExt);

	strcat(szFileName, szExt);

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
	char szFileName[MAX_PATH];

	_splitpath(m_pszData, NULL, NULL, szFileName, NULL);

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
	char szExt[MAX_PATH];

	_splitpath(m_pszData, NULL, NULL, NULL, szExt);

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

bool CPath::Select(const CWnd& rParent, DlgMode eMode, const char* pszExts,
					const char* pszDefExt, const char* pszDir)
{
	bool 			bOkay;
	OPENFILENAME	ofnFile = { 0 };
	char			szFileName[MAX_PATH];

	// Initialise filename.
	szFileName[0] = '\0';

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
		ofnFile.lpstrTitle = "Select";
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

bool CPath::SelectDir(const CWnd& rParent, const char* pszTitle, const char* pszDir)
{
	BROWSEINFO   oInfo;
	char         szDir[MAX_PATH];
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
	oInfo.lParam    = (LPARAM)pszDir;

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
			char szDir[MAX_PATH];

			if (::SHGetPathFromIDList((LPITEMIDLIST) lParam, szDir))
				::SendMessage(hWnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)szDir);
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

bool CPath::SelectComputer(const CWnd& rParent, const char* pszTitle)
{
	BROWSEINFO   oInfo = { 0 };
	char         szComputer[MAX_PATH];
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

inline bool IsPathSeparator(char cChar)
{
	return ((cChar == '\\') || (cChar == '/'));
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

void CPath::Normalise(char* pszPath)
{
	ASSERT(pszPath != NULL);

	int nLength = strlen(pszPath);

	// "\" or "/" is a valid root. 
	if (nLength > 1)
	{
		char* pszEnd = pszPath+nLength-1;

		// "C:\" is a valid root.
		if (IsPathSeparator(*pszEnd) && (*(pszEnd-1) != ':'))
			*pszEnd = '\0';
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

bool CPath::SelectFiles(const CWnd& rParent, const char* pszExts, const char* pszDefExt, CStrArray& astrFiles)
{
	return SelectFiles(rParent, pszExts, pszDefExt, NULL, astrFiles);
}

bool CPath::SelectFiles(const CWnd& rParent, const char* pszExts, const char* pszDefExt, const char* pszDir, CStrArray& astrFiles)
{
	OPENFILENAME ofnFile = { 0 };
	char         szFileName[MAX_PATH*100] = "";

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
	ofnFile.lpstrTitle        = "Select";
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
	if (_access(szFileName, 0) != 0)
		return false;

	struct stat oInfo = { 0 };

	// Get the returned paths type.
	if (::stat(szFileName, &oInfo) != 0)
		return false;

	// Multiple files?
	if ((oInfo.st_mode & _S_IFDIR))
	{
		// First path is the directory.
		const char* pszDir = szFileName;

		// Convert filename list to full paths.
		// NB: Files are separated by '\0' and the list is terminated by a "\0\0".
		const char *pszFileName = pszDir + strlen(pszDir) + 1;

		while (*pszFileName != 0)
		{ 
			astrFiles.Add(CPath(pszDir, pszFileName));

			pszFileName += strlen(pszFileName) + 1;
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

void CPath::operator/=(const char* pszPath)
{
	ASSERT(pszPath != NULL);

	// Check RHS path for leading separator.
	if ((*pszPath != '\\') && (*pszPath != '/'))
	{
		int nLength = Length();

		// Check LHS path for trailing separator.
		if ( (nLength > 0) && (m_pszData[nLength-1] != '\\') )
			operator +=('\\');
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
	if (Find('%') != -1)
	{
		Replace("%ProgramFiles%", CPath::SpecialDir(CSIDL_PROGRAM_FILES));
		Replace("%SystemRoot%",   CPath::WindowsDir());
		Replace("%Temp%",         CPath::TempDir());
	}
}
