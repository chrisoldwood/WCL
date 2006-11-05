/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FRAMEWND.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CFrameWnd class methods.
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

// Window class name.
const char* CFrameWnd::CLASS_NAME = "FrameWnd";

/******************************************************************************
** Method:		Default constructor.
**
** Description:	.
**
** Parameters:	iIconID		The frame window icon.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFrameWnd::CFrameWnd(uint iIconID)
	: m_iIconID(iIconID)
	, m_pAccel(NULL)
	, m_pMenu(NULL)
	, m_pToolBar(NULL)
	, m_pStatusBar(NULL)
	, m_pActiveDlg(NULL)
{
	// Add to the main threads' msg filters.
	CApp::This().m_MainThread.AddMsgFilter(this);
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

CFrameWnd::~CFrameWnd()
{
	// Remove from the main threads' msg filters.
	CApp::This().m_MainThread.RemoveMsgFilter(this);
}

/******************************************************************************
** Method:		GetClassParams()
**
** Description:	Template method to get the window class data.
**
** Parameters:	rParams		The class structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CPopupWnd::GetClassParams(rParams);

	// Override any settings.
	rParams.hIcon         = ::LoadIcon(CModule::This().Handle(), MAKEINTRESOURCE(m_iIconID));
	rParams.hbrBackground = (HBRUSH) (COLOR_BTNSHADOW + 1);
	rParams.lpszClassName = CLASS_NAME;

	ASSERT(rParams.hIcon);
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

void CFrameWnd::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CPopupWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName  = CLASS_NAME;
	rParams.pszTitle      = CApp::This().m_strTitle;
	rParams.dwStyle       = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
	rParams.hParent       = HWND_DESKTOP;
}

/******************************************************************************
** Method:		Accel()
**
** Description:	Set the accelerator table.
**
** Parameters:	pAccel		The accelerator table.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::Accel(CAccel* pAccel)
{
	m_pAccel = pAccel;
}

/******************************************************************************
** Method:		Menu()
**
** Description:	Set the menu.
**
** Parameters:	pMenu		The menu.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::Menu(CFrameMenu* pMenu)
{
	m_pMenu = pMenu;

	// Attach to window.
	if ( (m_hWnd) && (m_pMenu) )
		::SetMenu(m_hWnd, m_pMenu->Handle());
}

/******************************************************************************
** Method:		ToolBar()
**
** Description:	Set the toolbar.
**
** Parameters:	pToolBar	The toolbar.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::ToolBar(CToolBar* pToolBar)
{
	m_pToolBar = pToolBar;
}

/******************************************************************************
** Method:		StatusBar()
**
** Description:	Set the status bar.
**
** Parameters:	pStatusBar	The status bar.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::StatusBar(CStatusBar* pStatusBar)
{
	m_pStatusBar = pStatusBar;
}

/******************************************************************************
** Method:		ActiveDlg()
**
** Description:	Set the active dialog.
**
** Parameters:	pDialog		The active dialog.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::ActiveDlg(CDialog* pDialog)
{
	m_pActiveDlg = pDialog;
}

/******************************************************************************
** Method:		WndProc()
**
** Description:	This is the window procedure that performs message processing
**				that is specific to a main window.
**				
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CFrameWnd::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Decode message.
	switch(iMsg)
	{
		// App is being activated.	
		case WM_ACTIVATEAPP:
			OnActivateApp(wParam);
			break;
		
		// Drag'n'drop performed.
		case WM_DROPFILES:
			{
				HDROP hDrop  = (HDROP)wParam;
				int   nFiles = ::DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

				// For all files
				for (int i = 0; i < nFiles; i++)
				{
					char szPath[MAX_PATH+1];

					// Get filename and process.
					if (::DragQueryFile(hDrop, i, szPath, MAX_PATH) > 0)
						OnDropFile(i, szPath);
				}
			}
			break;

		// Can Windows shutdown?
		case WM_QUERYENDSESSION:
			if (OnQueryClose())
			{
				MsgHandled(true);
				MsgResult (TRUE);
				return 0;
			}
			break;

		// Application shutting down.
		case WM_CLOSE:
			if (OnQueryClose())
			{
				OnClose();

				// Detach menu first
				::SetMenu(m_hWnd, NULL);

				Destroy();
			}
			break;

		// Windows shutting down.
		case WM_ENDSESSION:
			if (wParam == TRUE)
			{
				OnClose();

				// Detach menu first
				::SetMenu(m_hWnd, NULL);

				Destroy();
			}
			break;

		// Main window destroyed.
		case WM_DESTROY:
			// Terminate message loop.
			PostQuitMessage(0);
			return CPopupWnd::WndProc(hWnd, iMsg, wParam, lParam);

		// Call the default handler.
		default:
			return CPopupWnd::WndProc(hWnd, iMsg, wParam, lParam);
	}

	MsgHandled(true);
	MsgResult (0);

	return 0;
}

/******************************************************************************
** Method:		OnResize()
**
** Description:	The window has been resized. This resizes the toolbar and info
**				line to match the new settings.
**
** Parameters:	iFlag		The resize method.
**				rNewSize	The new window dimensions.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::OnResize(int iFlag, const CSize& rNewSize)
{
	// Only when our window is changed.
	if ( (iFlag == SIZE_RESTORED) || (iFlag == SIZE_MAXIMIZED) )
	{
		// Resize toolbar.
		if (m_pToolBar)
		{
			// Get current pos.
			CRect rcToolBar = m_pToolBar->ClientRect();
			
			// Calc new pos and move.
			CRect rcNewPos(0, 0, rNewSize.cx, rcToolBar.Size().cy);
			m_pToolBar->Move(rcNewPos);
		}
		
		// Resize Status bar.
		if (m_pStatusBar)
		{
			// Get current pos.
			CRect rcStatusBar = m_pStatusBar->ClientRect();

			// Calc new pos and move.
			CRect rcNewPos(0, rNewSize.cy - rcStatusBar.Size().cy, 
								rNewSize.cx, rNewSize.cy);
			m_pStatusBar->Move(rcNewPos);
		}
	}
}

/******************************************************************************
** Method:		OnQueryClose()
**
** Description:	Queries if the main window can close.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFrameWnd::OnQueryClose()
{
	return true;
}

/******************************************************************************
** Method:		OnClose()
**
** Description:	The main window is closing.
**				NB: Called from WM_CLOSE or WM_ENDSESSION.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::OnClose()
{
}

/******************************************************************************
** Method:		ClientRect()
**
** Description:	Get the position of the client area, accounting for the DIL
**				and toolbars etc.
**
** Parameters:	None.
**
** Returns:		The rect.
**
*******************************************************************************
*/

