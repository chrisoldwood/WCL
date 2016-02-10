/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TOOLBAR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CToolBar class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ToolBar.hpp"
#include "App.hpp"
#include "DC.hpp"
#include "CmdCtrl.hpp"
#include "StatusBar.hpp"
#include "FrameWnd.hpp"
#include "ICmdController.hpp"

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Top border height.
const int TOP_BORDER = 2;

// Border around controls.
const int BORDER_SIZE = 0;

// Tooltip control ID.
const int TOOLTIP_ID = 10;

// Control size (square).
const int CONTROL_SIZE = 24;

// Separator border indent.
const int SEP_INDENT = 1;

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	rParent		The windows parent.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CToolBar::CToolBar(WCL::IMsgThread& thread, WCL::ICmdController& controller)
	: m_pCtrlTable(nullptr)
	, m_oToolTip()
	, m_thread(thread)
	, m_controller(controller)
{
	// Add to the main threads' msg filters.
	m_thread.AddMsgFilter(this);
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CToolBar::~CToolBar()
{
	// Remove from the main threads' msg filters.
	m_thread.RemoveMsgFilter(this);
}

/******************************************************************************
** Method:		GetClassParams()
**
** Description:	Template method to get the window creation data.
**
** Parameters:	rParams		The create structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CToolBar::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
	rParams.lpszClassName = TXT("ToolBar");
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

void CToolBar::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = TXT("ToolBar");
	rParams.rcPos.Set(0, 0, 0, CONTROL_SIZE + (BORDER_SIZE*2) + TOP_BORDER);
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Creates the controls.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CToolBar::OnCreate(const CRect& /*rcClient*/)
{
	// Create the tool tip control.
	m_oToolTip.Create(*this, TOOLTIP_ID, CRect());

	// Any controls?
	if (m_pCtrlTable == nullptr)
		return;

	CPoint	ptOrigin(0, BORDER_SIZE+TOP_BORDER);
	CSize	dmSize(CONTROL_SIZE, CONTROL_SIZE);
	CTRL*	pCtrl = m_pCtrlTable;

	// For all controls.
	while ( (pCtrl) && (pCtrl->nID) )
	{
		// Separator?
		if (pCtrl->nID == IDC_SEPARATOR)
		{
			// Leave a gap.
			ptOrigin.x += CONTROL_SIZE/2;
		}
		// Control
		else
		{
			// Create control.
			pCtrl->pWnd->Create(*this, pCtrl->nID, CRect(ptOrigin, dmSize));
			ptOrigin.x += CONTROL_SIZE;

			// Add to tooltip control.
			m_oToolTip.AddTool(*this, *pCtrl->pWnd, LPSTR_TEXTCALLBACK);
		}

		// Move to next.
		++pCtrl;
	}
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the toolbar background.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CToolBar::OnPaint(CDC& rDC)
{
	// Draw etched line at top.
	CRect rcClient = ClientRect();
	rDC.HorzLine3D(rcClient.left, rcClient.right, rcClient.top, false);

	CPoint ptOrigin(0, BORDER_SIZE+TOP_BORDER);

	// Draw all separators.
	for (CTRL* pCtrl = m_pCtrlTable; (pCtrl) && (pCtrl->nID); ++pCtrl)
	{
		// Separator?
		if (pCtrl->nID == IDC_SEPARATOR)
		{
			rDC.VertLine3D(ptOrigin.x+CONTROL_SIZE/4, rcClient.top+TOP_BORDER+(SEP_INDENT*2), rcClient.bottom-(SEP_INDENT*2), false);

			ptOrigin.x += CONTROL_SIZE/2;
		}
		// Control
		else
		{
			ptOrigin.x += CONTROL_SIZE;
		}
	}
}

/******************************************************************************
** Methods:		OnCtlMsg()
**
** Description:	Convert all BN_CLICKED messages into WM_COMMAND messages and
**				forward to the frame window.
**
** Parameters:	iID			Child control ID.
**				iMsg		Control message.
**				hControl	Handle of control window.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CToolBar::OnCtrlMsg(uint iID, uint iMsg, HWND /*hControl*/)
{
	// Forward to frame window.
	if (iMsg == BN_CLICKED)
		::PostMessage(GetParent(m_hWnd), WM_COMMAND, iID, 0L);
}

/******************************************************************************
** Method:		OnCtrlMsg()
**
** Description:	A WM_NOTIFY event has been sent, possibly from the tool tip
**				control (which has no ID).
**
** Parameters:	rMsgHdr		The message.
**
** Returns:		Depends on the message.
**
*******************************************************************************
*/

LRESULT CToolBar::OnCtrlMsg(NMHDR& rMsgHdr)
{
	// Get tool tip?
	if ( (rMsgHdr.hwndFrom == m_oToolTip.Handle())
	  && (rMsgHdr.code     == TTN_GETDISPINFO) )
	{
		NMTTDISPINFO& oInfo = reinterpret_cast<NMTTDISPINFO&>(rMsgHdr);

		ASSERT(oInfo.uFlags & TTF_IDISHWND);

		// Get the tip (Assumes the ID is the controls HWND).
		int nCtlID = ::GetDlgCtrlID(reinterpret_cast<HWND>(rMsgHdr.idFrom));

		// Return it.
		tstrcpy(oInfo.szText, m_controller.CmdToolTipStr(nCtlID));
		return 0;
	}

	return CCtrlWnd::OnCtrlMsg(rMsgHdr);
}

/******************************************************************************
** Method:		ProcessMsg()
**
** Description:	Check for mouse move events over the toolbars' controls and
**				show a hint if over a control.
**
** Parameters:	pMsg	The message.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CToolBar::ProcessMsg(MSG& rMsg)
{
	// Only interested in mouse moves.
	if (rMsg.message == WM_MOUSEMOVE)
	{
		// Is in the toolbar window?
		if (rMsg.hwnd == m_hWnd)
		{
			// Convert LPARAM to a point.
			CPoint ptCursor(GET_X_LPARAM(rMsg.lParam), GET_Y_LPARAM(rMsg.lParam));

			// Check for a disabled window.
			HWND hWnd = ::ChildWindowFromPoint(m_hWnd, ptCursor);

			// Is still toolbar?
			if (hWnd == m_hWnd)
				OnShowHint(nullptr);
			else
				OnShowHint(s_WndMap.Find(hWnd));
		}
		// Is in a toolbar control?
		else if (::GetParent(rMsg.hwnd) == m_hWnd)
		{
			OnShowHint(s_WndMap.Find(rMsg.hwnd));
		}
	}

	return false;
}

/******************************************************************************
** Method:		OnShowHint()
**
** Description:	Show the status bar hint for the toolbars' control.
**
** Parameters:	pWnd	The window to show the hint for or nullptr to remove the
**						hint.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CToolBar::OnShowHint(const CWnd* pWnd) const
{
	// Get the status bar.
	CStatusBar*	pStatusBar = CApp::This().m_rMainWnd.StatusBar();
	if (pStatusBar == nullptr)
		return;

	// Show a hint?
	if (pWnd != nullptr)
		pStatusBar->Hint(m_controller.CmdHintStr(::GetDlgCtrlID(pWnd->Handle())));
	else
		pStatusBar->Hint(TXT(""));
}
