/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EDITBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CEditBox class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CEditBox::CEditBox()
	: m_pFilter(NULL)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	Free up resources.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CEditBox::~CEditBox()
{
	// Free character filter.
	if (m_pFilter != NULL)
		delete[] m_pFilter;
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

void CEditBox::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = "EDIT";
	rParams.dwStyle     |= ES_MULTILINE | ES_AUTOVSCROLL | ES_LEFT | WS_VSCROLL;
}

/******************************************************************************
** Method:		WndProc()
**
** Description:	Catch WM_CHAR messages and filter the characters, if required.
**				
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CEditBox::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Decode message.
	switch(iMsg)
	{
		// Key pressed.
		case WM_CHAR:
//			TRACE1("%#08X\n", wParam);

			// Check filter.
			if (FilterKey((char)(wParam & 0xFF)))
			{
				// Consume message.
				m_bMsgHandled = true;
				m_lMsgResult  = 0;
				return 0;
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

void CEditBox::OnReflectedCtrlMsg(uint iMsg)
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

/******************************************************************************
** Method:		Filter()
**
** Description:	Sets up the list of valid characters that can be entered into
**				the edit box.
**
** Parameters:	pszFilter	The array of valid characters.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CEditBox::Filter(const char* pszFilter)
{
	ASSERT(pszFilter != NULL);

	// Allocate the filter array.
	m_pFilter = new bool[256];

	// Initialise to all invalid.
	memset(m_pFilter, false, sizeof(bool) * 256);

	// Make valid all chars in the filter.
	while (*pszFilter != '\0')
		m_pFilter[*pszFilter++] = true;

	// Allow Backspace key as well.
	m_pFilter[8] = true;
}

/******************************************************************************
** Method:		FilterKey()
**
** Description:	Called on WM_CHAR to determine if the the keystroke should be
**				allowed or not.
**
** Parameters:	cChar	The character to test.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CEditBox::FilterKey(char cChar)
{
	// Filter set AND key disallowed?
	return ( (m_pFilter != NULL) && (m_pFilter[cChar] == false) );
}