CRect CFrameWnd::ClientRect() const
{
	CRect rcClient;

	// Get the maximum size.
	::GetClientRect(m_hWnd, &rcClient);

	// Has a visible toolbar.
	if ( (m_pToolBar) && (m_pToolBar->IsVisible()) )
	{
		// Get current pos.
		CRect rcToolBar = m_pToolBar->ClientRect();
			
		// Adjust client rect.
		rcClient.top += rcToolBar.Height();
	}

	// Has a visible info line.
	if ( (m_pStatusBar) && (m_pStatusBar->IsVisible()) )
	{
		// Get current pos.
		CRect rcStatusBar = m_pStatusBar->ClientRect();

		// Adjust client rect.
		rcClient.bottom -= rcStatusBar.Height();
	}
	
	return rcClient;
}

/******************************************************************************
** Method:		OnActivateApp()
**
** Description:	The application is about to be activated or de-activated.
**
** Parameters:	bActivating		Being activated?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::OnActivateApp(bool /*bActivating*/)
{
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paint a 3D border.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::OnPaint(CDC& rDC)
{
	rDC.Border3D(ClientRect(), false, true);
}

/******************************************************************************
** Method:		ProcessMsg()
**
** Description:	Try and process the message using the accelerator table or
**				active modeless dialog.
**
** Parameters:	pMsg	The message.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFrameWnd::ProcessMsg(MSG& rMsg)
{
	// Try accelerator table first.
	if ( (m_pAccel != NULL) && (m_pAccel->Translate(m_hWnd, rMsg)) )
		return true;

	// Try active modeless dialog next.
	if ( (m_pActiveDlg != NULL) && (::IsDialogMessage(m_pActiveDlg->Handle(), &rMsg)) )
		return true;

	return false;
}

/******************************************************************************
** Method:		OnDropFile()
**
** Description:	The user has drag'n'dropped one or more files onto the window.
**
** Parameters:	nFile		The index of the dropped file.
**				pszPath		The files' path.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::OnDropFile(int /*nFile*/, const char* /*pszPath*/)
{
}
