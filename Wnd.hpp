/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WND.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CWnd class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WND_HPP
#define WND_HPP

/******************************************************************************
** 
** This is the base class from which all window classes are derived. It
** encapsulates the window handles and provides all the standard methods that
** work on an HWND. It also provides static functions that map objects and
** HWNDs to each other.
**
*******************************************************************************
*/

class CWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CWnd();
	CWnd(HWND hWnd);
	virtual ~CWnd();

    //
    // Member access.
    //
    HWND Handle() const;

    //
    // State.
    //
    bool Destroy();

    bool Show(int iStyle = SW_SHOW);
    bool IsVisible() const;

    void Enable(bool bEnable = true);
    bool IsEnabled();

	bool IsMinimised() const;
	bool IsMaximised() const;

	void Focus();

    //
    // Attributes.
    //
	void Title(const char* lpszTitle);
	CString Title() const;

	void Font(const CFont& rFont, bool bRedraw = true);
	CFont Font() const;

	void  WindowExStyle(DWORD dwExStyle);
	DWORD WindowExStyle() const;

	void  WindowStyle(DWORD dwStyle);
	DWORD WindowStyle() const;

	//
	// Position/Dimensions.
	//
	void Centre();
	void Move(const CRect& rNewPos, bool bRepaint = true);

	CRect WindowRect() const;
	virtual	CRect ClientRect() const;
	CRect ChildRect(const CWnd& rWnd) const;
	CRect Placement() const;

	void WindowPos(HWND hPos, bool bShow);
	void WindowPos(HWND hPos, const CRect& rcPos, bool bShow);

    //
    // Child window access.
    //
	CWnd Control(int iID) const;

    //
    // Message handling.
    //
    LRESULT	SendMessage(UINT iMsg, WPARAM wParam = 0, LPARAM lParam = 0L) const;
    bool PostMessage(UINT iMsg, WPARAM wParam = 0, LPARAM lParam = 0L) const;
    bool PostCommand(uint iCmd) const;
    bool PostCtrlMsg(uint iMsg, uint iCtrlID, HWND hCtrl) const;
	
    //
    // Timers.
    //
	uint StartTimer(uint iTimerID, uint iTimeout);
	void StopTimer(uint iTimerID);

    //
    // Painting.
    //
	void Redraw(bool bRedraw);
    void Invalidate(const CRect& rArea, bool bErase = true);
    void Invalidate(bool bErase = true);
    void Update();
	void RepaintNow();
	void DrawMenuBar();

    //
    // Message boxes.
    //
	int AlertMsg(const char* pszMsg, ...) const;
	int QueryMsg(const char* pszMsg, ...) const;
	int NotifyMsg(const char* pszMsg, ...) const;
	int FatalMsg(const char* pszMsg, ...) const;
    
	// Handle <-> Window map.
	static CWndMap s_WndMap;

protected:
	//
	// Members.
	//
	HWND	m_hWnd;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CWnd::CWnd()
{
	m_hWnd = NULL;
}

inline CWnd::CWnd(HWND hWnd)
{
	ASSERT(hWnd != NULL);
	
	m_hWnd = hWnd;
}

inline CWnd::~CWnd()
{
}

inline HWND CWnd::Handle() const
{
	return m_hWnd;
}

inline bool CWnd::Destroy()
{
	return ::DestroyWindow(m_hWnd);
}

inline bool CWnd::Show(int iStyle)
{
	return ::ShowWindow(m_hWnd, iStyle);
}

inline bool CWnd::IsVisible() const
{
	return ::IsWindowVisible(m_hWnd);
}

inline void CWnd::Enable(bool bEnable)
{
	::EnableWindow(m_hWnd, bEnable);
}

inline bool CWnd::IsEnabled()
{
	return ::IsWindowEnabled(m_hWnd);
}

inline bool CWnd::IsMinimised() const
{
	return ::IsIconic(m_hWnd);
}

