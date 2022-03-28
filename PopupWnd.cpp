/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		POPUPWND.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPopupWnd class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "PopupWnd.hpp"
#include "Module.hpp"
#include "Exception.hpp"
#include "StatusBar.hpp"
#include "App.hpp"
#include "FrameWnd.hpp"
#include "CmdCtrl.hpp"

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) // GCC 4.2+
// missing initializer for member 'X'
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Does nothing.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPopupWnd::CPopupWnd()
	: m_lpfnOldWndProc(nullptr)
{
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

void CPopupWnd::GetClassParams(WNDCLASS& rParams)
{
	// Fill in default WNDCLASS members.
	rParams.style         = CS_HREDRAW | CS_VREDRAW;
	rParams.lpfnWndProc   = DefWindowProc;
	rParams.cbClsExtra    = 0;
	rParams.cbWndExtra    = 0;
	rParams.hInstance     = CModule::This().Handle();
	rParams.hIcon         = NULL;
	rParams.hCursor       =::LoadCursor(NULL, IDC_ARROW);
	rParams.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	rParams.lpszMenuName  = nullptr;
	rParams.lpszClassName = nullptr;
}

/******************************************************************************
** Method:		Register()
**
** Description:	Registers the "window class" of a CPopupWnd derived window. It
**				checks first to see if the class is registered so that it can
**				be called by any instance of the object.
**
** Parameters:	rParams		The class parameters.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPopupWnd::Register(WNDCLASS& rParams)
{
	WNDCLASS	wcPrev;

	ASSERT(rParams.lpfnWndProc);
	ASSERT(rParams.hInstance);
	ASSERT(rParams.hbrBackground);
	ASSERT(rParams.lpszClassName);

	// Is already registered?
	if (GetClassInfo(rParams.hInstance, rParams.lpszClassName, &wcPrev))
		return true;

	// Do it.
	return ::RegisterClass(&rParams);
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

void CPopupWnd::GetCreateParams(WNDCREATE& rParams)
{
	// Fill in default WNDINIT members.
	rParams.dwExStyle     = 0;
	rParams.pszClassName  = nullptr;
	rParams.pszTitle      = nullptr;
	rParams.dwStyle       = 0;
	rParams.rcPos.Set(CW_USEDEFAULT, 0, 0, 0);
	rParams.hParent       = NULL;
	rParams.hMenu         = NULL;
	rParams.lpCreation    = nullptr;
}

/******************************************************************************
** Method:		Create()
**
** Description:	Template method used to actually create the window.
**
** Parameters:	rCreate		The create window parameters.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPopupWnd::Create(WNDCREATE& rCreate)
{
	// Now create it.
	m_hWnd = ::CreateWindowEx(	rCreate.dwExStyle,
								rCreate.pszClassName,
								rCreate.pszTitle,
								rCreate.dwStyle,
								rCreate.rcPos.left,
								rCreate.rcPos.top,
								rCreate.rcPos.Width(),
								rCreate.rcPos.Height(),
								rCreate.hParent,
								rCreate.hMenu,
								CModule::This().Handle(),
								rCreate.lpCreation );
	ASSERT(m_hWnd);

	// Setup Window/Object mapping.
	CWnd::s_WndMap.Add(*this);

	// Change WndProc to our multi purpose one.
	m_lpfnOldWndProc = WindowProc(PopupWndProc);

	// Initialise.
	OnCreate(ClientRect());

	return (m_hWnd != NULL);
}

/******************************************************************************
** Method:		Create()
**
** Description:	Calls the template methods to create the window.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPopupWnd::Create()
{
	ASSERT(m_hWnd == NULL);

	// Register the class.
	WNDCLASS WndClass;

	GetClassParams(WndClass);
	if (!Register(WndClass))
		return false;

	// Create the window.
	WNDCREATE WndCreate = { 0 };

	GetCreateParams(WndCreate);
	return Create(WndCreate);
}

/******************************************************************************
** Method:		Create()
**
** Description:	Calls the template methods to create the window, overriding
**				the styles with the ones passed in.
**
** Parameters:	dwExStyle	The extended styles.
**				dwStyle		The styles.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPopupWnd::Create(DWORD dwExStyle, DWORD dwStyle)
{
	ASSERT(m_hWnd == NULL);

	// Register the class.
	WNDCLASS WndClass;

	GetClassParams(WndClass);
	if (!Register(WndClass))
		return false;

	// Create the window.
	WNDCREATE WndCreate;

	GetCreateParams(WndCreate);

	WndCreate.dwExStyle = dwExStyle;
	WndCreate.dwStyle   = dwStyle;

	return Create(WndCreate);
}

#if (__GNUC__ >= 8) // GCC 8+
// error: format '%hs' expects argument of type 'short int*', but argument 3 has type 'const char*' [-Werror=format=]
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif

/******************************************************************************
** Function:	PopupWndProc()
**
** Description:	This is the real CPopupWnd based window message procedure. It
**				works out which object belongs to the window handle and passes
**				the message straight onto that object for processing.
**
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message
**
*******************************************************************************
*/

LRESULT WINDOWPROC CPopupWnd::PopupWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Store the return values for this message.
	BOOL    bMsgHandled = false;
	LRESULT lMsgResult  = 0;

	try
	{
		CPopupWnd* pWnd;

		// Get the window object.
		pWnd = static_cast<CPopupWnd*>(CWnd::s_WndMap.Find(hWnd));
		ASSERT(pWnd);

		//
		// This function can be called recursively so we need to use
		// the program stack to hold the return values for each
		// message whilst it is being processed.
		//

		// Push the existing messages' return values onto the stack.
		BOOL*	 pbMsgHandled = pWnd->MsgHandledBuffer(&bMsgHandled);
		LRESULT* plMsgResult  = pWnd->MsgResultBuffer (&lMsgResult);

		// Call real message handler.
		pWnd->WndProc(hWnd, iMsg, wParam, lParam);

		// Pop the old messages' return values back off the stack.
		pWnd->MsgHandledBuffer(pbMsgHandled);
		pWnd->MsgResultBuffer (plMsgResult);
	}
	catch (const Core::Exception& e)
	{
		WCL::ReportUnhandledException(	TXT("Unexpected exception caught in PopupWndProc()\n\n")
										TXT("Message: H=0x%p M=0x%08X W=0x%08X L=0x%08lX\n\n%s"),
										hWnd, iMsg, wParam, lParam, e.twhat());
	}
	catch (const std::exception& e)
	{
		WCL::ReportUnhandledException(	TXT("Unexpected exception caught in PopupWndProc()\n\n")
										TXT("Message: H=0x%p M=0x%08X W=0x%08X L=0x%08lX\n\n%hs"),
										hWnd, iMsg, wParam, lParam, e.what());
	}
	catch (...)
	{
		WCL::ReportUnhandledException(	TXT("Unexpected unknown exception caught in PopupWndProc()\n\n")
										TXT("Message: H=0x%p M=0x%08X W=0x%08X L=0x%08lX"),
										hWnd, iMsg, wParam, lParam);
	}

	return lMsgResult;
}

