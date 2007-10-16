/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATUSBAR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CStatusBar class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StatusBar.hpp"
#include "StatusBarPanel.hpp"
#include "ScreenDC.hpp"
#include "App.hpp"

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Width of border around child windows.
// NB: Lower outer border is part of the main window.
const int OUTER_BORDER_SIZE = 2;

// Width of border around child window content.
const int INNER_BORDER_SIZE = CStatusBarPanel::BORDER_SIZE;

// Size of sizing grip handle.
const int SIZE_GRIP_SIZE = 12;

// Size of gap between panels.
const int PANEL_GAP_SIZE = 2;

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

CStatusBar::CStatusBar(bool bSizeGrip)
	: m_bSizeGrip(bSizeGrip)
	, m_pActive(NULL)
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
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

    // Get the height of the default font.
    CSize FontSize = CScreenDC().TextExtents(CApp::This().DefaultFont(), "Ly");

	// Override any settings.
	rParams.pszClassName  = "StatusBar";
	rParams.rcPos.Set(0, 0, 0, FontSize.cy + (2*INNER_BORDER_SIZE) + OUTER_BORDER_SIZE);
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
	m_oHintBar.Create(*this, IDC_HINT_BAR, rcClient);

	// Set active window to be the hint window.
	m_pActive = &m_oHintBar;
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the sizing grip, if one enabled.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBar::OnPaint(CDC& rDC)
{
	ASSERT(m_pParent != NULL);

	// Ignore, if no size grip OR frame window is maximised.
	if ( (!m_bSizeGrip) || (::IsZoomed(m_pParent->Handle())) )
		return;

	// Get window dimensions.
	CRect rcClient = ClientRect();

	// Get bottom right co-ordinates.
	CPoint ptCorner(rcClient.right-1, rcClient.bottom-1);

	// Create pens.
	CPen oDarkPen (PS_SOLID, 0, ::GetSysColor(COLOR_BTNSHADOW));
	CPen oLightPen(PS_SOLID, 0, ::GetSysColor(COLOR_BTNHIGHLIGHT));
	CPen oFacePen (PS_SOLID, 0, ::GetSysColor(COLOR_BTNFACE));

	// For all lines.
	for (int i = 0; i < 12; ++i)
	{
		// Select the required pen.
		if ((i % 4) == 3)
			rDC.Select(oLightPen);
		else if ( ((i % 4) == 1) || ((i % 4) == 2) )
			rDC.Select(oDarkPen);
		else
			rDC.Select(oFacePen);

		// Draw the line.
		rDC.Line(ptCorner.x-i, ptCorner.y, ptCorner.x+1, ptCorner.y-i-1);
	}

#ifdef _DEBUG
	// Passify BoundsChecker.
	rDC.Select(CPen(NULL_PEN));
#endif
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

void CStatusBar::OnResize(int /*iFlag*/, const CSize& rNewSize)
{
	ASSERT(m_oHintBar.Handle());

	// Template shorthands.
	typedef CPanels::reverse_iterator CIter;

	CSize dmSize = rNewSize;

	// Adjust size for the grip, if one.
	if (m_bSizeGrip)
		dmSize.cx -= SIZE_GRIP_SIZE + PANEL_GAP_SIZE;

	// Allocate DWP handle.
	HDWP hDWP = ::BeginDeferWindowPos(m_apPanels.size() + 1);

	ASSERT(hDWP != NULL);

	// Reposition the child panels.
	for (CIter oIter = m_apPanels.rbegin(); oIter != m_apPanels.rend(); ++oIter)
	{
		CStatusBarPanel* pPanel = *oIter;
		int              nWidth = pPanel->ClientRect().Width();

		// Reposition window.
		CRect rcNewPos(dmSize.cx-nWidth, OUTER_BORDER_SIZE, dmSize.cx, OUTER_BORDER_SIZE+(dmSize.cy-OUTER_BORDER_SIZE));

		::DeferWindowPos(hDWP, pPanel->Handle(), NULL, rcNewPos.left, rcNewPos.top,
							rcNewPos.Width(), rcNewPos.Height(), SWP_NOZORDER | SWP_NOCOPYBITS);

		// Adjust size for panel.
		dmSize.cx -= nWidth;
		dmSize.cx -= PANEL_GAP_SIZE;
	}

	// Reposition the main child.
	CRect rcNewPos(0, OUTER_BORDER_SIZE, dmSize.cx, OUTER_BORDER_SIZE+(dmSize.cy-OUTER_BORDER_SIZE));

	::DeferWindowPos(hDWP, m_oHintBar.Handle(), NULL, rcNewPos.left, rcNewPos.top,
						rcNewPos.Width(), rcNewPos.Height(), SWP_NOZORDER | SWP_NOCOPYBITS);

	// Move them.
	::EndDeferWindowPos(hDWP);
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
	ASSERT(m_oHintBar.Handle());

	ActivateWnd(&m_oHintBar);
	m_oHintBar.Hint(iRscID);
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
	ASSERT(m_oHintBar.Handle());

	ActivateWnd(&m_oHintBar);
	m_oHintBar.Hint(pszHint);
}

/******************************************************************************
** Method:		OnHitTest()
**
** Description:	Checks if the mouse is on the sizing grip.
**
** Parameters:	ptCursor	The mouse position in screen coordinates.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBar::OnHitTest(const CPoint& ptCursor)
{
	// Have sizing grip AND not maximised?
	if ( (m_bSizeGrip) && (!::IsZoomed(m_pParent->Handle())) )
	{
		CPoint ptClient = ptCursor;

		// Convert mouse coordinates to client.
		::ScreenToClient(m_hWnd, &ptClient);

		// Calculate grip rectangle.
		CRect rcGrip = ClientRect();

		rcGrip.left = rcGrip.right  - 12;
		rcGrip.top  = rcGrip.bottom - 12;

		// Is in sizing grip rect?
		if (ptClient.IsIn(rcGrip))
		{
			MsgHandled(true);
			MsgResult (HTBOTTOMRIGHT);
			return;
		}
	}

	// Handle in base class.
	CCtrlWnd::OnHitTest(ptCursor);
}

/******************************************************************************
** Method:		AddPanel()
**
** Description:	Adds a panel to the status bar. The panel is added to the right
**				of the existing ones.
**
** Parameters:	oPanel		The new panel.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBar::AddPanel(CStatusBarPanel& oPanel)
{
	ASSERT(oPanel.Handle() != NULL);

	m_apPanels.push_back(&oPanel);

	// Force a layout change, if window created.
	if (m_hWnd != NULL)
		OnResize(SIZE_RESTORED, ClientRect().Size());
}
