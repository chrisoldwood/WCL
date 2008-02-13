/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LISTBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CListBox class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ListBox.hpp"

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
** Parameters:	nItem	The item.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CListBox::Text(size_t nItem) const
{
	CString	strText;

	// Allocate space.
	strText.BufferSize(TextLength(nItem)+1);

	ListBox_GetText(m_hWnd, nItem, strText.Buffer());

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
	rParams.pszClassName = TXT("LISTBOX");
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

/******************************************************************************
** Methods:		RestoreSel()
**
** Description:	Restores the selection provided. If there was no selection,
**				then it selects the first item. If the item no longer exists,
**				it sets it to the last item.
**
** Parameters:	nItem	The item to select, or LB_ERR, if there was none.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListBox::RestoreSel(size_t nItem) const
{
	size_t nCount = Count();

	// Handle no selection, or invalid selection.
	nItem = (nItem == Core::npos) ? 0 : nItem;
	nItem = (nItem >= nCount) ? (nCount-1) : nItem;

	CurSel(nItem);
}
