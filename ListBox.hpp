/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LISTBOX.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CListBox class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"

/******************************************************************************
** 
** This is a listbox control.
**
*******************************************************************************
*/

class CListBox : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CListBox();

	//
	// Standard methods.
	//
	void Reset() const;
	size_t Count() const;
	size_t Add(const tchar* pszText) const;
	size_t Add(const tchar* pszText, LPARAM lData) const;
	size_t Add(const tchar* pszText, void*  pData) const;
	size_t Insert(const tchar* pszText, size_t nItem) const;
	size_t Delete(size_t nItem) const;
	size_t Find(const tchar* pszText, size_t nFirst = Core::npos) const;
	size_t FindExact(const tchar* pszText, size_t nFirst = Core::npos) const;
	void ItemData(size_t nItem, LPARAM lData) const;
	void ItemPtr(size_t nItem, void* pData) const;
	LPARAM ItemData(size_t nItem) const;
	void*  ItemPtr(size_t nItem) const;
	size_t CurSel() const;
	void CurSel(size_t nItem) const;
	size_t  CurSel(const tchar* pszText, size_t nFirst = Core::npos) const;
	bool IsSel(size_t nItem) const;
	void RestoreSel(size_t nItem) const;
	size_t TextLength(size_t nItem) const;
	size_t Text(tchar* pszText, size_t nItem) const;
	CString Text(size_t nItem) const;
	void SetTabStops(size_t iNumTabStops, const uint* pTabStops);
	void ItemHeight(size_t nItem, uint nHeight);

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
	virtual void OnReflectedCtrlMsg(uint iMsg);
	virtual void OnSelChange();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CListBox::Reset() const
{
	SendMessage(LB_RESETCONTENT, 0, 0L);
}

inline size_t CListBox::Count() const
{
	return SendMessage(LB_GETCOUNT, 0, 0L);
}

inline size_t CListBox::Add(const tchar* pszText) const
{
	return SendMessage(LB_ADDSTRING, 0, (LPARAM)pszText);
}

inline size_t CListBox::Add(const tchar* pszText, LPARAM lData) const
{
	size_t n = Add(pszText);

	ItemData(n, lData);

	return n;
}

inline size_t CListBox::Add(const tchar* pszText, void*  pData) const
{
	size_t n = Add(pszText);

	ItemPtr(n, pData);

	return n;
}

inline size_t CListBox::Insert(const tchar* pszText, size_t nItem) const
{
	return SendMessage(LB_INSERTSTRING, nItem, (LPARAM)pszText);
}

inline size_t CListBox::Delete(size_t nItem) const
{
	return SendMessage(LB_DELETESTRING, nItem, 0L);
}

inline size_t CListBox::Find(const tchar* pszText, size_t nFirst) const
{
	return SendMessage(LB_FINDSTRING, nFirst, (LPARAM)pszText);
}

inline size_t CListBox::FindExact(const tchar* pszText, size_t nFirst) const
{
	return SendMessage(LB_FINDSTRINGEXACT, nFirst, (LPARAM)pszText);
}

inline void CListBox::ItemData(size_t nItem, LPARAM lData) const
{
	SendMessage(LB_SETITEMDATA, nItem, lData);
}

inline LPARAM CListBox::ItemData(size_t nItem) const
{
	return SendMessage(LB_GETITEMDATA, nItem, 0L);
}

inline void CListBox::ItemPtr(size_t nItem, void* pData) const
{
	SendMessage(LB_SETITEMDATA, nItem, (LPARAM)pData);
}

inline void* CListBox::ItemPtr(size_t nItem) const
{
	return reinterpret_cast<void*>(SendMessage(LB_GETITEMDATA, nItem, 0L));
}

inline size_t CListBox::CurSel() const
{
	return SendMessage(LB_GETCURSEL, 0, 0L);
}

inline void CListBox::CurSel(size_t nItem) const
{
	SendMessage(LB_SETCURSEL, nItem, 0L);
}

inline size_t CListBox::CurSel(const tchar* pszText, size_t nFirst) const
{
	return SendMessage(LB_SELECTSTRING, nFirst, reinterpret_cast<LPARAM>(pszText));
}

inline bool CListBox::IsSel(size_t nItem) const
{
	return static_cast<bool>(SendMessage(LB_GETSEL, nItem, 0L));
}

inline size_t CListBox::TextLength(size_t nItem) const
{
	return SendMessage(LB_GETTEXTLEN, nItem, 0L);
}

inline size_t CListBox::Text(tchar* pszText, size_t nItem) const
{
	return SendMessage(LB_GETTEXT, nItem, reinterpret_cast<LPARAM>(pszText));
}

inline void CListBox::SetTabStops(size_t iNumTabStops, const uint* pTabStops)
{
	SendMessage(LB_SETTABSTOPS, iNumTabStops, reinterpret_cast<LPARAM>(pTabStops));
}

inline void CListBox::ItemHeight(size_t nItem, uint nHeight)
{
	SendMessage(LB_SETITEMHEIGHT, nItem, nHeight);
}

#endif //LISTBOX_HPP
