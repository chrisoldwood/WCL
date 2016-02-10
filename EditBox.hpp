/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EDITBOX.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CEditBox class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EDITBOX_HPP
#define EDITBOX_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"

/******************************************************************************
**
** This is an edit-box control.
**
*******************************************************************************
*/

class CEditBox : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CEditBox();
	virtual	~CEditBox();

	//
	// Standard methods.
	//
	void TextLimit(int iLimit) const;
	void ReadOnly(bool bReadOnly = true) const;
	void Select(size_t iFirstChar = 0, size_t iLastChar = Core::npos) const;
	void Text(const tchar* pszText);
	void Text(const tstring& strText);
	void ReplaceSel(const tchar* pszText, bool bCanUndo = true);
	void Append(const tchar* pszText);
	void TabWidth(uint nWidth);

	void    Selected(int& nStart, int& nEnd) const;
	size_t  TextLength() const;
	CString Text() const;

	//
	// Custom methods.
	//
	void SetFilterDefault(bool bAllow);
	void Filter(const tchar* pszFilter, bool bAllow = true);
	void Filter(tchar cFilter, bool bAllow = true);

protected:
	//
	// Members.
	//
	bool*	m_pFilter;

	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message handlers.
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnReflectedCtrlMsg(uint iMsg);
	virtual bool FilterKey(tchar cChar);

	//
	// Internal methods.
	//
	void AllocFilterMap();

private:
	// NotCopyable.
	CEditBox(const CEditBox&);
	CEditBox& operator=(const CEditBox&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CEditBox::TextLimit(int iLimit) const
{
	SendMessage(EM_LIMITTEXT, iLimit, 0L);
}

inline void CEditBox::ReadOnly(bool bReadOnly) const
{
	SendMessage(EM_SETREADONLY, bReadOnly, 0L);
}

inline void	CEditBox::Select(size_t iFirstChar, size_t iLastChar) const
{
	SendMessage(EM_SETSEL, iFirstChar, iLastChar);
}

inline void CEditBox::Selected(int& nStart, int& nEnd) const
{
	DWORD dwFirst, dwLast;

	SendMessage(EM_GETSEL, reinterpret_cast<WPARAM>(&dwFirst), reinterpret_cast<LPARAM>(&dwLast));

	nStart = dwFirst;
	nEnd   = dwLast;
}

inline void CEditBox::Text(const tchar* pszText)
{
	Title(pszText);
}

inline void CEditBox::Text(const tstring& strText)
{
	Title(strText.c_str());
}

inline void CEditBox::ReplaceSel(const tchar* pszText, bool bCanUndo)
{
	SendMessage(EM_REPLACESEL, bCanUndo, reinterpret_cast<LPARAM>(pszText));
}

inline void CEditBox::TabWidth(uint nWidth)
{
	::SendMessage(m_hWnd, EM_SETTABSTOPS, 1, reinterpret_cast<LPARAM>(&nWidth));
}

inline size_t CEditBox::TextLength() const
{
	return SendMessage(WM_GETTEXTLENGTH, 0, 0L);
}

inline CString CEditBox::Text() const
{
	return Title();
}

#endif //EDITBOX_HPP
