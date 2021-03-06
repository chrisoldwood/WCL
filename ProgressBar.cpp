/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROGRESSBAR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CProgressBar class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ProgressBar.hpp"

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

CProgressBar::CProgressBar()
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

void CProgressBar::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = PROGRESS_CLASS;
//	rParams.dwStyle     |= ;
}
