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

CFrameWnd::~CFrameWnd()
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

	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);

	// Override any settings.
	rParams.hIcon         = ::LoadIcon(pApp->m_hInstance, MAKEINTRESOURCE(m_iIconID));
	rParams.hbrBackground = (HBRUSH) (COLOR_BTNSHADOW + 1);
	rParams.lpszClassName = "FrameWnd";

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

	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);

	// Override any settings.
	rParams.pszClassName  = "FrameWnd";
	rParams.pszTitle      = pApp->m_strTitle;
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
		
		// Menu item selected.
		case WM_MENUSELECT:
			OnSelectMenu(HIWORD(wParam), LOWORD(wParam), (HMENU)lParam);
			break;

		// Can Windows terminate?
		case WM_QUERYENDSESSION:
			if (OnQueryClose())
				break;
			else
				return 0;

		// Application requesting termination.
		case WM_CLOSE:
			if (OnQueryClose())
			{
				// Detach menu.
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

	m_bMsgHandled = true;
	m_lMsgResult  = 0;

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
** Method:		OnSelectMenu()
**
** Description:	Decode the menu item being shown and display a hint for it. The
**				strings IDs are the same as the item IDs, except for popup
**				menus where they are a multiple of 25; in which case it looks
**				as the first item to determine the hint ID.
**
** Parameters:	iFlags		The menu item flags.
**				iItemID		The menu ID.
**				hMenu		The menu handle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::OnSelectMenu(uint iFlags, uint iItemID, HMENU hMenu)
{
	char* pszHint = "";

	// Is a popup?
	if (iFlags & MF_POPUP)
	{
		// Menu item selected?
		if (iFlags == 0xFFFF)
		{
			pszHint = "";
		}
		else if (iFlags & MF_SYSMENU)
		{
			pszHint = "System Menu";
		}
		else // Popup menu
		{
			hMenu = GetSubMenu(hMenu, iItemID);

			OnShowMenuPopupHint(hMenu);
			return;
		}
	}
	else // Menu item
	{
		// Is a separator
		if (iFlags & MF_SEPARATOR)
		{
			pszHint = "";
		}
		else // Menu item.
		{
			OnShowMenuItemHint(iItemID);
			return;
		}
	}
		
	// Show menu hint.
	if (m_pStatusBar)
		m_pStatusBar->Hint(pszHint);
}

/******************************************************************************
** Method:		OnShowMenuItemHint()
**
** Description:	Display a hint for the selected menu item. This method is
**				virtual and can be overriden.
**
** Parameters:	iItemID		The menu ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::OnShowMenuItemHint(uint iItemID)
{
	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp != NULL);

	// Show hint.
	if (m_pStatusBar)
		m_pStatusBar->Hint(pApp->m_rCmdControl.CmdHint(iItemID));
}

/******************************************************************************
** Method:		OnShowMenuPopupHint()
**
** Description:	Display a hint for the selected popup menu. This method is
**				virtual and can be overriden, by defualt it loads the hint from
**				resource file and displays it. It looks at the first item in
**				the submenu and uses modulo 10 to find the hint for it.
**
** Parameters:	hMenu		The menu handle
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFrameWnd::OnShowMenuPopupHint(HMENU hMenu)
{
	// Get ID of first item in menu.
	int iFirstID = GetMenuItemID(hMenu, 0);
    
    // Menu not empty?
    if (iFirstID != -1)
    {
		// The menu item ID is modulo 10.
		OnShowMenuItemHint(iFirstID - (iFirstID % 10));
	}
	else
	{
		// Show dummy hint.
		if (m_pStatusBar)
			m_pStatusBar->Hint("");
	}
}

/******************************************************************************
** Method:		OnQueryClose()
**
** Description:	Ask if the main window can close.
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

void CFrameWnd::OnActivateApp(bool bActivating)
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
	if (m_pAccel)
		return m_pAccel->Translate(m_hWnd, rMsg);

	// Try active modeless dialog next.

	return false;
}
