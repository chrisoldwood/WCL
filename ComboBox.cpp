/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		COMBOBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CComboBox class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ComboBox.hpp"

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
** Parameters:	nItem	The item.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CComboBox::Text(size_t nItem) const
{
	CString	strText;

	// Allocate space for string.
	strText.BufferSize(TextLength(nItem)+1);

	// Get string.
	ComboBox_GetLBText(m_hWnd, nItem, strText.Buffer());

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

	// Get string length.
	size_t nChars = TextLength();

	// Allocate space.
	strText.BufferSize(nChars+1);

	// Fetch string.
	ComboBox_GetText(m_hWnd, strText.Buffer(), nChars+1);

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
	rParams.pszClassName = TXT("COMBOX");
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

void CComboBox::OnReflectedCtrlMsg(uint /*iMsg*/)
{
}
