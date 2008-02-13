/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MRULIST.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMRUList class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "MRUList.hpp"
#include "Menu.hpp"
#include "IniFile.hpp"

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

CMRUList::CMRUList(size_t nMaxSize)
	: m_nMaxSize(nMaxSize)
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

CMRUList::~CMRUList()
{
}

/******************************************************************************
** Method:		Add()
**
** Description:	Adds a new path to the top of the MRU list, or moves an
**				existing path up to the top of the list.
**
** Parameters:	pszPath		The path to add.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMRUList::Add(const tchar* pszPath)
{
	// See if the path exists already.
	int iOldPos = m_Paths.Find(pszPath, true);

	// Already at the top?
	if (iOldPos == 0)
		return;

	// Remove the path, if lower down.
	if (iOldPos != -1)
		m_Paths.Delete(iOldPos);

	// Insert the path at the top.
	m_Paths.Insert(0, pszPath);

	// Trim list, if required.
	if (m_Paths.Size() > m_nMaxSize)
		m_Paths.Delete(m_nMaxSize);
}

/******************************************************************************
** Method:		UpdateMenu()
**
** Description:	Updates the menu with the current MRU list.
**
** Parameters:	rMenu		The menu to update.
**				iCmdBase	The base ID of the commands used for the MRU list.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMRUList::UpdateMenu(CMenu& rMenu, uint iCmdBase)
{
	// For all MRU items.
	for (size_t i = 0; i < m_nMaxSize; ++i)
	{
		CString strText;
		bool	bEnable = false;

		// Create item number.
		strText.Format(TXT("&%d "), i+1);

		// Valid path for this item?
		if ( (i < m_Paths.Size()) && (m_Paths[i] != TXT("")) )
		{
			strText += m_Paths[i];
			bEnable  = true;
		}

		// Modify menu.
		rMenu.SetCmdText(iCmdBase, strText);
		rMenu.EnableCmd(iCmdBase, bEnable);

		++iCmdBase;
	}
}

/******************************************************************************
** Methods:		Load()
**				Save()
**
** Description:	Loads/Saves the MRU list from/to the given .ini file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMRUList::Load(CIniFile& rCfgFile, const tchar* pszSection)
{
	ASSERT(pszSection != NULL);

	// For all MRU items.
	for (size_t i = 0; i < m_nMaxSize; ++i)
	{
		CString strEntry, strValue;

		// Create section entry name and read value.
		strEntry.Format(TXT("%d"), i+1);
		strValue = rCfgFile.ReadString(pszSection, strEntry, TXT(""));

		// Valid path?
		if (strValue != TXT(""))
			m_Paths.Add(strValue);
	}
}

void CMRUList::Save(CIniFile& rCfgFile, const tchar* pszSection)
{
	ASSERT(pszSection != NULL);

	// For all MRU items.
	for (size_t i = 0; i < m_nMaxSize; ++i)
	{
		CString strEntry;

		// Create section entry name.
		strEntry.Format(TXT("%d"), i+1);

		// Valid path for this item?
		if ( (i < m_Paths.Size()) && (m_Paths[i] != TXT("")) )
			rCfgFile.WriteString(pszSection, strEntry, m_Paths[i]);
	}
}