#if (__GNUC__ >= 8) // GCC 8+
#pragma GCC diagnostic pop
#endif

/******************************************************************************
** Method:		WndProc()
**
** Description:	This is the base implementation of a CPopupWnd window message
**				handler. It handles all messages common to all pop-up windows.
**				This is a virtual function and is overridden by derived classes
**				to farm out more specific messages, but should always be called
**				by derived classes to get the default processing.
**
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CPopupWnd::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Decode message.
	switch(iMsg)
	{
		// Window (de)activated.
		case WM_ACTIVATE:
			OnActivate(wParam != WA_INACTIVE);
			break;

		// Window gained the focus.
		case WM_SETFOCUS:
			OnFocus();
			break;

		// Window lost the focus.
		case WM_KILLFOCUS:
			OnFocusLost();
			break;

        // Left button pressed.
		case WM_LBUTTONDOWN:
			OnLeftButtonDown(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), static_cast<WCL::KeyFlags>(wParam));
			break;

        // Left button released.
		case WM_LBUTTONUP:
			OnLeftButtonUp(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), static_cast<WCL::KeyFlags>(wParam));
			break;

        // Left button double clicked.
		case WM_LBUTTONDBLCLK:
			OnLeftButtonDblClick(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), static_cast<WCL::KeyFlags>(wParam));
			break;

        // Right button pressed.
		case WM_RBUTTONDOWN:
			OnRightButtonDown(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), static_cast<WCL::KeyFlags>(wParam));
			break;

        // Right button released.
		case WM_RBUTTONUP:
			OnRightButtonUp(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), static_cast<WCL::KeyFlags>(wParam));
			break;

        // Right button double clicked.
		case WM_RBUTTONDBLCLK:
			OnRightButtonDblClick(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), static_cast<WCL::KeyFlags>(wParam));
			break;

		// Mouse moved.
		case WM_MOUSEMOVE:
			OnMouseMove(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), static_cast<WCL::KeyFlags>(wParam));
			break;

		// Key pressed.
		case WM_KEYDOWN:
			OnKeyDown(static_cast<WCL::KeyCode>(wParam), static_cast<WCL::KeyState>(lParam));
			break;

		// Key released.
		case WM_KEYUP:
			OnKeyUp(static_cast<WCL::KeyCode>(wParam), static_cast<WCL::KeyState>(lParam));
			break;

		// Translated WM_KEYDOWN/UP.
		case WM_CHAR:
			OnChar(static_cast<WCL::KeyCode>(wParam), static_cast<WCL::KeyState>(lParam));
			break;

		// Menu item selected.
		case WM_MENUSELECT:
			OnSelectMenu(HIWORD(wParam), LOWORD(wParam), reinterpret_cast<HMENU>(lParam));
			break;

		// Mouse capture lost.
		case WM_CAPTURECHANGED:
			OnCaptureChanged();
			break;

		// Window being destroyed.
		case WM_NCDESTROY:
			// Restore WndProc.
			WindowProc(m_lpfnOldWndProc);

			OnNCDestroy();
			break;

		// Call the default handler.
		default:
			return CMsgWnd::WndProc(hWnd, iMsg, wParam, lParam);
	}

	MsgHandled(true);
	MsgResult (0);

	return 0;
}

/******************************************************************************
** Method:		DefaultWndProc()
**
** Description:	This is the handler for all non-handled messages. It calls
**				DefWindowProc().
**
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CPopupWnd::DefaultWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	MsgHandled(true);
	MsgResult (DefWindowProc(hWnd, iMsg, wParam, lParam));

	return 0;
}

/******************************************************************************
** Method:		OnActivate()
**
** Description:	The window has been activated or deactivated.
**
** Parameters:	bActivating		Window being activated or deactivated?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupWnd::OnActivate(bool /*bActivating*/)
{
}

