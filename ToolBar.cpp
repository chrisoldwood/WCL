/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TOOLBAR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CToolBar class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

// Border around controls.
#define BORDER_SIZE		3

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

CToolBar::CToolBar()
	: m_pCtrlTable(NULL)
{
	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);

	// Add to the main threads' msg filters.
	pApp->m_MainThread.AddMsgFilter(*this);
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
	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);

	// Remove from the main threads' msg filters.
	pApp->m_MainThread.RemoveMsgFilter(*this);
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
	rParams.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	rParams.lpszClassName = "ToolBar";
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

	// Get height of controls.
	int iCtrlHt = 24;

	// Override any settings.
	rParams.pszClassName = "ToolBar";
	rParams.rcPos.Set(0, 0, 0, iCtrlHt + (BORDER_SIZE*2) + 2);
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

void CToolBar::OnCreate(const CRect& rcClient)
{
	// Any controls?
	if (m_pCtrlTable == NULL)
		return;

	int		iCtrlHt = 24;
	CPoint	ptOrigin(iCtrlHt/2, BORDER_SIZE+2);
	CSize	dmSize(iCtrlHt, iCtrlHt);
	CTRL*	pCtrl = m_pCtrlTable;

	// For all controls.
	while ( (pCtrl) && (pCtrl->iID) )
	{
		// Separator?
		if (pCtrl->iID == IDC_SEPARATOR)
		{
			// Leave a gap.
			ptOrigin.x += iCtrlHt/2;
		}
		// Control
		else
		{
			// Create control.
			pCtrl->pWnd->Create(*this, pCtrl->iID, CRect(ptOrigin, dmSize));
			ptOrigin.x += iCtrlHt;
		}
		
		// Move to next.
		pCtrl++;
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

void CToolBar::OnCtrlMsg(uint iID, uint iMsg, HWND hControl)
{
	// Forward to frame window.
	if (iMsg == BN_CLICKED)
		::PostMessage(GetParent(m_hWnd), WM_COMMAND, iID, 0L);
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
				OnShowHint(NULL);
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
** Parameters:	pWnd	The window to show the hint for or NULL to remove the
**						hint.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CToolBar::OnShowHint(const CWnd* pWnd) const
{
	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);

	// Get the status bar.
	CStatusBar*	pStatusBar = pApp->m_rMainWnd.StatusBar();
	if (pStatusBar == NULL)
		return;

	// Show a hint?
	if (pWnd)
		pStatusBar->Hint(::GetDlgCtrlID(pWnd->Handle()));
	else
		pStatusBar->Hint("");
}
