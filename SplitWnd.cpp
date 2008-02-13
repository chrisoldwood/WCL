/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SPLITWND.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CSplitWnd class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "SplitWnd.hpp"
#include "DC.hpp"

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Thickness of the bar.
#define	BAR_SIZE	4

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

CSplitWnd::CSplitWnd(bool bVertSplit, bool bFixedPanes)
	: m_bVertSplit(bVertSplit)
	, m_bFixedPanes(bFixedPanes)
	, m_iBarPos(100)
{
	m_pPanes[0] = NULL;
	m_pPanes[1] = NULL;
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

CSplitWnd::~CSplitWnd()
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

void CSplitWnd::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	rParams.lpszClassName = TXT("SplitWnd");
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

void CSplitWnd::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = TXT("SplitWnd");
}

/******************************************************************************
** Method:		OnResize()
**
** Description:	Resize the panes to fit the new size.
**
** Parameters:	iFlag		The resize method.
**				rNewSize	The new window dimensions.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSplitWnd::OnResize(int /*iFlag*/, const CSize& /*rNewSize*/)
{
	// Left/Top pane set and changed size?
	if ( (m_pPanes[0] != NULL) && (PaneRect(0).Size() != m_pPanes[0]->WindowRect().Size()) )
		m_pPanes[0]->Move(PaneRect(0));

	// Right/Bottom pane set and changed size?
	if ( (m_pPanes[1] != NULL)&& (PaneRect(1).Size() != m_pPanes[1]->WindowRect().Size()) )
		m_pPanes[1]->Move(PaneRect(1));
}

/******************************************************************************
** Method:		Pane()
**
** Description:	Sets either the left/top or right/bottom window pane.
**
** Parameters:	nPane		The window pane to set.
**				pWnd		The window pane or NULL to remove it.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSplitWnd::Pane(size_t nPane, CWnd* pWnd)
{
	ASSERT( (nPane == 0) || (nPane == 1) );

	// Ensure the window is
	// visible and sized correctly.
	if (pWnd != NULL)
	{
		pWnd->Move(PaneRect(nPane));
		pWnd->Show();
	}

	m_pPanes[nPane] = pWnd;
}

/******************************************************************************
** Method:		Pane()
**
** Description:	Gets either the left/top or right/bottom window pane.
**
** Parameters:	nPane		The window pane to get.
**
** Returns:		The window pane or NULL if not set.
**
*******************************************************************************
*/

CWnd* CSplitWnd::Pane(size_t nPane) const
{
	ASSERT( (nPane == 0) || (nPane == 1) );

	return m_pPanes[nPane];
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the background for unset panes.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CRect CSplitWnd::PaneRect(int nPane) const
{
	ASSERT( (nPane == 0) || (nPane == 1) );

	CRect rcPane(ClientRect());

	// Calculate rect.
	if ( (m_bVertSplit) && (nPane == LEFT_PANE) )
	{
		rcPane.right = m_iBarPos - (BAR_SIZE / 2);
	}
	else if ( (m_bVertSplit) && (nPane == RIGHT_PANE) )
	{
		rcPane.left  = m_iBarPos + (BAR_SIZE / 2);
	}
	else if ( (!m_bVertSplit) && (nPane == TOP_PANE) )
	{
		rcPane.bottom = m_iBarPos - (BAR_SIZE / 2);
	}
	else if ( (!m_bVertSplit) && (nPane == BOTTOM_PANE) )
	{
		rcPane.top    = m_iBarPos + (BAR_SIZE / 2);
	}

	return rcPane;
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the background for unset panes.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSplitWnd::OnPaint(CDC& rDC)
{
	CBrush BgBrush(GRAY_BRUSH);

	// Left/Top pane empty?
	if (m_pPanes[0] == NULL)
	{
		CRect rcPane = PaneRect(0);
		rDC.Fill(rcPane, BgBrush);
		rDC.Border3D(rcPane, false, true);
	}

	// Right/Bottom pane empty?
	if (m_pPanes[1] == NULL)
	{
		CRect rcPane = PaneRect(1);
		rDC.Fill(rcPane, BgBrush);
		rDC.Border3D(rcPane, false, true);
	}
}
