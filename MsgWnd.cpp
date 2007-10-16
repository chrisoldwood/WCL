/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MSGWND.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMsgWnd class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "MsgWnd.hpp"
#include "ScreenDC.hpp"
#include "App.hpp"
#include "CmdCtrl.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Initialise members.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMsgWnd::CMsgWnd()
	: m_pbMsgHandled(NULL)
	, m_plMsgResult(NULL)
	, m_pCtrlMsgTable(NULL)
{
}

/******************************************************************************
** Method:		WndProc()
**
** Description:	This is the base implementation of a CMsgWnd window message
**				handler. It handles all messages common to all popup windows.
**				This is a virtual function and is overriden by derived clases
**				to farm out more specific messages, but should always be called
**				by derived clases to get the default processing.
**				
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CMsgWnd::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_pbMsgHandled != NULL);
	ASSERT(m_plMsgResult  != NULL);

	// Is in WM_USER range?
	if ( (iMsg >= WM_USER) && (iMsg < WM_APP) )
		OnUserMsg(iMsg, wParam, lParam);

	// Is in WM_APP range?
	if ( (iMsg >= WM_APP) && (iMsg < 0xC000) )
		OnAppMsg(iMsg, wParam, lParam);

	// Is in RegisterWindowMessage() range ?
	if ( (iMsg >= 0xC000) && (iMsg < 0xFFFF) )
		OnRegisteredMsg(iMsg, wParam, lParam);
	
	// Decode message.
	switch(iMsg)
	{
		// Child control message.
		case WM_COMMAND:
			if (lParam == NULL)
				OnCmdMsg(LOWORD(wParam));
			else
				OnCtrlMsg(LOWORD(wParam), HIWORD(wParam), (HWND)lParam);
			break;

		// Child control message.
		case WM_NOTIFY:
			{
				NMHDR* pMsgHdr = (NMHDR*) lParam;
				ASSERT(pMsgHdr);

				*m_plMsgResult  = OnCtrlMsg(*pMsgHdr);
				*m_pbMsgHandled = true;
				return 0;
			}
			break;

		// Window background needs painting.
		case WM_ERASEBKGND:
			{
				// Assume the message will be handled.
				*m_pbMsgHandled = true;
				*m_plMsgResult  = TRUE;

				// Construct a device and call the method.
				CScreenDC	DC((HDC) wParam);
				OnEraseBackground(DC);
				return 0;
			}
			break;

		// Window needs redrawing.	
		case WM_PAINT:
			PAINTSTRUCT psPaint;
			BeginPaint(hWnd, &psPaint);
			{
				// Construct a device and call the paint method.
				CScreenDC	DC(psPaint);
				OnPaint(DC);
			}
			EndPaint(hWnd, &psPaint);
			break;

		// Initialise DC for child controls.
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
			OnCtlColour(iMsg, (HDC)wParam, (HWND)lParam);
			return 0;

		// Hit test on the window.
		case WM_NCHITTEST:
			OnHitTest(CPoint(LOWORD(lParam), HIWORD(lParam)));
			return 0;

		// Window resized.
		case WM_SIZE:
			{
				CSize NewSize(LOWORD(lParam), HIWORD(lParam));
				OnResize(wParam, NewSize);
			}
			break;

		// Window is being enabled or disabled.
		case WM_ENABLE:
			//OnEnable((bool)wParam);
			break;
        
		// Timer gone off.
		case WM_TIMER:
			OnTimer(wParam);
			break;

		// Horizontal scrollbar changed.
		case WM_HSCROLL:
			OnHorizScroll(wParam, LOWORD(lParam));
			break;

		// Vertical scrollbar changed.
		case WM_VSCROLL:
			OnVertScroll(wParam, LOWORD(lParam));
			break;

		// Window being shown.
		case WM_SHOWWINDOW:
			OnShow(wParam);
			break;

		// Measure a control/menu.
		case WM_MEASUREITEM:
			{
				MEASUREITEMSTRUCT* lpInfo = (MEASUREITEMSTRUCT*) lParam;

				// Is a control?
				if (lpInfo->CtlType != ODT_MENU)
				{
					OnMeasureItem(lpInfo->CtlID, lpInfo->itemID, lpInfo->itemWidth, lpInfo->itemHeight);
				}
				// Is a menu.
				else
				{
					// TODO: Menu handling.
				}
			}
			break;

		// Draw part of a control/menu.
		case WM_DRAWITEM:
			{
				DRAWITEMSTRUCT* lpInfo = (DRAWITEMSTRUCT*) lParam;

				// Is a control?
				if (lpInfo->CtlType != ODT_MENU)
				{
					// Get control.
					CMsgWnd* pWnd = (CMsgWnd*) CWnd::s_WndMap.Find(lpInfo->hwndItem);
					ASSERT(pWnd);
					
					// Construct a paint DC.
					CScreenDC	dcPaint(lpInfo->hDC);
					CRect		rcItem(&lpInfo->rcItem);
					
					pWnd->OnDrawItem(lpInfo->CtlID, lpInfo->itemAction, lpInfo->itemState,
										dcPaint, lpInfo->itemID, rcItem);
				}
				// Is a menu.
				else
				{
					// TODO: Menu painting.
				}
			}
			break;
		
		// Help requested.
		case WM_HELP:
			{
				HELPINFO* pInfo = (LPHELPINFO)lParam;

				OnHelp(*pInfo);
			}
			break;

		// Window being destroyed.
		case WM_DESTROY:
			OnDestroy();
			break;
		
		// Window being destroyed (Non-client).
		case WM_NCDESTROY:
			OnNCDestroy();
			break;

		// Call the default handler.
		default:
			return DefaultWndProc(hWnd, iMsg, wParam, lParam);
	}

	*m_pbMsgHandled = true;
	*m_plMsgResult  = 0;

	return 0;
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	The window has just been created.
**
** Parameters:	rcClient	The client area.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnCreate(const CRect& /*rcClient*/)
{
}

