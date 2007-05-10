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
#ifndef APP_HPP
#define APP_HPP

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
	CApp(CFrameWnd& rFrameWnd, CCmdControl& rCmdControl);
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
	uint StartTimer(uint nFrequency);
	void StopTimer(uint nTimerID);

    //
    // Message boxes.
    // For use when no window is available.
    //
	int AlertMsg(const char* pszMsg, ...) const;
	int QueryMsg(const char* pszMsg, ...) const;
	int NotifyMsg(const char* pszMsg, ...) const;
	int FatalMsg(const char* pszMsg, ...) const;

	//
	// Other methods.
	//
	bool ShowNormal() const;

	static CString FormatError(DWORD dwError = ::GetLastError());

	// Global access to the app object.
	static CApp& This();
	
	//
	// Members.
	//
	CLeakCheck		m_oLeakChecker;		// Dumps memory leaks.
	CString			m_strTitle;			// Application title.
	CFrameWnd&		m_rMainWnd;			// Main window.
	CCmdControl&	m_rCmdControl;		// Command controller.
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
	virtual void OnTimer(uint nTimerID);
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
	friend int WINAPI WinMain(HINSTANCE hCurrInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int iCmdShow);
	friend class CMainThread;

	//
	// Disallow copies and assignments.
	//
	CApp(const CApp&);
	CApp& operator=(const CApp&);

	// The timer callback function.
	static void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT nTimerID, DWORD dwTime);

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
		m_DefaultFont.Create((HFONT)::GetStockObject(DEFAULT_GUI_FONT));

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

inline uint CApp::StartTimer(uint nFrequency)
{
	return ::SetTimer(NULL, 0, nFrequency, TimerProc);
}

inline void CApp::StopTimer(uint nTimerID)
{
	::KillTimer(NULL, nTimerID);
}

inline bool CApp::ShowNormal() const
{
	return ( (m_iCmdShow == SW_SHOWNORMAL) || (m_iCmdShow == SW_SHOWNOACTIVATE)
		  || (m_iCmdShow == SW_SHOW)       || (m_iCmdShow == SW_SHOWNA) );
}

#endif //APP_HPP
