/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WND.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CWnd class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Wnd.hpp"
#include <stdio.h>
#include <stdarg.h>
#include "App.hpp"

/******************************************************************************
**
** Class variables.
**
*******************************************************************************
*/

// Handle <-> Window map.
CWndMap CWnd::s_WndMap;

// Desktop window.
CWnd CWnd::g_oDesktop;

/******************************************************************************
** Method:		WindowRect()
**
** Description:	Get the rect describing the windows outer border relative to
**				the screen.
**
** Parameters:	None.
**
** Returns:		The rect.
**
*******************************************************************************
*/

CRect CWnd::WindowRect() const
{
	CRect rcWnd;

	::GetWindowRect(m_hWnd, &rcWnd);

	return rcWnd;
}

/******************************************************************************
** Method:		ClientRect()
**
** Description:	Get the position of the client area of the window, for child
**				windows the top-left corner will always be 0,0. This is
**				virtual and should be overridden by frame windows to account for
**				tool-bars etc.
**
** Parameters:	None.
**
** Returns:		The rect.
**
*******************************************************************************
*/

CRect CWnd::ClientRect() const
{
	CRect rcClient;

	::GetClientRect(m_hWnd, &rcClient);

	return rcClient;
}

/******************************************************************************
** Method:		ChildRect()
**
** Description:	Get the rect describing the windows border relative to this
**				window.
**
** Parameters:	None.
**
** Returns:		The rect.
**
*******************************************************************************
*/

CRect CWnd::ChildRect(const CWnd& rWnd) const
{
	// Get position relative to the screen.
	CRect rcWnd = rWnd.WindowRect();

	// Convert to relative to this window.
	::MapWindowPoints(NULL, m_hWnd, reinterpret_cast<LPPOINT>(&rcWnd), 2);

	return rcWnd;
}

/******************************************************************************
** Method:		Placement()
**
** Description:	Get the rect describing the windows normal placement.
**
** Parameters:	None.
**
** Returns:		The rect.
**
*******************************************************************************
*/

CRect CWnd::Placement() const
{
	WINDOWPLACEMENT oRects;

	memset(&oRects, 0, sizeof(oRects));
	oRects.length = sizeof(oRects);

	// Get placement.
	::GetWindowPlacement(m_hWnd, &oRects);

	return oRects.rcNormalPosition;
}

/******************************************************************************
** Method:		Centre()
**
** Description:	Centre the window on its parent.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWnd::Centre()
{
	HWND	hParent;
	CRect	rcThis;
	CSize	dmThis;
	CRect	rcParent;
	CPoint	ptOrigin;

	// Get parent, use desktop, if none.
	hParent = GetParent(m_hWnd);
	if (!hParent)
		hParent = GetDesktopWindow();

	// Get the window dimensions.
	::GetWindowRect(hParent, &rcParent);
	rcThis = WindowRect();
	dmThis = rcThis.Size();

	// Calculate new origin.
	ptOrigin.x = ((rcParent.Width()  - dmThis.cx) / 2 ) + rcParent.left;
	ptOrigin.y = ((rcParent.Height() - dmThis.cy) / 2 ) + rcParent.top;

	// Move it
	Move(CRect(ptOrigin, dmThis));
}

/******************************************************************************
** Methods:		AlertMsg()
**				NotifyMsg()
**				QueryMsg()
**				FatalMsg()
**
** Description:	Displays a message box linked to the window.
**
** Parameters:	pszMsg			The message format.
**				...				Variable number of arguments.
**
** Returns:		Result from MessageBox() if appropriate.
**
*******************************************************************************
*/

int CWnd::AlertMsg(const tchar* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);

	// Format message.
	strMsg.FormatEx(pszMsg, args);

	return MessageBox(m_hWnd, strMsg, CApp::This().m_strTitle, MB_OK | MB_ICONEXCLAMATION);
}

int CWnd::NotifyMsg(const tchar* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);

	// Format message.
	strMsg.FormatEx(pszMsg, args);

	return MessageBox(m_hWnd, strMsg, CApp::This().m_strTitle, MB_OK | MB_ICONINFORMATION);
}

int CWnd::QueryMsg(const tchar* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);

	// Format message.
	strMsg.FormatEx(pszMsg, args);

	return MessageBox(m_hWnd, strMsg, CApp::This().m_strTitle, MB_YESNOCANCEL | MB_ICONQUESTION);
}

int CWnd::FatalMsg(const tchar* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);

	// Format message.
	strMsg.FormatEx(pszMsg, args);

	return MessageBox(m_hWnd, strMsg, CApp::This().m_strTitle, MB_OK | MB_ICONSTOP);
}

/******************************************************************************
** Methods:		Title()
**
** Description:	Get the title of the window as a string.
**
** Parameters:	None.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CWnd::Title() const
{
	CString	strText;

	// Get string length.
	size_t nChars = SendMessage(WM_GETTEXTLENGTH, 0, 0L);

	// Allocate space.
	strText.BufferSize(nChars+1);

	// Fetch string.
	SendMessage(WM_GETTEXT, nChars+1, reinterpret_cast<LPARAM>(strText.Buffer()));

	return strText;
}
