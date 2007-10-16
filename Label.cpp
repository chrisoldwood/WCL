/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LABEL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CLabel class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Label.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Does nothing.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CLabel::CLabel()
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

void CLabel::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = "STATIC";
	rParams.dwStyle     |= SS_SIMPLE;
}
