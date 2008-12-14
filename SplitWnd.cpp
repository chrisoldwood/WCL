////////////////////////////////////////////////////////////////////////////////
//! \file   SplitWnd.cpp
//! \brief  The CSplitWnd class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "SplitWnd.hpp"
#include "DC.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants.

//! The thickness of the sizing bar.
static const uint BAR_SIZE = 4;
//! The thickness of a recessed client window border.
static const uint CLIENT_BORDER = 2;

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

CSplitWnd::CSplitWnd(Sizing eSizing)
	: m_eSplit(VERTICAL)
	, m_eSizing(eSizing)
	, m_nBarPos(100)
{
	Initialise();
}

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

CSplitWnd::CSplitWnd(Split eSplit, Sizing eSizing)
	: m_eSplit(eSplit)
	, m_eSizing(eSizing)
	, m_nBarPos(100)
{
	Initialise();
}

////////////////////////////////////////////////////////////////////////////////
//! Common construction.

void CSplitWnd::Initialise()
{
	m_pPanes[0] = nullptr;
	m_pPanes[1] = nullptr;

	m_curArrow.LoadRsc(IDC_ARROW);

	if (m_eSizing == RESIZEABLE)
		m_curSizer.LoadRsc((m_eSplit == VERTICAL) ? IDC_SIZEWE : IDC_SIZENS);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

CSplitWnd::~CSplitWnd()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get the window class settings.

void CSplitWnd::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = (HBRUSH) (COLOR_BTNSHADOW + 1);
	rParams.lpszClassName = TXT("SplitWnd");
	rParams.hCursor       = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the window instance settings.

void CSplitWnd::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = TXT("SplitWnd");
}

////////////////////////////////////////////////////////////////////////////////
//! Resize the child panes.

void CSplitWnd::OnResize(int /*iFlag*/, const CSize& rNewSize)
{
	// Clip the sizing bar to ensure it's always visible..
	if (m_eSplit == VERTICAL)
		m_nBarPos = ClipBarPos(m_nBarPos, 0, rNewSize.cx);
	else
		m_nBarPos = ClipBarPos(m_nBarPos, 0, rNewSize.cy);

	CRect rcNewClient = CRect(CPoint(0, 0), rNewSize);
	CRect rcPane = PaneRect(0, rcNewClient);

	// Left/Top pane set and changed size?
	if ( (m_pPanes[0] != nullptr) && (rcPane != m_pPanes[0]->WindowRect()) )
		m_pPanes[0]->Move(rcPane);

	rcPane = PaneRect(1, rcNewClient);

	// Right/Bottom pane set and changed size?
	if ( (m_pPanes[1] != nullptr)&& (rcPane != m_pPanes[1]->WindowRect()) )
		m_pPanes[1]->Move(rcPane);
}

////////////////////////////////////////////////////////////////////////////////
//! Paint the window.

void CSplitWnd::OnPaint(CDC& rDC)
{
	// Paint the sizing bar.
	CBrush brBtnFace(::GetSysColorBrush(COLOR_BTNFACE));

	rDC.Fill(SizingBarRect(), brBtnFace);

	// If empty, draw the left/top pane border.
	if (m_pPanes[0] == nullptr)
		rDC.Border3D(PaneRect(0), false, true);

	// If empty, draw the right/bottom pane border.
	if (m_pPanes[1] == nullptr)
		rDC.Border3D(PaneRect(1), false, true);
}

////////////////////////////////////////////////////////////////////////////////
//! Set the split style.

