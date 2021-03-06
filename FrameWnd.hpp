/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FRAMEWND.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CFrameWnd class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FRAMEWND_HPP
#define FRAMEWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "PopupWnd.hpp"
#include "IMsgFilter.hpp"
#include "ICommandWnd.hpp"

// Forward declarations.
class CAccel;
class CFrameMenu;
class CToolBar;
class CStatusBar;
class CDialog;

/******************************************************************************
**
** This is the base class for the main application window. It contains the menu
** and caption etc. It can also support status and tool bars.
**
*******************************************************************************
*/

class CFrameWnd : public CPopupWnd, public IMsgFilter, public WCL::ICommandWnd /*: private NotCopyable*/
{
public:
	//
	// Constructors/Destructor.
	//
	CFrameWnd(uint iIconID);
	virtual	~CFrameWnd();

	//
	// Properties.
	//

	//! Get the final placement of the window.
	const CRect& FinalPlacement() const;

	//
	// Frame components.
	//
	void Accel(CAccel* pAccel);
	CAccel* Accel() const;

	void Menu(CFrameMenu* pMenu);
	CFrameMenu* Menu() const;

	void ToolBar(CToolBar* pToolBar);
	CToolBar* ToolBar() const;

	void StatusBar(CStatusBar* pStatusBar);
	CStatusBar* StatusBar() const;

	void ActiveDlg(CDialog* pDialog);
	CDialog* ActiveDlg() const;

	//
	// Methods.
	//

	//! Open the window using the style specified.
	bool Open(int showStyle);

	//! Open the window and restore its position.
	bool Open(int showStyle, const CRect& position);

    //
    // State.
    //
    bool Close();

	//
	// Attributes.
	//
	virtual	CRect ClientRect() const;

	//
	// Message filtering.
	//
	virtual bool ProcessMsg(MSG& rMsg);

	//
	// ICommandWnd methods.
	//

	//! Handle updates to any command states.
	virtual void OnCommandsUpdated();

protected:
	//
	// Members.
	//
	uint		m_iIconID;		// ID of icon.
	CAccel*		m_pAccel;		// Accelerator table.
	CFrameMenu*	m_pMenu;		// Main menu.
	CToolBar*	m_pToolBar;		// Toolbar, if one.
	CStatusBar*	m_pStatusBar;	// Status Bar, if one.
	CDialog*	m_pActiveDlg;	// The active mode-less dialog, if one.
	CRect		m_finalPlacement;	//!< Final placement of the window.

	//
	// Constants.
	//

	// Window class name.
	static const tchar* CLASS_NAME;

	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors (Overridden from the base class).
	//
	virtual	LRESULT	WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual	void OnPaint(CDC& rDC);
	virtual void OnResize(int iFlag, const CSize& rNewSize);

	//
	// Message processors (Specific to this class).
	//
	virtual void OnActivateApp(bool bActivating);
	virtual bool OnQueryClose();
	virtual void OnClose();
	virtual void OnDropFile(int nFile, const tchar* pszPath);

private:
	// NotCopyable.
	CFrameWnd(const CFrameWnd&);
	CFrameWnd& operator=(const CFrameWnd&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

////////////////////////////////////////////////////////////////////////////////
//! Get the final placement of the window. This can only be called once the
//! window has been closed.

inline const CRect& CFrameWnd::FinalPlacement() const
{
	ASSERT(m_hWnd == NULL);

	return m_finalPlacement;
}

inline CAccel* CFrameWnd::Accel() const
{
	return m_pAccel;
}

inline CFrameMenu* CFrameWnd::Menu() const
{
	return m_pMenu;
}

inline CToolBar* CFrameWnd::ToolBar() const
{
	return m_pToolBar;
}

inline CStatusBar* CFrameWnd::StatusBar() const
{
	return m_pStatusBar;
}

inline CDialog* CFrameWnd::ActiveDlg() const
{
	return m_pActiveDlg;
}

inline bool CFrameWnd::Close()
{
	return PostMessage(WM_CLOSE);
}

#endif //FRAMEWND_HPP
