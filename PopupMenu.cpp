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
