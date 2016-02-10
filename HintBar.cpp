/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		HINTBAR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CHintBar class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "HintBar.hpp"
#include "StatusBarPanel.hpp"
#include "DC.hpp"
#include "App.hpp"

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Width of border around child window content.
const int INNER_BORDER_SIZE = CStatusBarPanel::BORDER_SIZE;

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
	: m_strHint()
{
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
	rParams.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
	rParams.lpszClassName = TXT("HintBar");
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
	rParams.pszClassName  = TXT("HintBar");
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

void CHintBar::Hint(const tchar* pszHint)
{
	ASSERT(pszHint != nullptr);

	// Ignore, if same hint.
	if (m_strHint == pszHint)
		return;

	m_strHint = pszHint;

	// Redraw.
	Invalidate();
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
	// Draw the hint.
	rDC.Select(CApp::This().DefaultFont());
	rDC.TextColour(GetSysColor(COLOR_BTNTEXT));
	rDC.BkMode(TRANSPARENT);

	rDC.TextOut(INNER_BORDER_SIZE, INNER_BORDER_SIZE, m_strHint);
}
