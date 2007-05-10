/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TABCTRL.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CTabCtrl class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TABCTRL_HPP
#define TABCTRL_HPP

/******************************************************************************
** 
** This is a Tab Control.
**
*******************************************************************************
*/

class CTabCtrl : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CTabCtrl();
	virtual	~CTabCtrl();
	
	//
	// Methods.
	//
	int  NumTabs() const;

	int  AddTab(const char* pszName, LPARAM lData);
	int  AddTab(const char* pszName, const void* pData);

	int  CurSel() const;
	void CurSel(int nTab);

	LPARAM ItemData(int nTab) const;
	void*  ItemPtr(int nTab) const;

	CRect DisplayRect() const;

protected:
	//
	// Members.
	//

	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnReflectedCtrlMsg(NMHDR& rMsgHdr);
	virtual void OnSelChanging();
	virtual void OnSelChange();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline int CTabCtrl::NumTabs() const
{
	return TabCtrl_GetItemCount(m_hWnd);
}

inline int CTabCtrl::AddTab(const char* pszName, const void* pData)
{
	return AddTab(pszName, (LPARAM)pData);
}

inline int CTabCtrl::CurSel() const
{
	return TabCtrl_GetCurSel(m_hWnd);
}

inline void CTabCtrl::CurSel(int nTab)
{
	TabCtrl_SetCurSel(m_hWnd, nTab);
}

inline void* CTabCtrl::ItemPtr(int nTab) const
{
	return (void*) ItemData(nTab);
}

#endif //TABCTRL_HPP
