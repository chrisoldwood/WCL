/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATUSBARLABEL.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CStatusBarLabel class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StatusBarLabel.hpp"
#include "ScreenDC.hpp"
#include "App.hpp"

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

CStatusBarLabel::CStatusBarLabel(size_t nChars)
	: m_nChars(nChars)
	, m_strLabel()
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

CStatusBarLabel::~CStatusBarLabel()
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

void CStatusBarLabel::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CStatusBarPanel::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
	rParams.lpszClassName = TXT("StatusBarLabel");
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

void CStatusBarLabel::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CStatusBarPanel::GetCreateParams(rParams);

    // Get the height of the default font.
    CScreenDC DC;

    DC.Select(CApp::This().DefaultFont());
    CSize FontSize = DC.TextExtents(TXT("Ly"));

	int count  = static_cast<int>(m_nChars);
	int right  = ((FontSize.cx*count)/2) + (2*BORDER_SIZE);
	int bottom = FontSize.cy + (2*BORDER_SIZE);

	// Override any settings.
	rParams.pszClassName = TXT("StatusBarLabel");
	rParams.rcPos.Set(0, 0, right, bottom);
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the panel border.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBarLabel::OnPaint(CDC& rDC)
{
	// Draw the label.
	rDC.Select(CApp::This().DefaultFont());
	rDC.TextColour(GetSysColor(COLOR_BTNTEXT));
	rDC.BkMode(TRANSPARENT);

	rDC.TextOut(BORDER_SIZE, BORDER_SIZE, m_strLabel);

	// Draw border last.
	CStatusBarPanel::OnPaint(rDC);
}

/******************************************************************************
** Method:		SetLabel()
**
** Description:	Set the label.
**
** Parameters:	pszLabel	The label.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBarLabel::SetLabel(const tchar* pszLabel)
{
	ASSERT(pszLabel != NULL);

	m_strLabel = pszLabel;

	// Repaint, if created.
	if (m_hWnd != NULL)
		Invalidate();
}
