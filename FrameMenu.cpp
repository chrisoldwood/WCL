/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FRAMEMENU.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CFrameMenu class methods.
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

CFrameMenu::CFrameMenu()
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

CFrameMenu::~CFrameMenu()
{
	if (m_hMenu != NULL)
		::DestroyMenu(m_hMenu);
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

void CFrameMenu::LoadRsc(uint iRscID)
{
	// Free previous menu.
	if (m_hMenu != NULL)
	{
		::DestroyMenu(m_hMenu);
		m_hMenu = NULL;
	}

	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);
	
	// Load the resource.
	m_hMenu = ::LoadMenu(pApp->m_hInstance, MAKEINTRESOURCE(iRscID));
	ASSERT(m_hMenu != NULL);
}
