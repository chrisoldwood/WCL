/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		POPUPWND.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPopupWnd class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

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
	: m_lpfnOldWndProc(NULL)
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
	rParams.hCursor       = ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	rParams.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	rParams.lpszMenuName  = NULL;
	rParams.lpszClassName = NULL;
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
	rParams.pszClassName  = NULL;
	rParams.pszTitle      = NULL;
	rParams.dwStyle       = 0;
	rParams.rcPos.Set(CW_USEDEFAULT, 0, 0, 0);
	rParams.hParent       = NULL;
	rParams.hMenu         = NULL;
	rParams.lpCreation    = NULL;
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
	m_lpfnOldWndProc = WindowProc(::PopupWndProc);

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
	WNDCREATE WndCreate;

	GetCreateParams(WndCreate);
	return Create(WndCreate);
}

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

LRESULT WINDOWPROC PopupWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	CPopupWnd* pWnd;
	
	// Get the window object.
	pWnd = (CPopupWnd*) CWnd::s_WndMap.Find(hWnd);
	ASSERT(pWnd);

	//
	// This function can be called recursively so we need to use
	// the program stack to hold the return values for each
	// message whilst it is being precessed.
	//

	// Store the return values for this message.
	BOOL     bMsgHandled = false;
	LRESULT  lMsgResult  = 0;

	// Push the existing messages' return values onto the stack.
	BOOL*	 pbMsgHandled = pWnd->MsgHandledBuffer(&bMsgHandled);
	LRESULT* plMsgResult  = pWnd->MsgResultBuffer (&lMsgResult);
	
	// Call real message handler.
	pWnd->WndProc(hWnd, iMsg, wParam, lParam);

	// Pop the old messages' return values back off the stack.
	pWnd->MsgHandledBuffer(pbMsgHandled);
	pWnd->MsgResultBuffer (plMsgResult);

	return lMsgResult;
}

/******************************************************************************
** Method:		WndProc()
**
** Description:	This is the base implementation of a CPopupWnd window message
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
			OnLeftButtonDown(CPoint(LOWORD(lParam), HIWORD(lParam)), wParam);
			break;

        // Left button released.
		case WM_LBUTTONUP:
			OnLeftButtonUp(CPoint(LOWORD(lParam), HIWORD(lParam)), wParam);
			break;
		
        // Left button double clicked.
		case WM_LBUTTONDBLCLK:
			OnLeftButtonDblClick(CPoint(LOWORD(lParam), HIWORD(lParam)), wParam);
			break;

        // Right button pressed.
		case WM_RBUTTONDOWN:
			OnRightButtonDown(CPoint(LOWORD(lParam), HIWORD(lParam)), wParam);
			break;

        // Right button released.
		case WM_RBUTTONUP:
			OnRightButtonUp(CPoint(LOWORD(lParam), HIWORD(lParam)), wParam);
			break;
		
        // Right button double clicked.
		case WM_RBUTTONDBLCLK:
			OnRightButtonDblClick(CPoint(LOWORD(lParam), HIWORD(lParam)), wParam);
			break;
		
		// Mouse moved.
		case WM_MOUSEMOVE:
			OnMouseMove(CPoint(LOWORD(lParam), HIWORD(lParam)), wParam);
			break;
		
		// Key pressed.
		case WM_KEYDOWN:
			OnKeyDown((WORD)wParam, lParam);
			break;
		
		// Key released.
		case WM_KEYUP:
			OnKeyUp((WORD)wParam, lParam);
			break;

		// Translated WM_KEYDOWN/UP.
		case WM_CHAR:
			OnChar((WORD)wParam, lParam);
			break;

		// Window being destroyed.
		case WM_NCDESTROY:
			// Restore WndProc.
			WindowProc(m_lpfnOldWndProc);
			
			// Delete object mapping.
			CWnd::s_WndMap.Remove(*this);
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

void CPopupWnd::OnActivate(bool bActivating)
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

void CPopupWnd::OnLeftButtonDown(const CPoint& ptCursor, uint iKeyFlags)
{
}

void CPopupWnd::OnLeftButtonUp(const CPoint& ptCursor, uint iKeyFlags)
{
}

void CPopupWnd::OnLeftButtonDblClick(const CPoint& ptCursor, uint iKeyFlags)
{
}

void CPopupWnd::OnRightButtonDown(const CPoint& ptCursor, uint iKeyFlags)
{
}

void CPopupWnd::OnRightButtonUp(const CPoint& ptCursor, uint iKeyFlags)
{
}

void CPopupWnd::OnRightButtonDblClick(const CPoint& ptCursor, uint iKeyFlags)
{
}

void CPopupWnd::OnMouseMove(const CPoint& ptCursor, uint iKeyFlags)
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

void CPopupWnd::OnKeyDown(WORD wKey, DWORD dwFlags)
{
}

void CPopupWnd::OnKeyUp(WORD wKey, DWORD dwFlags)
{
}

void CPopupWnd::OnChar(WORD wKey, DWORD dwFlags)
{
}
