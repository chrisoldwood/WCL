/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TABWNDHOST.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CTabWndHost class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TABWNDHOST_HPP
#define TABWNDHOST_HPP

/******************************************************************************
** 
** This is a Tab Control used to one window per tab, swapping windows as the
** tabs are swapped.
**
*******************************************************************************
*/

class CTabWndHost : public CTabCtrl
{
public:
	//
	// Constructors/Destructor.
	//
	CTabWndHost();
	~CTabWndHost();
	
	//
	// Methods.
	//
	int  AddTab(const char* pszName, CWnd& oWnd);

	int  CurSel() const;
	void CurSel(int nTab);

	CWnd& TabWnd(int nTab) const;
	CWnd& CurTabWnd() const;

protected:
	//
	// Members.
	//

	//
	// Message processors.
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnSelChanging();
	virtual void OnSelChange();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline int CTabWndHost::AddTab(const char* pszName, CWnd& oWnd)
{
	oWnd.Show(SW_HIDE);
	return CTabCtrl::AddTab(pszName, &oWnd);
}

inline int CTabWndHost::CurSel() const
{
	return CTabCtrl::CurSel();
}

inline void CTabWndHost::CurSel(int nTab)
{
	OnSelChanging();
	CTabCtrl::CurSel(nTab);
	OnSelChange();
}

inline CWnd& CTabWndHost::TabWnd(int nTab) const
{
	return *((CWnd*) ItemPtr(nTab));
}

inline CWnd& CTabWndHost::CurTabWnd() const
{
	ASSERT(CurSel() >= 0);

	return TabWnd(CurSel());
}

#endif //TABWNDHOST_HPP
