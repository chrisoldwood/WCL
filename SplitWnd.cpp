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
static const uint BAR_SIZE = 2;
//! The thickness of a recessed client window border.
static const uint CLIENT_BORDER = 2;

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

CSplitWnd::CSplitWnd(Split eSplit, Sizing eSizing)
	: m_eSplit(eSplit)
	, m_eSizing(eSizing)
	, m_nBarPos(100)
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

void CSplitWnd::OnResize(int /*iFlag*/, const CSize& /*rNewSize*/)
{
	// Left/Top pane set and changed size?
	if ( (m_pPanes[0] != nullptr) && (PaneRect(0).Size() != m_pPanes[0]->WindowRect().Size()) )
		m_pPanes[0]->Move(PaneRect(0));

	// Right/Bottom pane set and changed size?
	if ( (m_pPanes[1] != nullptr)&& (PaneRect(1).Size() != m_pPanes[1]->WindowRect().Size()) )
		m_pPanes[1]->Move(PaneRect(1));
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
	ASSERT( (nPane == 0) || (nPane == 1) );

	CRect rcPane(ClientRect());

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

	CRect rcClient     = ClientRect();
	int   iBarWidth    = BAR_SIZE / 2;
	int   iMinCltWidth = (CLIENT_BORDER * 2) + 1;

	// Move the sizing bar.
	if (m_eSplit == VERTICAL)
	{
		int iBarPos = ptCursor.x;

		// Clip to window edge.
		iBarPos = max(iBarPos, rcClient.left  + (iBarWidth + iMinCltWidth));
		iBarPos = min(iBarPos, rcClient.right - (iBarWidth + iMinCltWidth));

		// Resize panes, only if changed..
		if (m_nBarPos != static_cast<uint>(iBarPos))
		{
			m_nBarPos = iBarPos;
			OnResize(SIZE_RESTORED, rcClient.Size());
			Invalidate();
		}
	}
	else //(m_eSplit == HORIZONTAL)
	{
		int iBarPos = ptCursor.y;

		// Clip to window edge.
		iBarPos = max(iBarPos, rcClient.top    + (iBarWidth + iMinCltWidth));
		iBarPos = min(iBarPos, rcClient.bottom - (iBarWidth + iMinCltWidth));

		// Resize panes, only if changed..
		if (m_nBarPos != static_cast<uint>(iBarPos))
		{
			m_nBarPos = iBarPos;
			OnResize(SIZE_RESTORED, rcClient.Size());
			Invalidate();
		}
	}
}
