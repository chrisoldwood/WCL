/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAINDLG.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMainDlg class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	iRscID		The dialog template resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMainDlg::CMainDlg(uint iRscID) : CDialog(iRscID)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	iRscID		The dialog template resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMainDlg::~CMainDlg()
{
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paint the top and bottom etched borders.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMainDlg::OnPaint(CDC& rDC)
{
	// Draw etched line at top.
	CRect rcClient = ClientRect();
	rDC.HorzLine3D(rcClient.left, rcClient.right, rcClient.top,      false);
	rDC.HorzLine3D(rcClient.left, rcClient.right, rcClient.bottom-2, false);
}
