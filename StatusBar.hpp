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

/******************************************************************************
** 
** This is a child window that acts as a placeholder for other child windows
** that display information about the application. By defualt it knows about a
** hint window and a progress bar.
**
*******************************************************************************
*/

class CStatusBar : public CCtrlWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CStatusBar();
	~CStatusBar();

	//
	// Wrapper methods.
	//
	void Hint(uint iRscID);
	void Hint(const char* pszHint);

protected:
	//
	// Members.
	//
	CWnd*			m_pActive;
	CHintBar		m_HintBar;
//	CProgressBar	m_ProgressBar;

	// Child window IDs.
	enum {	IDC_HINT_BAR     = 100,
			IDC_PROGRESS_BAR = 101 };

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
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //STATUSBAR_HPP
