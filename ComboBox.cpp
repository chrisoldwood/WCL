/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		COMBOBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CComboBox class methods.
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

CComboBox::CComboBox()
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

CString CComboBox::Text(int iPos) const
{
	CString	strText;

	// Allocate space for string.
	strText.BufferSize(TextLength(iPos)+1);

	// Get string.
	SendMessage(CB_GETLBTEXT, iPos, (LPARAM)(LPCSTR) strText);

	return strText;
}

/******************************************************************************
** Method:		Text()
**
** Description:	Get the string for edit box part of the control.
**
** Parameters:	None.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CComboBox::Text() const
{
	CString	strText;
	int		iLen;

	// Get string length.
	iLen = TextLength();

	// Allocate space.
	strText.BufferSize(iLen+1);

	// Fetch string.
	SendMessage(WM_GETTEXT, iLen+1, (LPARAM)(LPCSTR) strText);

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

void CComboBox::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = "COMBOX";
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

void CComboBox::OnReflectedCtrlMsg(uint iMsg)
{
/*
	// Decode message.
	switch(iMsg)
	{
		// Unknown.
		default:
			break;
	}
*/
}
