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
	CRect rcClient = ClientRect();

	// Get the parent CFrameWnd.
	CFrameWnd* pParentFrame = static_cast<CFrameWnd*>(m_pParentWnd);

	// Draw upper border.
	if ( (pParentFrame->ToolBar() != NULL) || (pParentFrame->Menu() != NULL) )
		rDC.HorzLine3D(rcClient.left, rcClient.right, rcClient.top, false);

	// Draw lower border.
	if (pParentFrame->StatusBar() != NULL)
		rDC.HorzLine3D(rcClient.left, rcClient.right, rcClient.bottom-2, false);
}
