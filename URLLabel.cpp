/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		URLLABEL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CURLLabel class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "URLLabel.hpp"

/******************************************************************************
** Only available for Win98 and Win2K upwards.
*/

#ifndef	IDC_HAND
#define IDC_HAND	MAKEINTRESOURCE(32649)
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

CURLLabel::CURLLabel()
	: m_strProtocol()
	, m_oCursor()
	, m_oFont()
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

CURLLabel::~CURLLabel()
{
}

/******************************************************************************
** Method:		WndProc()
**
** Description:	Catch messages required to implememt hyperlink behaviour.
**
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CURLLabel::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Decode message.
	switch(iMsg)
	{
		// Set cursor.
		case WM_SETCURSOR:
			OnSetCursor(reinterpret_cast<HWND>(wParam), LOWORD(lParam), HIWORD(lParam));

			// Consume message.
			MsgHandled(true);
			MsgResult (TRUE);
			return 0;

		// Left mouse click.
		case WM_LBUTTONDOWN:
			OnClick();
			break;

		// Call the default handler.
		default:
			break;
	}

	// Call the base class' handler.
	return CStdWnd::WndProc(hWnd, iMsg, wParam, lParam);
}

/******************************************************************************
** Method:		OnSetCursor()
**
** Description:	Set the cursor for the given window.
**
** Parameters:	hWnd		The window requiring a cursor.
**				nHitCode	The HTXXX hit test code.
**				nMouseMsg	The WM_* mouse message that generated the event.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CURLLabel::OnSetCursor(HWND /*hWnd*/, uint /*nHitCode*/, uint /*nMouseMsg*/)
{
	// Hand cursor needs loading?
	if (m_oCursor.Handle() == NULL)
		m_oCursor.LoadRsc(IDC_HAND);

	// Fall back to up arrow, if hand not supported.
	if (m_oCursor.Handle() == NULL)
		m_oCursor.LoadRsc(IDC_UPARROW);

	::SetCursor(m_oCursor.Handle());
}

/******************************************************************************
** Method:		OnClick()
**
** Description:	The user clicked the control.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CURLLabel::OnClick()
{
	// Window title is URL.
	CString strURL = Title();

	// Invokr shell to handle the comamnd.
	::ShellExecute(NULL, NULL, m_strProtocol + strURL, NULL, NULL, SW_SHOW);
}

/******************************************************************************
** Method:		OnReflectedCtlClr()
**
** Description:	Setup the DC to paint the hyperlink in standard font/colours.
**
** Parameters:	nCtlClrMsg	The WM_CTLCOLOR* message,
**				hDC			The drawing HDC.
**
** Returns:		See WM_CTLCOLOR*.
**
*******************************************************************************
*/

HBRUSH CURLLabel::OnReflectedCtlClr(uint /*nCtlClrMsg*/, HDC hDC)
{
	// Created underlined font, if not already.
	if (m_oFont.Handle() == NULL)
	{
        CLogFont oLogFont(Font().Handle());

        oLogFont.lfUnderline = TRUE;

		m_oFont.Create(oLogFont);
	}

	// Setup DC.
	::SelectObject(hDC, m_oFont.Handle());
	::SetTextColor(hDC, RGB(0,0,255));
	::SetBkMode(hDC, TRANSPARENT);

	return GetStockBrush(HOLLOW_BRUSH);
}