/******************************************************************************
** Method:		OnEraseBackground()
**
** Description:	Window background needs repainting
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnEraseBackground(CDC& rDC)
{
	DefaultWndProc(m_hWnd, WM_ERASEBKGND, (WPARAM)rDC.Handle(), 0L);
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Window needs repainting. By default do nothing.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnPaint(CDC& /*rDC*/)
{
}

/******************************************************************************
** Method:		OnResize()
**
** Description:	Window has been resized. By default do nothing.
**
** Parameters:	iFlag		The resize method.
**				rNewSize	The new window dimensions.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnResize(int /*iFlag*/, const CSize& /*rNewSize*/)
{
}

/******************************************************************************
** Method:		OnTimer()
**
** Description:	A timer has gone off. By default do nothing.
**
** Parameters:	iTimerID	The timers' ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnTimer(uint /*iTimerID*/)
{
}

/******************************************************************************
** Method:		OnShow()
**
** Description:	The window is about to be shown. By default do nothing.
**
** Parameters:	bShowing	Being shown?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnShow(bool /*bShowing*/)
{
}

/******************************************************************************
** Method:		OnDestroy()
**
** Description:	The window is being destroyed. By default do nothing.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnDestroy()
{
}

/******************************************************************************
** Method:		OnNCDestroy()
**
** Description:	The window has been destroyed. Unmap handle.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnNCDestroy()
{
	// Delete object mapping.
	CWnd::s_WndMap.Remove(*this);

	m_hWnd = NULL;
}

/******************************************************************************
** Methods:		OnHorizScroll()
**				OnVertScroll()
**
** Description:	User has moved a scroll bar.
**
** Parameters:	iCode		How the scroll bar was moved.
**				iPos		Position of scroll bar for SB_THUMB*.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnHorizScroll(uint /*iCode*/, uint /*iPos*/)
{
}

void CMsgWnd::OnVertScroll(uint /*iCode*/, uint /*iPos*/)
{
}

