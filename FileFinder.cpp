/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FILEFINDER.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CFileFinder class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFileFinder::CFileFinder()
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFileFinder::~CFileFinder()
{
}

/******************************************************************************
** Method:		Find.
**
** Description:	Find all files in the path matching the mask.
**
** Parameters:	pszPath		The root path to search.
**				pszMask		The file mask.
**				bRecurse	Recurse into subdirectories flag.
**				oTree		The file tree to fill in.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFileFinder::Find(const char* pszPath, const char* pszMask, bool bRecurse, CFileTree& oTree)
{
	ASSERT(pszPath != NULL);
	ASSERT(pszMask != NULL);

	// Clear the existing tree.
	oTree.Clear();

	// Allocate the root node.
	CFileTreeNode* pRoot = new CFileTreeNode();

	// Initialise the node and tree.
	pRoot->m_oData.m_strPath = pszPath;
	oTree.Root(pRoot);

	// Enumerate start directory.
	Find(*pRoot, pszMask, bRecurse);
}

/******************************************************************************
** Method:		Find.
**
** Description:	Find all files in the path of the given directory node.
**
** Parameters:	oNode		The directory node to search.
**				pszMask		The file mask.
**				bRecurse	Recurse into subdirectories flag.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFileFinder::Find(CFileTreeNode& oNode, const char* pszMask, bool bRecurse)
{
	HANDLE			hFind;
	WIN32_FIND_DATA	oInfo;
	CPath			strFind = oNode.m_oData.m_strPath + pszMask;

	// Find the files...
	hFind = ::FindFirstFile(strFind, &oInfo);

	// At least 1 file found?
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// Is a directory?
			if (oInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				oNode.m_oData.m_astrDirs.Add(oInfo.cFileName);
			else
				oNode.m_oData.m_astrFiles.Add(oInfo.cFileName);
		}
		while (::FindNextFile(hFind, &oInfo));

		// Cleanup.
		::FindClose(hFind);
	}

	// Recurse into subdirectories?
	if (bRecurse)
	{
		ASSERT(false);
	}
}
