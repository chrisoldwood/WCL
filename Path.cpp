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

/******************************************************************************
** Method:		Constructor
**
** Description:	Default constructor. Initialise base class.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPath::CPath()
{
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
** Method:		Directory()
**
** Description:	Get the directory from the full path. This assumes that the
**				last part of the path name specifies a file and as such only
**				copies the path up to the last entry.
**
** Parameters:	None.
**
** Returns:		The directory as a path.
**
*******************************************************************************
*/

CPath CPath::Directory() const
{
	char szDir[MAX_PATH];

	_splitpath(m_pszData, NULL, szDir, NULL, NULL);

	return CPath(szDir);
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
** Parameters:	pParent		The dialogs parent.
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
	OPENFILENAME	ofnFile;
	char			szFileName[MAX_PATH];

	// Initialise filename.
	szFileName[0] = '\0';

    // Fill in structure.
	ofnFile.lStructSize       = sizeof(OPENFILENAME);
	ofnFile.hwndOwner         = rParent.Handle();
	ofnFile.hInstance         = NULL;
	ofnFile.lpstrFilter       = pszExts;
	ofnFile.lpstrCustomFilter = NULL;
	ofnFile.nMaxCustFilter    = NULL;
	ofnFile.nFilterIndex      = NULL;
	ofnFile.lpstrFile         = szFileName;
	ofnFile.nMaxFile          = MAX_PATH;
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
** Parameters:	pParent		The dialogs parent.
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
** Parameters:	pParent		The dialogs parent.
**				pszTitle	The hint displayed above the view.
**
** Returns:		true		If user pressed OK.
**				false		If user pressed Cancel.
**
*******************************************************************************
*/

bool CPath::SelectComputer(const CWnd& rParent, const char* pszTitle)
{
	BROWSEINFO   oInfo;
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
	memset(&oInfo, 0, sizeof(oInfo));
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
