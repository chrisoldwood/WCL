/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SPLITWND.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CSplitWnd class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SPLITWND_HPP
#define SPLITWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "CtrlWnd.hpp"

/******************************************************************************
** 
** This is a window which hosts 2 other windows either side by side or one
** above the other. A bar separates the two windows and can be used to resize
** them.
**
*******************************************************************************
*/

class CSplitWnd : public CCtrlWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CSplitWnd(bool bVertSplit, bool bFixedPanes);
	virtual	~CSplitWnd();

	//
	// Indexes of panes.
	//
	enum
	{
		LEFT_PANE   = 0,
		RIGHT_PANE  = 1,

		TOP_PANE    = 0,
		BOTTOM_PANE = 1
	};

	//
	// Accesors & Mutators.
	//
	void Pane(size_t nPane, CWnd* pWnd);
	CWnd* Pane(size_t nPane) const;

	void BarPos(int nPos);
	int BarPos() const;

	//
	// Attributes
	//
	CRect PaneRect(int nPane) const;

protected:
	//
	// Members.
	//
	CWnd*	m_pPanes[2];	// The window panes.
	bool	m_bVertSplit;	// Split is vertical or horizontal?
	bool	m_bFixedPanes;	// Panes cannot be resized.
	int		m_iBarPos;		// The position of the bar.

	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors (Overriden from the base class).
	//
	virtual void OnResize(int iFlag, const CSize& rNewSize);
	virtual	void OnPaint(CDC& rDC);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CSplitWnd::BarPos(int nPos)
{
	m_iBarPos = nPos;
	OnResize(0, ClientRect().Size());
}

inline int CSplitWnd::BarPos() const
{
	return m_iBarPos;
}

#endif //SPLITWND_HPP
