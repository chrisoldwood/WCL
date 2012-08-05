/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		APP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CApp class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_APP_HPP
#define WCL_APP_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Font.hpp"
#include "Brush.hpp"
#include "Pen.hpp"
#include "Module.hpp"
#include "MainThread.hpp"
#include "ComCtl32.hpp"

// Forward declarations.
class CFrameWnd;

namespace WCL
{
class ICmdController;
}

/******************************************************************************
** 
** This is base class from which the application class is derived.
**
*******************************************************************************
*/

class CApp
{
public:
	//
	// Constructors/Destructor.
	//
	CApp(CFrameWnd& rFrameWnd, WCL::ICmdController& controller);
	virtual ~CApp();

	//
	// For drawing 3D controls etc.
	//
	const CFont&  DefaultFont();
	const CBrush& MidToneBrush();
	const CPen&   LightPen();
	const CPen&   LightestPen();
	const CPen&   DarkPen();
	const CPen&   DarkestPen();

    //
    // Timer methods.
    //
	WCL::TimerID StartTimer(uint nFrequency);
	void StopTimer(WCL::TimerID nTimerID);

    //
    // Message boxes.
    // For use when no window is available.
    //
	int AlertMsg(const tchar* pszMsg, ...) const;
	int QueryMsg(const tchar* pszMsg, ...) const;
	int NotifyMsg(const tchar* pszMsg, ...) const;
	int FatalMsg(const tchar* pszMsg, ...) const;

	//
	// Other methods.
	//
	bool ShowNormal() const;

	//! Check if the app singleton is valid.
	static bool IsValid();
	
	//! Global access to the app singleton.
	static CApp& This();
	
	//
	// Members.
	//
	CString			m_strTitle;			// Application title.
	CFrameWnd&		m_rMainWnd;			// Main window.
	WCL::ICmdController&	m_controller;		//!< Command controller.
	CModule			m_Module;			// Application module.
	CMainThread		m_MainThread;		// Main application thread.
	CString			m_strCmdLine;		// Command line.
	int				m_iCmdShow;			// Main window inital state.
	CComCtl32		m_oComCtl32;		// COMCTL32.DLL loader.

protected:
	//
	// Members.
	//
	CFont	m_DefaultFont;
	CBrush	m_MidToneBrush;
	CPen	m_LightPen, m_LightestPen;
	CPen	m_DarkPen,  m_DarkestPen;

	//
	// Startup and Shutdown template methods.
	// (Overriden in the derived class).
	//
	virtual	bool OnOpen();
	virtual	bool OnClose();

	//
	// Message handlers.
	//
	virtual void OnTimer(WCL::TimerID nTimerID);
	virtual void OnThreadMsg(UINT nMsg, WPARAM wParam, LPARAM lParam);

private:
	//
	// Startup and shutdown methods.
	// (Called from WinMain).
	//
	bool Open();
	void Run();
	void Close();

	//
	// Friends.
	//
	friend int WCL::winMain(HINSTANCE hInstance, LPSTR lpszCmdLine, int nCmdShow);
	friend class CMainThread;

	//
	// Disallow copies and assignments.
	//
	CApp(const CApp&);
	CApp& operator=(const CApp&);

	// The timer callback function.
	static void CALLBACK TimerProc(HWND hWnd, UINT uMsg, WCL::TimerID nTimerID, DWORD dwTime);

	//
	// Class members.
	//

	//! The singleton EXE component object.
	static CApp* g_pThis;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline const CFont& CApp::DefaultFont()
{
	// Create, if first call.
	if (m_DefaultFont.Handle() == NULL)
		m_DefaultFont.Create(reinterpret_cast<HFONT>(::GetStockObject(DEFAULT_GUI_FONT)));

	return m_DefaultFont;
}

inline const CBrush& CApp::MidToneBrush()
{
	// Create, if first call.
	if (m_MidToneBrush.Handle() == NULL)
		m_MidToneBrush.Create(::GetSysColor(COLOR_3DFACE));

	return m_MidToneBrush;
}

inline const CPen& CApp::LightPen()
{
	// Create, if first call.
	if (m_LightPen.Handle() == NULL)
		m_LightPen.Create(PS_SOLID, 0, ::GetSysColor(COLOR_3DLIGHT));

	return m_LightPen;
}

inline const CPen& CApp::LightestPen()
{
	// Create, if first call.
	if (m_LightestPen.Handle() == NULL)
		m_LightestPen.Create(PS_SOLID, 0, ::GetSysColor(COLOR_3DHIGHLIGHT));

	return m_LightestPen;
}

inline const CPen& CApp::DarkPen()
{
	// Create, if first call.
	if (m_DarkPen.Handle() == NULL)
		m_DarkPen.Create(PS_SOLID, 0, ::GetSysColor(COLOR_3DSHADOW));

	return m_DarkPen;
}

inline const CPen& CApp::DarkestPen()
{
	// Create, if first call.
	if (m_DarkestPen.Handle() == NULL)
		m_DarkestPen.Create(PS_SOLID, 0, ::GetSysColor(COLOR_3DDKSHADOW));

	return m_DarkestPen;
}

inline WCL::TimerID CApp::StartTimer(uint nFrequency)
{
	return ::SetTimer(NULL, 0, nFrequency, TimerProc);
}

inline void CApp::StopTimer(WCL::TimerID nTimerID)
{
	::KillTimer(NULL, nTimerID);
}

inline bool CApp::ShowNormal() const
{
	return ( (m_iCmdShow == SW_SHOWNORMAL) || (m_iCmdShow == SW_SHOWNOACTIVATE)
		  || (m_iCmdShow == SW_SHOW)       || (m_iCmdShow == SW_SHOWNA) );
}

#endif // WCL_APP_HPP
