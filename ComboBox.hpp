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

/******************************************************************************
** 
** This is a combobox control.
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
	int Count() const;
	void TextLimit(int iLimit) const;
	int Add(const char* pszText) const;
	int Add(const char* pszText, LPARAM lData) const;
	int Add(const char* pszText, void*  pData) const;
	int Insert(const char* pszText, int iPos) const;
	int Delete(int iItem) const;
	int Find(const char* pszText, int iFirst = -1) const;
	int FindExact(const char* pszText, int iFirst = -1) const;
	void ItemData(int iItem, LPARAM lData) const;
	void ItemPtr(int iItem, void* pData) const;
	LPARAM ItemData(int iItem) const;
	void*  ItemPtr(int iItem) const;
	int CurSel() const;
	void CurSel(int iItem) const;
	int CurSel(const char* pszText, int iFirst = -1) const;
	int TextLength(int iPos) const;
	int TextLength() const;
	CString Text(int iPos) const;
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

inline int CComboBox::Count() const
{
	return (int)SendMessage(CB_GETCOUNT, 0, 0L);
}

inline void CComboBox::TextLimit(int iLimit) const
{
	SendMessage(CB_LIMITTEXT, iLimit, 0L);
}

inline int CComboBox::Add(const char* pszText) const
{
	return (int)SendMessage(CB_ADDSTRING, 0, (LPARAM)(LPCSTR) pszText);
}

inline int CComboBox::Add(const char* pszText, LPARAM lData) const
{
	int nPos = Add(pszText);

	ItemData(nPos, lData);

	return nPos;
}

inline int CComboBox::Add(const char* pszText, void*  pData) const
{
	int nPos = Add(pszText);

	ItemPtr(nPos, pData);

	return nPos;
}

inline int CComboBox::Insert(const char* pszText, int iPos) const
{
	return (int)SendMessage(CB_INSERTSTRING, iPos, (LPARAM)(LPCSTR) pszText);
}

inline int CComboBox::Delete(int iItem) const
{
	return (int)SendMessage(CB_DELETESTRING, iItem, 0L);
}

inline int CComboBox::Find( const char* pszText, int iFirst) const
{
	return (int)SendMessage(CB_FINDSTRING, iFirst, (LPARAM)(LPCSTR) pszText);
}

inline int CComboBox::FindExact(const char* pszText, int iFirst) const
{
	return (int)SendMessage(CB_FINDSTRINGEXACT, iFirst, (LPARAM)(LPCSTR) pszText);
}

inline void CComboBox::ItemData(int iItem, LPARAM lData) const
{
	SendMessage(CB_SETITEMDATA, iItem, lData);
}

inline LPARAM CComboBox::ItemData(int iItem) const
{
	return SendMessage(CB_GETITEMDATA, iItem, 0L);
}

inline void CComboBox::ItemPtr(int iItem, void* pData) const
{
	SendMessage(CB_SETITEMDATA, iItem, (LPARAM)pData);
}

inline void* CComboBox::ItemPtr(int iItem) const
{
	return (void*) SendMessage(CB_GETITEMDATA, iItem, 0L);
}

inline int CComboBox::CurSel() const
{
	return (int) SendMessage(CB_GETCURSEL, 0, 0L);
}

inline void CComboBox::CurSel(int iItem) const
{
	SendMessage(CB_SETCURSEL, iItem, 0L);
}

inline int CComboBox::CurSel(const char* pszText, int iFirst) const
{
	return (int)SendMessage(CB_SELECTSTRING, iFirst, (LPARAM)(LPCSTR) pszText);
}

inline int CComboBox::TextLength(int iPos) const
{
	return (int)SendMessage(CB_GETLBTEXTLEN, iPos, 0L);
}

inline int CComboBox::TextLength() const
{
	return (int)SendMessage(WM_GETTEXTLENGTH, 0, 0L);
}

#endif //COMBOBOX_HPP
