/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STDWND.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CStdWnd class methods.
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

CStdWnd::CStdWnd()
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	Cleanup resources.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStdWnd::~CStdWnd()
{
}

/******************************************************************************
** Method:		WndProc()
**
** Description:	This is the base implementation of sublassed controls' window
**				proc. By default it calls the original window proc, but listens
**				for WM_NCDESTROY to detach itself at destruction.
**				
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CStdWnd::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Decode message.
	switch(iMsg)
	{
		// Window being destroyed.
		case WM_NCDESTROY:
			// Restore WndProc.
			WindowProc(m_lpfnOldWndProc);
			
			// Delete object mapping.
			CWnd::s_WndMap.Remove(*this);
			break;

		// Call the default handler.
		default:
			break;
	}

	// Call the controls' real handler.
	m_bMsgHandled = false;
	m_lMsgResult  = ::CallWindowProc(m_lpfnOldWndProc, hWnd, iMsg, wParam, lParam);

	return 0;
}

/******************************************************************************
** Method:		Register()
**
** Description:	Standard controls are already registered.
**				
** Parameters:	rParams		The window class data.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CStdWnd::Register(WNDCLASS& rParams)
{
	return true;
}
