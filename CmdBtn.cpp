/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CMDBTN.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCmdButton class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

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

CCmdButton::CCmdButton()
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

void CCmdButton::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CButton::GetCreateParams(rParams);

	// Override any settings.
	rParams.dwStyle |= BS_OWNERDRAW;
}

/******************************************************************************
** Method:		OnDrawItem()
**
** Description:	Draw the button.
**
** Parameters:	See DRAWITEMSTRUCT.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCmdButton::OnDrawItem(uint iID, uint iAction, uint iState, CDC& rDC,
							uint iItem, const CRect& rcItem)
{
	// Repaint or Selection change?
	if ( (iAction & ODA_DRAWENTIRE) || (iAction & ODA_SELECT) )
	{
		CPoint ptDst;
		
		// Button down?
		if (iState & ODS_SELECTED)
		{
			ptDst.x = 1;
			ptDst.y = 1;
		}
		// Button up
		else
		{
			ptDst.x = 0;
			ptDst.y = 0;
		}

		// Get application object.
		CApp* pApp = CApp::This();
		ASSERT(pApp);

		CRect rcDst(ptDst, rcItem.Size());

		// Draw button face.
		if (iState & ODS_DISABLED)
			pApp->m_rCmdControl.DrawCmd(iID, rDC, rcDst, false);
		else
			pApp->m_rCmdControl.DrawCmd(iID, rDC, rcDst, true);
		
		// Draw button border.
		if (iState & ODS_SELECTED)
			rDC.Border3D(rcItem, false, true);
		else
			rDC.Border3D(rcItem, true, true);
	}
}
