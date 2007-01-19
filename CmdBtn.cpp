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

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
**
** Constants.
**
*******************************************************************************
*/

// Border deactivation timer frequency.
const uint  TIMER_ID   = 1;
const dword TIMER_FREQ = 100;

/******************************************************************************
**
** Class members.
**
*******************************************************************************
*/

CCmdButton* CCmdButton::g_pActiveBtn = NULL;

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
	: m_bOnToolbar(true)
	, m_bTimerOn(false)
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
** Method:		WndProc()
**
** Description:	Catch WM_MOUSEMOVE messages.
**				
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CCmdButton::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Decode message.
	switch(iMsg)
	{
		// Mouse moved.
		case WM_MOUSEMOVE:
			OnMouseMove(CPoint(LOWORD(lParam), HIWORD(lParam)), wParam);
			break;

		// Timer gone off.
		case WM_TIMER:
			OnTimer(wParam);
			break;

		// Call the default handler.
		default:
			break;
	}

	// Call the base class' handler.
	return CStdWnd::WndProc(hWnd, iMsg, wParam, lParam);
}

/******************************************************************************
** Method:		OnNCDestroy()
**
** Description:	The window has been destroyed. Clean up.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCmdButton::OnNCDestroy()
{
	// Clear up border timer.
	if (m_bTimerOn)
		StopTimer(TIMER_ID);

	// Forward to base class.
	CButton::OnNCDestroy();
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
							uint /*iItem*/, const CRect& rcItem)
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
		CApp& oApp = CApp::This();

		CRect rcDst(ptDst, rcItem.Size());

		// Draw button face.
		if (iState & ODS_DISABLED)
			oApp.m_rCmdControl.DrawCmd(iID, rDC, rcDst, false);
		else
			oApp.m_rCmdControl.DrawCmd(iID, rDC, rcDst, true);

		// Draw button border, if non-toolbar style OR is 'active' toolbar button.
		if ( (!m_bOnToolbar) || ((iState & ODS_SELECTED) || (::GetCapture() == m_hWnd) || (g_pActiveBtn == this)) )
		{
			bool bThick = !m_bOnToolbar;

			if (iState & ODS_SELECTED)
				rDC.Border3D(rcItem, false, bThick);
			else
				rDC.Border3D(rcItem, true, bThick);
		}
	}
}

/******************************************************************************
** Method:		OnMouseMove()
**
** Description:	Mouse movement over the button.
**
** Parameters:	ptCursor	Mouse position.
**				iKeyFlags	State of control keys.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCmdButton::OnMouseMove(const CPoint& /*ptCursor*/, uint /*iKeyFlags*/)
{
	// Ignore, if not on a toolbar.
	if (!m_bOnToolbar)
		return;

	// Change 'active' button?
	if (g_pActiveBtn != this)
	{
		// Hide border on previous button.
		if (g_pActiveBtn != NULL)
			g_pActiveBtn->Invalidate();

		g_pActiveBtn = this;

		// Show border on this button.
		g_pActiveBtn->Invalidate();

		// Kick off border deactivation timer.
		if (!m_bTimerOn)
		{
			StartTimer(TIMER_ID, TIMER_FREQ);
			m_bTimerOn = true;
		}
	}
}

/******************************************************************************
** Method:		OnTimer()
**
** Description:	A timer has gone off. Check if the border should be remvoed.
**
** Parameters:	iTimerID	The timers' ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCmdButton::OnTimer(uint iTimerID)
{
	DEBUG_USE_ONLY(iTimerID);
	ASSERT(iTimerID == TIMER_ID);
	ASSERT(m_bOnToolbar);

	// No longer active?
	if (g_pActiveBtn != this)
	{
		StopTimer(TIMER_ID);
	
		m_bTimerOn = false;
	}
	else // (g_pActiveBtn == this)
	{
		POINT ptCursor;

		::GetCursorPos(&ptCursor);

		// Mouse not captured AND no longer over this button?
		if ( (::GetCapture() != m_hWnd) && (::WindowFromPoint(ptCursor) != m_hWnd) )
		{
			StopTimer(TIMER_ID);
		
			m_bTimerOn = false;
			g_pActiveBtn = NULL;

			Invalidate();
		}
	}
}