inline bool CWnd::IsMaximised() const
{
	return ::IsZoomed(m_hWnd);
}

inline void CWnd::Focus()
{
	::SetFocus(m_hWnd);
}

inline void CWnd::Title(const char* pszTitle)
{
	ASSERT(pszTitle);

	::SetWindowText(m_hWnd, pszTitle);
}

inline void CWnd::Font(const CFont& rFont, bool bRedraw)
{
	SendMessage(WM_SETFONT, (WPARAM)rFont.Handle(), bRedraw);
}

inline CFont CWnd::Font() const
{
	return CFont((HFONT)SendMessage(WM_GETFONT, 0, 0), false);
}

inline void CWnd::WindowExStyle(DWORD dwExStyle)
{
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
}

inline DWORD CWnd::WindowExStyle() const
{
	ASSERT(m_hWnd != NULL);

	return ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
}

inline void CWnd::WindowStyle(DWORD dwStyle)
{
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
}

inline DWORD CWnd::WindowStyle() const
{
	ASSERT(m_hWnd != NULL);

	return ::GetWindowLong(m_hWnd, GWL_STYLE);
}

inline void CWnd::Move(const CRect& rNewPos, bool bRepaint)
{
	::MoveWindow(m_hWnd, rNewPos.left, rNewPos.top, rNewPos.Width(), rNewPos.Height(), bRepaint);
}

inline void CWnd::WindowPos(HWND hPos, bool bShow)
{
	int nShow = (bShow == true) ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;

	::SetWindowPos(m_hWnd, hPos, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | nShow);
}

inline void CWnd::WindowPos(HWND hPos, const CRect& rcPos, bool bShow)
{
	int nShow = (bShow == true) ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;

	::SetWindowPos(m_hWnd, hPos, rcPos.left, rcPos.top, rcPos.Width(), rcPos.Height(), SWP_NOACTIVATE | nShow);
}

inline CWnd CWnd::Control(int iID) const
{
	return CWnd(::GetDlgItem(m_hWnd, iID));
}

inline LRESULT CWnd::SendMessage(UINT iMsg, WPARAM wParam, LPARAM lParam) const
{
	return ::SendMessage(m_hWnd, iMsg, wParam, lParam);
}

inline bool CWnd::PostMessage(UINT iMsg, WPARAM wParam, LPARAM lParam) const
{
	return ::PostMessage(m_hWnd, iMsg, wParam, lParam);
}

inline bool CWnd::PostCommand(uint iCmd) const
{
	return ::PostMessage(m_hWnd, WM_COMMAND, iCmd, 0L);
}

inline bool CWnd::PostCtrlMsg(uint iMsg, uint iCtrlID, HWND hCtrl) const
{
	return ::PostMessage(m_hWnd, WM_COMMAND, MAKEWPARAM(iCtrlID, iMsg), (LPARAM)hCtrl);
}

inline void CWnd::Redraw(bool bRedraw)
{
	SendMessage(WM_SETREDRAW, bRedraw, 0);
}

inline void CWnd::Invalidate(const CRect& rArea, bool bErase)
{
	::InvalidateRect(m_hWnd, (LPRECT)&rArea, bErase);
}

inline void CWnd::Invalidate(bool bErase)
{
	::InvalidateRect(m_hWnd, NULL, bErase);
}

inline void CWnd::Update()
{
	::UpdateWindow(m_hWnd);
}

inline void CWnd::RepaintNow()
{
	Invalidate(true);
	Update();
}

inline void CWnd::DrawMenuBar()
{
	::DrawMenuBar(m_hWnd);
}

inline uint CWnd::StartTimer(uint iTimerID, uint iTimeout)
{
	return ::SetTimer(m_hWnd, iTimerID, iTimeout, NULL);
}

inline void CWnd::StopTimer(uint iTimerID)
{
	::KillTimer(m_hWnd, iTimerID);
}

#endif //WND_HPP
