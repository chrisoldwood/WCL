/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATUSBARPANEL.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CStatusBarPanel class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StatusBarPanel.hpp"
#include "DC.hpp"

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

CStatusBarPanel::CStatusBarPanel()
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

CStatusBarPanel::~CStatusBarPanel()
{
}

/******************************************************************************
** Method:		GetClassParams()
**
** Description:	Template method to get the window class data.
**
** Parameters:	rParams		The class structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBarPanel::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	rParams.lpszClassName = "StatusBarPanel";
}

/******************************************************************************
** Method:		GetCreateParams()
**
** Description:	Template method to get the window creation data.
**
** Parameters:	rParams		The create structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBarPanel::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = "StatusBarPanel";
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the panel border.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBarPanel::OnPaint(CDC& rDC)
{
	CRect rcClient = ClientRect();

	rDC.Border3D(rcClient, false, false);
}