/******************************************************************************
** Method:		OnFocus()
**
** Description:	Window has gained the focus.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupWnd::OnFocus()
{
}

/******************************************************************************
** Method:		OnFocusLost()
**
** Description:	Window has lost the focus.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupWnd::OnFocusLost()
{
}

/******************************************************************************
** Methods:		OnLeftButtonDown()
**				OnLeftButtonUp()
**				OnLeftButtonDblClick()
**				OnRightButtonDown()
**				OnRightButtonUp()
**				OnRightButtonDblClick()
**				OnMouseMove()
**
** Description:	Mouse state messages. By default all do nothing.
**
** Parameters:	ptCursor	Mouse position.
**				iKeyFlags	State of control keys.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupWnd::OnLeftButtonDown(const CPoint& /*ptCursor*/, WCL::KeyFlags /*iKeyFlags*/)
{
}

void CPopupWnd::OnLeftButtonUp(const CPoint& /*ptCursor*/, WCL::KeyFlags /*iKeyFlags*/)
{
}

void CPopupWnd::OnLeftButtonDblClick(const CPoint& /*ptCursor*/, WCL::KeyFlags /*iKeyFlags*/)
{
}

void CPopupWnd::OnRightButtonDown(const CPoint& /*ptCursor*/, WCL::KeyFlags /*iKeyFlags*/)
{
}

void CPopupWnd::OnRightButtonUp(const CPoint& /*ptCursor*/, WCL::KeyFlags /*iKeyFlags*/)
{
}

