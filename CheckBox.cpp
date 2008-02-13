/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CHECKBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCheckBox class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "CheckBox.hpp"

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

CCheckBox::CCheckBox()
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

void CCheckBox::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = TXT("BUTTON");
	rParams.dwStyle     |= BS_AUTOCHECKBOX;
}
