/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCEL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CAccel class methods.
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

CAccel::CAccel()
{
	m_hAccel = NULL;
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

CAccel::~CAccel()
{
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads an accelerator table from the resource file.
**
** Parameters:	iRscID		The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccel::LoadRsc(uint iRscID)
{
	ASSERT(m_hAccel == NULL);

	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);
	
	// Load the resource.
	m_hAccel = ::LoadAccelerators(pApp->m_hInstance, MAKEINTRESOURCE(iRscID));
	ASSERT(m_hAccel);
}

/******************************************************************************
** Method:		Translate()
**
** Description:	Attempts to translate an accelerator keystroke.
**
** Parameters:	hWnd	The message window destination.
**				pMsg	The message.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CAccel::Translate(HWND hWnd, MSG& rMsg)
{
	// Attempt to translate it.
	if (m_hAccel)
		return TranslateAccelerator(hWnd, m_hAccel, &rMsg);
	
	return false;
}
