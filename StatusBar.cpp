/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATUSBAR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CStatusBar class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

// Width of border around child windows.
#define BORDER_SIZE		3

/******************************************************************************
** Method:		Default constructor.
**
** Description:	.
**
** Parameters:	rParent		The windows parent.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStatusBar::CStatusBar()
	: m_pActive(NULL)
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

CStatusBar::~CStatusBar()
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

void CStatusBar::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	rParams.lpszClassName = "StatusBar";
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

void CStatusBar::GetCreateParams(WNDCREATE& rParams)
{
	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);

	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

    // Get the height of the default font.
    CScreenDC DC;
    
    DC.Select(pApp->DefaultFont());
    CSize FontSize = DC.TextExtents("Ly");

	// Override any settings.
	rParams.pszClassName  = "StatusBar";
	rParams.rcPos.Set(0, 0, 0, FontSize.cy + (2*BORDER_SIZE));
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Creates the hint and progress bars.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBar::OnCreate(const CRect& rcClient)
{
	// Create the child windows.
	m_HintBar.Create(*this, IDC_HINT_BAR, rcClient);
//	m_ProgressBar.Create(*this, IDC_PROGRESS_BAR, rcClient);

	// Set active window to be the hint window.
	m_pActive = &m_HintBar;
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the border.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBar::OnPaint(CDC& rDC)
{
}

/******************************************************************************
** Method:		OnResize()
**
** Description:	Window resized - save the new window dimensions and resize all
**				the info line children.
**
** Parameters:	iFlag		The resize method.
**				rNewSize	The new window dimensions.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBar::OnResize(int iFlag, const CSize& rNewSize)
{
	ASSERT(m_HintBar.Handle());
//	ASSERT(m_ProgressBar.Handle());

	// Calculate the position of all the children.
	CRect rcNewPos(BORDER_SIZE, BORDER_SIZE, rNewSize.cx-BORDER_SIZE, 
					rNewSize.cy-BORDER_SIZE);

	// Move the children
	m_HintBar.Move(rcNewPos);
//	m_ProgressBar.Move(rcNewPos);
}

/******************************************************************************
** Method:		ActivateWnd()
**
** Description:	Make the child window the currently visible one. This is used
**				internally to switch between different child windows when a
**				command is issued, such as SetHint().
**
** Parameters:	pWindow		The child window to make visible.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBar::ActivateWnd(CWnd* pWnd)
{
	ASSERT(pWnd);
	
	// Changed?
	if (m_pActive != pWnd)
	{
		// Hide previous
		if (m_pActive)
			m_pActive->Show(SW_HIDE);

		// Show next.
		m_pActive = pWnd;
		m_pActive->Show(SW_SHOW);
	}
}

/******************************************************************************
** Methods:		Hint()
**
** Description:	Wrappers that call the same method on the child window after
**				having activated the window.
**
** Parameters:	As per the child.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBar::Hint(uint iRscID)
{
	ASSERT(m_HintBar.Handle());

	ActivateWnd(&m_HintBar);
	m_HintBar.Hint(iRscID);
}

/******************************************************************************
** Methods:		Hint()
**
** Description:	Wrappers that call the same method on the child window after
**				having activated the window.
**
** Parameters:	As per the child.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBar::Hint(const char* pszHint)
{
	ASSERT(m_HintBar.Handle());

	ActivateWnd(&m_HintBar);
	m_HintBar.Hint(pszHint);
}