/******************************************************************************
** Method:		OnCmdMsg()
**
** Description:	Execute the command.
**
** Parameters:	iID		Menu ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnCmdMsg(uint iID)
{
	// Forward msg to cmd controller.
	CApp::This().m_rCmdControl.Execute(iID);
}

/******************************************************************************
** Method:		OnCtrlMsg()
**
** Description:	A message has been sent by a child control to its parent. This
**				is the code used by the parent to handle the message. It first
**				forwards the message to the child control before calling the
**				handler set up by the parent.
**				NB: This only handles WM_COMMAND style events.
**
** Parameters:	iID			Child control ID.
**				iMsg		Control message.
**				hControl	Handle of control window.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnCtrlMsg(uint iID, uint iMsg, HWND hControl)
{
	// Find if control is mapped.
	CMsgWnd* pWnd = (CMsgWnd*) CWnd::s_WndMap.Find(hControl);

	// Reflect message back to control.
	if (pWnd != NULL)
		pWnd->OnReflectedCtrlMsg(iMsg);

	CTRLMSG* pCtrlMsg = m_pCtrlMsgTable;
	
	// Find control callback function.
	while ( (pCtrlMsg) && (pCtrlMsg->m_iCtrlID)
		 && ((pCtrlMsg->m_iMsgType != WM_COMMAND) || (pCtrlMsg->m_iCtrlID != iID) || (pCtrlMsg->m_iMsgID != iMsg)) )
	    pCtrlMsg++;

	// If found, call handler.
	if ( (pCtrlMsg) && (pCtrlMsg->m_iMsgType == WM_COMMAND)
	  && (pCtrlMsg->m_iCtrlID == iID) && (pCtrlMsg->m_iMsgID == iMsg) )
	{
		PFNCMDMSGHANDLER pfnMsgHandler = (PFNCMDMSGHANDLER) pCtrlMsg->m_pfnMsgHandler;
		(this->*pfnMsgHandler)();
	}
}

/******************************************************************************
** Method:		OnCtrlMsg()
**
** Description:	A message has been sent by a child control to its parent. This
**				is the code used by the parent to handle the message. It first
**				forwards the message to the child control before calling the
**				handler set up by the parent.
**				NB: This only handles WM_NOTIFY style events.
**
** Parameters:	rMsgHdr		The message.
**
** Returns:		Depends on the message.
**
*******************************************************************************
*/

LRESULT CMsgWnd::OnCtrlMsg(NMHDR& rMsgHdr)
{
	// Find if control is mapped.
	CMsgWnd* pWnd = (CMsgWnd*) CWnd::s_WndMap.Find(rMsgHdr.hwndFrom);

	// Reflect message back to control.
	if (pWnd != NULL)
		pWnd->OnReflectedCtrlMsg(rMsgHdr);

	LRESULT  lResult  = 0;
	CTRLMSG* pCtrlMsg = m_pCtrlMsgTable;
	uint	 iID      = rMsgHdr.idFrom;
	uint	 iMsg     = rMsgHdr.code;
	
	// Find control callback function.
	while ( (pCtrlMsg) && (pCtrlMsg->m_iCtrlID)
		 && ((pCtrlMsg->m_iMsgType != WM_NOTIFY) || (pCtrlMsg->m_iCtrlID != iID) || (pCtrlMsg->m_iMsgID != iMsg)) )
	    pCtrlMsg++;

	// If found, call handler.
	if ( (pCtrlMsg) && (pCtrlMsg->m_iMsgType == WM_NOTIFY)
	  && (pCtrlMsg->m_iCtrlID == iID) && (pCtrlMsg->m_iMsgID == iMsg) )
	{
		PFNNFYMSGHANDLER pfnMsgHandler = (PFNNFYMSGHANDLER) pCtrlMsg->m_pfnMsgHandler;
		lResult = (this->*pfnMsgHandler)(rMsgHdr);
	}

	return lResult;
}

/******************************************************************************
** Method:		OnReflectedCtrlMsg()
**
** Description:	A message from this child (usually a built-in Windows control)
**				has been sent to the parent and reflected back here to the
**				control. This method is usually overriden in a derived class.
**				NB: This is for WM_COMMAND style events.
**
** Parameters:	iMsg		Control message.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnReflectedCtrlMsg(uint /*iMsg*/)
{
}

/******************************************************************************
** Method:		OnReflectedCtrlMsg()
**
** Description:	A message from this child (usually a built-in Windows control)
**				has been sent to the parent and reflected back here to the
**				control. This method is usually overriden in a derived class.
**				NB: This is for WM_NOTIFY style events.
**
** Parameters:	rMsgHdr		The message.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnReflectedCtrlMsg(NMHDR& /*rMsgHdr*/)
{
}

/******************************************************************************
** Method:		OnActivate()
**
** Description:	The window is about to be activated or de-activated.
**
** Parameters:	bActivating		Being activated?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnActivate(bool /*bActivating*/)
{
}

