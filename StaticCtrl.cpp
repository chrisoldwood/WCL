/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATICCTRL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CStaticCtrl class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

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

CStaticCtrl::CStaticCtrl()
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

void CStaticCtrl::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = "STATIC";
	rParams.dwStyle     |= SS_SIMPLE;
}
