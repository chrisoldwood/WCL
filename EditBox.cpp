/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EDITBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CEditBox class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "EditBox.hpp"

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
				MsgHandled(true);
				MsgResult (0);
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

void CEditBox::OnReflectedCtrlMsg(uint /*iMsg*/)
{
}

/******************************************************************************
** Method:		SetFilterDefault()
**
** Description:	Sets the default mapping for the character filter.
**
** Parameters:	bAllow		Allow all characters by default?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CEditBox::SetFilterDefault(bool bAllow)
{
	AllocFilterMap();

	// Re-initialise map.
	memset(m_pFilter, bAllow, sizeof(bool) * 256);
}

/******************************************************************************
** Method:		Filter()
**
** Description:	Sets up the character filter or modifies the existing one.
**
** Parameters:	pszFilter	The array of characters.
**				bAllow		Allow or disallow these characters.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CEditBox::Filter(const char* pszFilter, bool bAllow)
{
	ASSERT(pszFilter != NULL);

	AllocFilterMap();

	// Make valid all chars in the filter.
	while (*pszFilter != '\0')
		m_pFilter[*pszFilter++] = bAllow;
}

/******************************************************************************
** Method:		Filter()
**
** Description:	Sets up a single character filter or modifies an existing one.
**
** Parameters:	cFilter		The character.
**				bAllow		Allow or disallow the character.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CEditBox::Filter(char cFilter, bool bAllow)
{
	AllocFilterMap();

	m_pFilter[cFilter] = bAllow;
}

/******************************************************************************
** Method:		AllocFilterMap()
**
** Description:	Ensures the filter map is allocated and initialised.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CEditBox::AllocFilterMap()
{
	// Not already allocated?
	if (m_pFilter == NULL)
	{
		// Allocate the filter map.
		m_pFilter = new bool[256];

		// Initialise to all invalid.
		memset(m_pFilter, false, sizeof(bool) * 256);

		// Always allow Backspace.
		m_pFilter[8] = true;
	}
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

/******************************************************************************
** Method:		Append()
**
** Description:	Appends text to the edit box.
**
** Parameters:	pszText		The text to append.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CEditBox::Append(const char* pszText)
{
	int n = TextLength();

	Select(n, n);
	ReplaceSel(pszText, false);
}