void CSplitWnd::SetSplitStyle(Split eSplit)
{
	// If required, load the correct sizing cursor.
	if (m_eSizing == RESIZEABLE)
	{
		m_curSizer.Release();
		m_curSizer.LoadRsc((eSplit == VERTICAL) ? IDC_SIZEWE : IDC_SIZENS);
	}

	// Update state.
	m_eSplit = eSplit;

	// Layout panes and repaint.
	OnResize(SIZE_RESTORED, ClientRect().Size());
	Invalidate();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the window inside a pane.

CWnd* CSplitWnd::Pane(size_t nPane) const
{
	ASSERT( (nPane == 0) || (nPane == 1) );

	return m_pPanes[nPane];
}

////////////////////////////////////////////////////////////////////////////////
//! Set the window inside a pane.

void CSplitWnd::SetPane(size_t nPane, CWnd* pWnd)
{
	ASSERT( (nPane == 0) || (nPane == 1) );

	// If present, hide previous pane window.
	if (m_pPanes[nPane] != nullptr)
	{
		m_pPanes[nPane]->Show(SW_HIDE);
	}

	// Ensure new window is sized & visible.
	if (pWnd != nullptr)
	{
		pWnd->Move(PaneRect(nPane));
		pWnd->Show(SW_SHOW);
	}

	// Update state.
	m_pPanes[nPane] = pWnd;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the rectangle for a pane.

CRect CSplitWnd::PaneRect(size_t nPane) const
{
	CRect rcClient = ClientRect();

	return PaneRect(nPane, rcClient);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the rectangle for a pane.

CRect CSplitWnd::PaneRect(size_t nPane, const CRect& rcClient) const
{
	ASSERT( (nPane == 0) || (nPane == 1) );

	CRect rcPane = rcClient;

	// Calculate rect.
	if ( (m_eSplit == VERTICAL) && (nPane == LEFT_PANE) )
	{
		rcPane.right = m_nBarPos - (BAR_SIZE / 2);
	}
	else if ( (m_eSplit == VERTICAL) && (nPane == RIGHT_PANE) )
	{
		rcPane.left = m_nBarPos + (BAR_SIZE / 2);
	}
	else if ( (m_eSplit == HORIZONTAL) && (nPane == TOP_PANE) )
	{
		rcPane.bottom = m_nBarPos - (BAR_SIZE / 2);
	}
	else if ( (m_eSplit == HORIZONTAL) && (nPane == BOTTOM_PANE) )
	{
		rcPane.top = m_nBarPos + (BAR_SIZE / 2);
	}

	return rcPane;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the rectangle for the sizing bar.

CRect CSplitWnd::SizingBarRect() const
{
	CRect rcBar(ClientRect());

	if (m_eSplit == VERTICAL)
	{
		rcBar.left  = m_nBarPos - (BAR_SIZE / 2);
		rcBar.right = m_nBarPos + (BAR_SIZE / 2);
	}
	else //(m_eSplit == HORIZONTAL)
	{
		rcBar.top    = m_nBarPos - (BAR_SIZE / 2);
		rcBar.bottom = m_nBarPos + (BAR_SIZE / 2);
	}

	return rcBar;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the cursor for this window or one of it's children.

void CSplitWnd::OnSetCursor(HWND hWnd, uint nHitCode, uint nMouseMsg)
{
	// Ignore, if request is for child window.
	if (hWnd != m_hWnd)
	{
		CCtrlWnd::OnSetCursor(hWnd, nHitCode, nMouseMsg);
		return;
	}

	// Default to the arrow for the empty panes.
	HCURSOR hCursor = m_curArrow.Handle();

	ASSERT(hCursor != NULL);

	// Show sizing cursor, if inside the bar.
	if (m_eSizing == RESIZEABLE)
	{
		ASSERT(m_curSizer.Handle() != NULL);

		CPoint ptCursor = CCursor::CurrentPos(m_hWnd);
		CRect  rcBar    = SizingBarRect();

		if (ptCursor.IsIn(rcBar))
			hCursor = m_curSizer.Handle();
	}

	::SetCursor(hCursor);
}

////////////////////////////////////////////////////////////////////////////////
//! Handle a mouse click over the sizing bar.

void CSplitWnd::OnLeftButtonDown(const CPoint& /*ptCursor*/, uint /*nKeyFlags*/)
{
	// Ignore if fixed size panes.
	if (m_eSizing != RESIZEABLE)
		return;

	::SetCapture(m_hWnd);
}

////////////////////////////////////////////////////////////////////////////////
//! Handle a mouse click over the sizing bar.

void CSplitWnd::OnLeftButtonUp(const CPoint& /*ptCursor*/, uint /*nKeyFlags*/)
{
	// Release mouse capture.
	if (::GetCapture() == m_hWnd)
		::ReleaseCapture();
}

////////////////////////////////////////////////////////////////////////////////
//! Handle resizng of the panes.

void CSplitWnd::OnMouseMove(const CPoint& ptCursor, uint /*nKeyFlags*/)
{
	// Ignore unless we have capture the mouse.
	if (::GetCapture() != m_hWnd)
		return;

	CRect rcClient = ClientRect();
	int   iBarPos  = (m_eSplit == VERTICAL) ? ptCursor.x : ptCursor.y;

	// Resize panes, only if changed..
	if (m_nBarPos != static_cast<uint>(iBarPos))
	{
		m_nBarPos = iBarPos;
		OnResize(SIZE_RESTORED, rcClient.Size());
		Invalidate();
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Clip the bar position.

int CSplitWnd::ClipBarPos(int iBarPos, int iMin, int iMax)
{
	const int BAR_WIDTH        = BAR_SIZE / 2;
	const int MIN_CLIENT_WIDTH = (CLIENT_BORDER * 2) + 2;

	iBarPos = std::max(iBarPos, iMin + (BAR_WIDTH + MIN_CLIENT_WIDTH));
	iBarPos = std::min(iBarPos, iMax - (BAR_WIDTH + MIN_CLIENT_WIDTH));

	return iBarPos;
}
