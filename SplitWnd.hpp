////////////////////////////////////////////////////////////////////////////////
//! \file   SplitWnd.hpp
//! \brief  The CSplitWnd class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef SPLITWND_HPP
#define SPLITWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "CtrlWnd.hpp"
#include "Cursor.hpp"

////////////////////////////////////////////////////////////////////////////////
//! This is a window which hosts 2 other windows either side by side or one
//! above the other. A bar separates the two windows and can be used to resize
//! them.

class CSplitWnd : public CCtrlWnd
{
public:
	//! The style of split.
	enum Split
	{
		VERTICAL,		//!< Split into a left & right pane.
		HORIZONTAL,		//!< Split into a top & bottom pane.
	};

	//! The style of pane resizing.
	enum Sizing
	{
		FIXED,			//!< The pane split is programmatic.
		RESIZEABLE,		//!< The pane split is user controlled.
	};

	//! Constructor.
	CSplitWnd(Sizing eSizing);

	//! Constructor.
	CSplitWnd(Split eSplit, Sizing eSizing);

	//! Destructor.
	virtual	~CSplitWnd();

	//! The Index of the panes.
	enum
	{
		LEFT_PANE   = 0,	//!< The left pane in a VERTICAL split.
		RIGHT_PANE  = 1,	//!< The right pane in a VERTICAL split.

		TOP_PANE    = 0,	//!< The top pane in a HORIZONTAL split.
		BOTTOM_PANE = 1,	//!< The bottom pane in a HORIZONTAL split.
	};

	//
	// Properties.
	//

	//! Get the split style.
	Split SplitStyle() const;

	//! Set the split style.
	void SetSplitStyle(Split eSplit);

	//! Get the window inside a pane.
	CWnd* Pane(size_t nPane) const;

	//! Set the window inside a pane.
	void SetPane(size_t nPane, CWnd* pWnd);

	//! Get the position of the sizing bar.
	uint SizingBarPos() const;

	//! Set the position of the sizing bar.
	void SetSizingBarPos(uint nPos);

	//
	// Methods.
	//

	//! Get the rectangle for a pane.
	CRect PaneRect(size_t nPane) const;

	//! Get the rectangle for the sizing bar.
	CRect SizingBarRect() const;

protected:
	//
	// Members.
	//
	CWnd*	m_pPanes[2];	//!< The window panes.
	Split	m_eSplit;		//!< The position of the split.
	Sizing	m_eSizing;		//!< The ability to resize the panes.
	uint	m_nBarPos;		//!< The x or y position of the bar.
	CCursor	m_curArrow;		//!< The arrow cursor.
	CCursor	m_curSizer;		//!< The sizing cursor.

	//
	// Window creation template methods.
	//

	//! Get the window class settings.
	virtual void GetClassParams(WNDCLASS& rParams);

	//! Get the window instance settings.
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message handlers.
	//

	//! Resize the child panes.
	virtual void OnResize(int iFlag, const CSize& rNewSize);

	//! Paint the window.
	virtual	void OnPaint(CDC& rDC);

	//! Set the cursor for this window or one of it's children.
	virtual void OnSetCursor(HWND hWnd, uint nHitCode, uint nMouseMsg);

	//! Handle a mouse click over the sizing bar.
	virtual void OnLeftButtonDown(const CPoint& ptCursor, uint nKeyFlags);

	//! Handle a mouse click over the sizing bar.
	virtual void OnLeftButtonUp(const CPoint& ptCursor, uint nKeyFlags);

	//! Handle resizng of the panes.
	virtual void OnMouseMove(const CPoint& ptCursor, uint nKeyFlags);

	//
	// Internal methods.
	//

	//! Common construction.
	void Initialise();

	//! Get the rectangle for a pane.
	CRect PaneRect(size_t nPane, const CRect& rcClient) const;

	//! Clip the bar position.
	static int ClipBarPos(int iBarPos, int iMin, int iMax);

private:
	// NotCopyable.
	CSplitWnd(const CSplitWnd&);
	CSplitWnd& operator=(const CSplitWnd&);
};

////////////////////////////////////////////////////////////////////////////////
//! Get the split style.

inline CSplitWnd::Split CSplitWnd::SplitStyle() const
{
	return m_eSplit;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the position of the sizing bar.

inline uint CSplitWnd::SizingBarPos() const
{
	return m_nBarPos;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the position of the sizing bar.

inline void CSplitWnd::SetSizingBarPos(uint nPos)
{
	m_nBarPos = nPos;
	OnResize(0, ClientRect().Size());
}

#endif //SPLITWND_HPP
