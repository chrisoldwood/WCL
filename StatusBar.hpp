/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATUSBAR.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CStatusBar class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "HintBar.hpp"
#include <vector>

// Forward declarations.
class CStatusBarPanel;

/******************************************************************************
**
** This is a child window that acts as a placeholder for other child windows
** that display information about the application.
**
*******************************************************************************
*/

class CStatusBar : public CCtrlWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CStatusBar(bool bSizeGrip = true);
	virtual	~CStatusBar();

	//
	// Panel methods.
	//
	void AddPanel(CStatusBarPanel& oPanel);

	//
	// Hint methods.
	//
	void Hint(uint iRscID);
	void Hint(const tchar* pszHint);

protected:
	// Template shorthands.
	typedef std::vector<CStatusBarPanel*> CPanels;

	//
	// Members.
	//
	bool			m_bSizeGrip;	// Dar a sizing grip?
	CWnd*			m_pActive;		// Active window to left of status bar.
	CPanels			m_apPanels;		// Status bar panels on right-hand side.
	CHintBar		m_oHintBar;		// The menu/toolbar hint windnow.

	// Child window IDs.
	static const uint IDC_HINT_BAR = 100;

	//
	// Internal methods.
	//
	void ActivateWnd(CWnd* pWnd);

	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual void OnPaint(CDC& rDC);
	virtual void OnResize(int iFlag, const CSize& rNewSize);
	virtual void OnHitTest(const CPoint& ptCursor);

private:
	// NotCopyable.
	CStatusBar(const CStatusBar&);
	CStatusBar& operator=(const CStatusBar&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //STATUSBAR_HPP
