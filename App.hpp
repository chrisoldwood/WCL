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
	~CApp();

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
    // Message boxes.
    // For use when no window is available.
    //
	int AlertMsg(const char* pszMsg, ...) const;
	int QueryMsg(const char* pszMsg, ...) const;
	int NotifyMsg(const char* pszMsg, ...) const;
	int FatalMsg(const char* pszMsg, ...) const;

	//
	// Error handling.
	//
	static CString FormatError(DWORD dwError = ::GetLastError());

	// Global access to the app object.
	static CApp& This();
	
	//
	// Members.
	//
	CString			m_strTitle;
	CFrameWnd&		m_rMainWnd;
	CCmdControl&	m_rCmdControl;
	CModule			m_Module;
	CMainThread		m_MainThread;
	CString			m_strCmdLine;
	int				m_iCmdShow;
	CComCtl32*		m_pComCtl32;

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

private:
	//
	// Startup and shutdown methods.
	// (Called from WinMain).
	//
	bool Open();
	void Run();
	void Close();

	friend int WINAPI WinMain(HINSTANCE hCurrInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int iCmdShow);

	//
	// Disallow copies and assignments.
	//
	CApp(const CApp&);
	CApp& operator=(const CApp&);
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

#endif //APP_HPP
