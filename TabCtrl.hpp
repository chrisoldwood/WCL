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

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"
#include <commctrl.h>

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
	size_t NumTabs() const;

	size_t AddTab(const tchar* pszName, LPARAM lData);
	size_t AddTab(const tchar* pszName, const void* pData);

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

inline size_t CTabCtrl::NumTabs() const
{
	return TabCtrl_GetItemCount(m_hWnd);
}

inline size_t CTabCtrl::AddTab(const tchar* pszName, const void* pData)
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
	return reinterpret_cast<void*>(ItemData(nTab));
}

#endif //TABCTRL_HPP
