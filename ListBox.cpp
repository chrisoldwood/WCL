/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LISTBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CListBox class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Override any default settings for the window class and style.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CListBox::CListBox()
{
}

/******************************************************************************
** Method:		Text()
**
** Description:	Get the string for the specified item.
**
** Parameters:	iPos	The item.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CListBox::Text(int iPos) const
{
	CString	strText;

	// Allocate space.
	strText.BufferSize(TextLength(iPos)+1);

	SendMessage(LB_GETTEXT, iPos, (LPARAM)(LPCSTR) strText);

	return strText;
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

void CListBox::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = "LISTBOX";
	rParams.dwStyle     |= LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY;
	rParams.dwStyle     |= LBS_SORT | WS_VSCROLL;
}

/******************************************************************************
** Method:		OnReflectedCtrlMsg()
**
** Description:	Handle child messages reflected back from the parent.
**
** Parameters:	iMsg		Control message.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListBox::OnReflectedCtrlMsg(uint iMsg)
{
	// Decode message.
	switch(iMsg)
	{
		// Selection changed.
		case LBN_SELCHANGE:
			OnSelChange();
			break;

		// Unknown.
		default:
			break;
	}
}

/******************************************************************************
** Methods:		OnSelChange()
**
** Description:	Default implementation of reflected message handlers.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListBox::OnSelChange()
{
}
