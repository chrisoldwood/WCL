/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BUTTON.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CButton class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Button.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Override any default settings for the window class and style.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CButton::CButton()
{
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

void CButton::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = TXT("BUTTON");
	rParams.dwStyle     |= BS_PUSHBUTTON;
}