/******************************************************************************
** Method:		OnMeasureItem()
**
** Description:	Get measurements for a control/menu item.
**
** Parameters:	See MEASUREITEMSTRUCT.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnMeasureItem(uint /*iID*/, uint /*iItem*/, uint& /*iWidth*/, uint& /*iHeight*/)
{
}

/******************************************************************************
** Method:		OnDrawItem()
**
** Description:	Draw an item of the control.
**
** Parameters:	See DRAWITEMSTRUCT.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnDrawItem(uint /*iID*/, uint /*iAction*/, uint /*iState*/, CDC& /*rDC*/,
							uint /*iItem*/, const CRect& /*rcItem*/)
{
}

/******************************************************************************
** Method:		OnSetCursor()
**
** Description:	Set the cursor for the given window.
**
** Parameters:	hWnd		The window requiring a cursor.
**				nHitCode	The HTXXX hit test code.
**				nMouseMsg	The WM_* mouse message that generated the event.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnSetCursor(HWND hWnd, uint nHitCode, uint nMouseMsg)
{
	DefaultWndProc(m_hWnd, WM_SETCURSOR, (WPARAM)hWnd, MAKELPARAM(nHitCode, nMouseMsg));
}

/******************************************************************************
** Method:		OnCtlColour()
**
** Description:	Gets the colours for a child control.
**				All WM_CTLCOLOR* messages map to this one.
**
** Parameters:	nCtlClrMsg	The WM_CTLCOLOR* message,
**				hDC			The drawing HDC.
**				hCtlWnd		The controls hWhd.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnCtlColour(uint nCtlClrMsg, HDC hDC, HWND hCtlWnd)
{
	HBRUSH hBrush = NULL;

	// Find if control is mapped.
	CMsgWnd* pWnd = (CMsgWnd*) CWnd::s_WndMap.Find(hCtlWnd);

	// Reflect message back to control first.
	if (pWnd != NULL)
		hBrush = pWnd->OnReflectedCtlClr(nCtlClrMsg, hDC);

	if (hBrush != NULL)
	{
		MsgHandled((BOOL)hBrush);
		MsgResult (0);
	}
	// If still not handled, call DefWindowProc.
	else
	{
		DefaultWndProc(m_hWnd, nCtlClrMsg, (WPARAM)hDC, (LPARAM)hCtlWnd);
	}
}

/******************************************************************************
** Method:		OnReflectedCtlClr()
**
** Description:	The WM_CTLCOLOR* message reflected from the parent back to the
**				child.
**
** Parameters:	nCtlClrMsg	The WM_CTLCOLOR* message,
**				hDC			The drawing HDC.
**
** Returns:		See WM_CTLCOLOR*.
**
*******************************************************************************
*/

HBRUSH CMsgWnd::OnReflectedCtlClr(uint /*nCtlClrMsg*/, HDC /*hDC*/)
{
	return NULL;
}

/******************************************************************************
** Method:		OnHelp()
**
** Description:	Help requested for the window.
**
** Parameters:	See HELPINFO.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnHelp(HELPINFO& /*oInfo*/)
{
}

/******************************************************************************
** Method:		OnUserMsg()
**
** Description:	Message handler for messages in the WM_USER range of
**				0x0400 - 0x7FFF.
**
** Parameters:	As WindowProc.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnUserMsg(uint /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
}

/******************************************************************************
** Method:		OnAppMsg()
**
** Description:	Message handler for messages in the WM_APP range of
**				0x8000 - 0xBFFF.
**
** Parameters:	As WindowProc.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnAppMsg(uint /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
}

/******************************************************************************
** Method:		OnRegisteredMsg()
**
** Description:	Message handler for messages in the RegisterWindowMessage()
**				range of 0xC000 - 0xFFFF.
**
** Parameters:	As WindowProc.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnRegisteredMsg(uint /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
}

/******************************************************************************
** Method:		OnHitTest()
**
** Description:	Queries the area of the window that the mouse is in.
**
** Parameters:	ptCursor	The mouse position in screen coordinates.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgWnd::OnHitTest(const CPoint& ptCursor)
{
	DefaultWndProc(m_hWnd, WM_NCHITTEST, 0, MAKELPARAM(ptCursor.x, ptCursor.y));
}
