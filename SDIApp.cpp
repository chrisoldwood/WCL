/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDIAPP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CSDIApp class definition.
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

CSDIApp::CSDIApp(CSDIFrame& rFrameWnd, CSDICmds& rCmdControl)
	: CApp(rFrameWnd, rCmdControl)
	, m_pDoc(NULL)
	, m_pView(NULL)
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

CSDIApp::~CSDIApp()
{
	ASSERT(m_pDoc  == NULL);
	ASSERT(m_pView == NULL);
}
