/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ICONCTRL.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CIconCtrl class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "IconCtrl.hpp"
#include "Icon.hpp"

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

CIconCtrl::CIconCtrl()
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

void CIconCtrl::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = TXT("STATIC");
	rParams.dwStyle     |= SS_ICON;
}

/******************************************************************************
** Method:		Icon()
**
** Description:	Set the icon to the resource specified.
**
** Parameters:	nRscID		The icon resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIconCtrl::Icon(uint nRscID)
{
	CIcon oIcon;

	oIcon.LoadRsc(nRscID);

	Icon(oIcon.Handle());
}
