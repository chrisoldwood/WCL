/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		COMBOBOX.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CComboBox class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef COMBOBOX_HPP
#define COMBOBOX_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"

/******************************************************************************
**
** This is a combo-box control.
**
*******************************************************************************
*/

class CComboBox : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CComboBox();

	//
	// Standard methods.
	//
	void Reset() const;
	size_t Count() const;
	void TextLimit(size_t nLimit) const;
	size_t Add(const tchar* pszText) const;
	size_t Add(const tstring& text) const;
	size_t Add(const tchar* pszText, LPARAM lData) const;
	size_t Add(const tchar* pszText, void*  pData) const;
	size_t Insert(const tchar* pszText, size_t nItem) const;
	size_t Delete(size_t nItem) const;
	size_t Find(const tchar* pszText, size_t nFirst = Core::npos) const;
	size_t FindExact(const tchar* pszText, size_t nFirst = Core::npos) const;
	size_t FindExact(const tstring& text, size_t first = Core::npos) const;
	bool Exists(const tstring& text) const;
	void ItemData(size_t nItem, LPARAM lData) const;
	void ItemPtr(size_t nItem, void* pData) const;
	LPARAM ItemData(size_t nItem) const;
	void*  ItemPtr(size_t nItem) const;
	size_t CurSel() const;
	void CurSel(size_t nItem) const;
	void RemoveSelection();
	size_t CurSel(const tchar* pszText, size_t iFirst = Core::npos) const;
	size_t Select(const tchar* pszText, size_t iFirst = Core::npos) const;
	size_t Select(const tstring& text, size_t first = Core::npos) const;
	size_t TextLength(size_t nItem) const;
	size_t TextLength() const;
	CString Text(size_t nItem) const;
	CString Text() const;

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
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CComboBox::Reset() const
{
	SendMessage(CB_RESETCONTENT, 0, 0L);
}

inline size_t CComboBox::Count() const
{
	return SendMessage(CB_GETCOUNT, 0, 0L);
}

inline void CComboBox::TextLimit(size_t nLimit) const
{
	SendMessage(CB_LIMITTEXT, nLimit, 0L);
}

inline size_t CComboBox::Add(const tchar* pszText) const
{
	LRESULT lResult = SendMessage(CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(pszText));

	ASSERT((lResult != CB_ERR) && (lResult != CB_ERRSPACE));

	return lResult;
}

inline size_t CComboBox::Add(const tstring& text) const
{
	return Add(text.c_str());
}

inline size_t CComboBox::Add(const tchar* pszText, LPARAM lData) const
{
	size_t nItem = Add(pszText);

	ItemData(nItem, lData);

	return nItem;
}

inline size_t CComboBox::Add(const tchar* pszText, void*  pData) const
{
	size_t nItem = Add(pszText);

	ItemPtr(nItem, pData);

	return nItem;
}

inline size_t CComboBox::Insert(const tchar* pszText, size_t nItem) const
{
	LRESULT lResult = SendMessage(CB_INSERTSTRING, nItem, reinterpret_cast<LPARAM>(pszText));

	ASSERT((lResult != CB_ERR) && (lResult != CB_ERRSPACE));

	return lResult;
}

inline size_t CComboBox::Delete(size_t nItem) const
{
	LRESULT lResult = SendMessage(CB_DELETESTRING, nItem, 0L);

	ASSERT(lResult != CB_ERR);

	return lResult;
}

inline size_t CComboBox::Find(const tchar* pszText, size_t nFirst) const
{
	return SendMessage(CB_FINDSTRING, nFirst, reinterpret_cast<LPARAM>(pszText));
}

inline size_t CComboBox::FindExact(const tchar* pszText, size_t nFirst) const
{
	return SendMessage(CB_FINDSTRINGEXACT, nFirst, reinterpret_cast<LPARAM>(pszText));
}

inline size_t CComboBox::FindExact(const tstring& text, size_t first) const
{
	return FindExact(text.c_str(), first);
}

inline bool CComboBox::Exists(const tstring& text) const
{
	return (FindExact(text) != Core::npos);
}

inline void CComboBox::ItemData(size_t nItem, LPARAM lData) const
{
	SendMessage(CB_SETITEMDATA, nItem, lData);
}

inline LPARAM CComboBox::ItemData(size_t nItem) const
{
	return SendMessage(CB_GETITEMDATA, nItem, 0L);
}

inline void CComboBox::ItemPtr(size_t nItem, void* pData) const
{
	SendMessage(CB_SETITEMDATA, nItem, reinterpret_cast<LPARAM>(pData));
}

inline void* CComboBox::ItemPtr(size_t nItem) const
{
	return reinterpret_cast<void*>(SendMessage(CB_GETITEMDATA, nItem, 0L));
}

inline size_t CComboBox::CurSel() const
{
	return SendMessage(CB_GETCURSEL, 0, 0L);
}

inline void CComboBox::CurSel(size_t nItem) const
{
	SendMessage(CB_SETCURSEL, nItem, 0L);
}

inline void CComboBox::RemoveSelection()
{
	SendMessage(CB_SETCURSEL, static_cast<WPARAM>(-1), 0L);
}

inline size_t CComboBox::CurSel(const tchar* pszText, size_t nFirst) const
{
	return SendMessage(CB_SELECTSTRING, nFirst, reinterpret_cast<LPARAM>(pszText));
}

inline size_t CComboBox::Select(const tchar* pszText, size_t nFirst) const
{
	size_t nItem = FindExact(pszText, nFirst);

	CurSel(nItem);

	return nItem;
}

inline size_t CComboBox::Select(const tstring& text, size_t first) const
{
	return Select(text.c_str(), first);
}

inline size_t CComboBox::TextLength(size_t nItem) const
{
	LRESULT lResult = SendMessage(CB_GETLBTEXTLEN, nItem, 0L);

	ASSERT(lResult != CB_ERR);

	return lResult;
}

inline size_t CComboBox::TextLength() const
{
	LRESULT lResult = SendMessage(WM_GETTEXTLENGTH, 0, 0L);

	ASSERT(lResult != CB_ERR);

	return lResult;
}

#endif //COMBOBOX_HPP
