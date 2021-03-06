/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		RADIOBTN.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CRadioBtn class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "RadioBtn.hpp"

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

CRadioBtn::CRadioBtn()
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

void CRadioBtn::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = TXT("BUTTON");
	rParams.dwStyle     |= BS_AUTORADIOBUTTON;
}
