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
	int Count() const;
	int Add(const char* pszText) const;
	int Insert(const char* pszText, int iPos) const;
	int Delete(int iItem) const;
	int Find(const char* pszText, int iFirst = -1) const;
	int FindExact(const char* pszText, int iFirst = -1) const;
	void ItemData(int iItem, LPARAM lData) const;
	LPARAM ItemData(int iItem) const;
	int CurSel() const;
	void CurSel(int iItem) const;
	int  CurSel(const char* pszText, int iFirst = -1) const;
	bool IsSel(int iItem) const;
	int TextLength(int iPos) const;
	int Text(char* pszText, int iPos) const;
	CString Text(int iPos) const;
	void SetTabStops(int iNumTabStops, const int* pTabStops);
	void ItemHeight(int nItem, int nHeight);

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

inline int CListBox::Count() const
{
	return (int)SendMessage(LB_GETCOUNT, 0, 0L);
}

inline int CListBox::Add(const char* pszText) const
{
	return (int)SendMessage(LB_ADDSTRING, 0, (LPARAM)(LPCSTR) pszText);
}

inline int CListBox::Insert(const char* pszText, int iPos) const
{
	return (int)SendMessage(LB_INSERTSTRING, iPos, (LPARAM)(LPCSTR) pszText);
}

inline int CListBox::Delete(int iItem) const
{
	return (int)SendMessage(LB_DELETESTRING, iItem, 0L);
}

inline int CListBox::Find(const char* pszText, int iFirst) const
{
	return (int)SendMessage(LB_FINDSTRING, iFirst, (LPARAM)(LPCSTR) pszText);
}

inline int CListBox::FindExact(const char* pszText, int iFirst) const
{
	return (int)SendMessage(LB_FINDSTRINGEXACT, iFirst, (LPARAM)(LPCSTR) pszText);
}

inline void CListBox::ItemData(int iItem, LPARAM lData) const
{
	SendMessage(LB_SETITEMDATA, iItem, lData);
}

inline LPARAM CListBox::ItemData(int iItem) const
{
	return SendMessage(LB_GETITEMDATA, iItem, 0L);
}

inline int CListBox::CurSel() const
{
	return (int) SendMessage(LB_GETCURSEL, 0, 0L);
}

inline void CListBox::CurSel(int iItem) const
{
	SendMessage(LB_SETCURSEL, iItem, 0L);
}

inline int CListBox::CurSel(const char* pszText, int iFirst) const
{
	return (int)SendMessage(LB_SELECTSTRING, iFirst, (LPARAM)(LPCSTR) pszText);
}

inline bool CListBox::IsSel(int iItem) const
{
	return (bool) SendMessage(LB_GETSEL, iItem, 0L);
}

inline int CListBox::TextLength(int iPos) const
{
	return (int)SendMessage(LB_GETTEXTLEN, iPos, 0L);
}

inline int CListBox::Text(char* pszText, int iPos) const
{
	return (int)SendMessage(LB_GETTEXT, iPos, (LPARAM)(LPCSTR) pszText);
}

inline void CListBox::SetTabStops(int iNumTabStops, const int* pTabStops)
{
	SendMessage(LB_SETTABSTOPS, iNumTabStops, (LPARAM)(void*)pTabStops);
}

inline void CListBox::ItemHeight(int nItem, int nHeight)
{
	SendMessage(LB_SETITEMHEIGHT, nItem, nHeight);
}

#endif //LISTBOX_HPP