void CPopupWnd::OnRightButtonDblClick(const CPoint& /*ptCursor*/, WCL::KeyFlags /*iKeyFlags*/)
{
}

void CPopupWnd::OnMouseMove(const CPoint& /*ptCursor*/, WCL::KeyFlags /*iKeyFlags*/)
{
}

/******************************************************************************
** Methods:		OnKeyDown()
**				OnKeyUp()
**				OnChar()
**
** Description:	Keyboard state messages. By default all do nothing.
**
** Parameters:	wKey		The keys' vitual keycode.
**				dwFlags		Key state information.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupWnd::OnKeyDown(WCL::KeyCode /*wKey*/, WCL::KeyState /*dwFlags*/)
{
}

void CPopupWnd::OnKeyUp(WCL::KeyCode /*wKey*/, WCL::KeyState /*dwFlags*/)
{
}

void CPopupWnd::OnChar(WCL::KeyCode /*wKey*/, WCL::KeyState /*dwFlags*/)
{
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

void CPopupWnd::OnSelectMenu(uint iFlags, uint iItemID, HMENU hMenu)
{
	// Is a popup menu?
	if (iFlags & MF_POPUP)
	{
		// Menu item selected?
		if (iFlags == 0xFFFF)
		{
			OnShowDefaultMenuHint();
		}
		// System popup menu?
		else if (iFlags & MF_SYSMENU)
		{
			OnShowSystemMenuHint();
		}
		// Popup menu.
		else
		{
			OnShowMenuPopupHint(GetSubMenu(hMenu, iItemID));
		}
	}
	// Menu item.
	else
	{
		// Is a separator?
		if (iFlags & MF_SEPARATOR)
		{
			OnShowDefaultMenuHint();
		}
		// Menu item.
		else
		{
			OnShowMenuItemHint(iItemID);
		}
	}
}


/******************************************************************************
** Method:		OnShowMenuItemHint()
**
** Description:	Display a hint for the selected menu item. This method is
**				virtual and can be overridden.
**
** Parameters:	iItemID		The menu ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupWnd::OnShowMenuItemHint(uint iItemID)
{
	// Get the applications status bar.
	CStatusBar* pStatusBar = CApp::This().m_rMainWnd.StatusBar();

	// Display hint from command controller.
	if (pStatusBar)
		pStatusBar->Hint(CApp::This().m_controller.CmdHintStr(iItemID));
}

/******************************************************************************
** Method:		OnShowMenuPopupHint()
**
** Description:	Display a hint for the selected pop-up menu. This method is
**				virtual and can be overridden, by default it loads the hint from
**				resource file and displays it. It looks at the first item in
**				the sub-menu and uses modulo 10 to find the hint for it.
**
** Parameters:	hMenu		The menu handle
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupWnd::OnShowMenuPopupHint(HMENU hMenu)
{
	// Get ID of first item in menu.
	int iFirstID = GetMenuItemID(hMenu, 0);

    // Menu not empty?
    if (iFirstID != -1)
		OnShowMenuItemHint(iFirstID - (iFirstID % 10));
	else
		OnShowDefaultMenuHint();
}

/******************************************************************************
** Method:		OnShowSystemMenuHint()
**
** Description:	Displays a hint for the system popup menu.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupWnd::OnShowSystemMenuHint()
{
	// Get the applications status bar.
	CStatusBar* pStatusBar = CApp::This().m_rMainWnd.StatusBar();

	// Display hint.
	if (pStatusBar != nullptr)
		pStatusBar->Hint(TXT("System Menu"));
}

/******************************************************************************
** Method:		OnShowDefaultMenuHint()
**
** Description:	Displays the default menu hint. This is used when over a
**				separator or empty popup menu.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPopupWnd::OnShowDefaultMenuHint()
{
	// Get the applications status bar.
	CStatusBar* pStatusBar = CApp::This().m_rMainWnd.StatusBar();

	// Remove previous hint.
	if (pStatusBar != nullptr)
		pStatusBar->Hint(TXT(""));
}

////////////////////////////////////////////////////////////////////////////////
//! Mouse capture lost.

void CPopupWnd::OnCaptureChanged()
{
}
