/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TABWNDHOST.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CTabWndHost class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CTabWndHost::CTabWndHost()
{
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

CTabWndHost::~CTabWndHost()
{
}

/******************************************************************************
** Method:		WndProc()
**
** Description:	Catch WM_SIZE and resize the child windows.
**				
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CTabWndHost::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Decode message.
	switch(iMsg)
	{
		// Key pressed.
		case WM_SIZE:
			{
				// Get the display area.
				CRect rcDisplay = DisplayRect();

				int nCurTab = CurSel();

				// Resize the currently displayed window.
				if (nCurTab != -1)
					TabWnd(nCurTab).Move(rcDisplay);
			}
			break;

		// Call the default handler.
		default:
			break;
	}

	// Call the base class' handler.
	return CStdWnd::WndProc(hWnd, iMsg, wParam, lParam);
}

/******************************************************************************
** Methods:		OnSelChanging()
**
** Description:	Hide the window associated with the currently selected tab.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTabWndHost::OnSelChanging()
{
	int nCurTab = CurSel();
	if (nCurTab == -1)
		return;

	// Hide current window.
	TabWnd(nCurTab).WindowPos(HWND_BOTTOM, false);
}

/******************************************************************************
** Methods:		OnSelChange()
**
** Description:	Show the window associated with the newly selected tab.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTabWndHost::OnSelChange()
{
	int nCurTab = CurSel();
	if (nCurTab == -1)
		return;

	CWnd& oWnd = TabWnd(nCurTab);

	// Resize and bring the window to the front.
	oWnd.WindowPos(HWND_TOP, DisplayRect(), true);
	oWnd.Focus();
}
