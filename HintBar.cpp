/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		HINTBAR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CHintBar class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Override any default settings for the window class and style.
**
** Parameters:	rParent		The windows parent.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CHintBar::CHintBar()
{
	// Clear hint.
	m_szHint[0] = '\0';
}

/******************************************************************************
** Method:		GetClassParams()
**
** Description:	Template method to get the window class data.
**
** Parameters:	rParams		The class structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CHintBar::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	rParams.lpszClassName = "HintBar";
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

void CHintBar::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName  = "HintBar";
}

/******************************************************************************
** Method:		Hint()
**
** Description:	Set the current hint and display it if changed.
**
** Parameters:	iRscID		The hints' resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CHintBar::Hint(uint iRscID)
{
	CString strHint(iRscID);
	Hint(strHint);
}

/******************************************************************************
** Method:		Hint()
**
** Description:	Set the current hint and display it if changed.
**
** Parameters:	pszHint		The hint.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CHintBar::Hint(const char* pszHint)
{
	ASSERT(pszHint);

	// Hint different?
	if (lstrcmp(pszHint, (LPCSTR)m_szHint) == 0)
		return;
		
	// Save it.
	lstrcpy(m_szHint, pszHint);

	// Redraw bar.
	Invalidate();
	Update();
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the hint window 3D border and hint.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CHintBar::OnPaint(CDC& rDC)
{
	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);

	// Draw the hint.
	rDC.Select(pApp->DefaultFont());
	rDC.TextColour(GetSysColor(COLOR_BTNTEXT));
	rDC.BkMode(TRANSPARENT);
	rDC.TextOut(2, 0, (const char*)m_szHint);
}
