/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		UPDOWNBTNS.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CUpDownBtns class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "UpDownBtns.hpp"

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

CUpDownBtns::CUpDownBtns()
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

void CUpDownBtns::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = UPDOWN_CLASS;
//	rParams.dwStyle     |= ;
}
