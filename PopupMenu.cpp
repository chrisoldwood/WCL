/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		POPUPMENU.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPopupMenu class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"


/******************************************************************************
** Method:		Constructor
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPopupMenu::CPopupMenu()
	: m_hParent(NULL)
{
}

/******************************************************************************
** Method:		Constructor
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPopupMenu::CPopupMenu(HMENU hMenu)
	: CMenu(hMenu)
	, m_hParent(NULL)
{
}

/******************************************************************************
** Method:		Constructor
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPopupMenu::CPopupMenu(uint iRscID)
	: m_hParent(NULL)
{
	LoadRsc(iRscID);
}

/******************************************************************************
** Method:		Destructor
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPopupMenu::~CPopupMenu()
{
	if (m_hParent != NULL)
		::DestroyMenu(m_hParent);
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads a menu from the resource file.
**
** Parameters:	iRscID		The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupMenu::LoadRsc(uint iRscID)
{
	ASSERT(m_hMenu   == NULL);
	ASSERT(m_hParent == NULL);

	// Load the resource.
	m_hParent = ::LoadMenu(CModule::This().Handle(), MAKEINTRESOURCE(iRscID));

	ASSERT(m_hParent != NULL);

	// Get the popup menu.
	m_hMenu = ::GetSubMenu(m_hParent, 0);

	ASSERT(m_hMenu != NULL);
}

/******************************************************************************
** Method:		TrackMenu()
**
** Description:	Shows and tracks a popup menu.
**
** Parameters:	rParent		The menus parent window.
**				ptOrigin	The position of the menus top-left corner.
**
** Returns:		The command ID or NULL.
**
*******************************************************************************
*/

uint CPopupMenu::TrackMenu(CWnd& rParent, const CPoint& ptOrigin)
{
	return ::TrackPopupMenu(m_hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
							ptOrigin.x, ptOrigin.y, NULL, rParent.Handle(), NULL);
}
