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

/******************************************************************************
** 
** This is an editbox control.
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
	~CEditBox();

	//
	// Standard methods.
	//
	void TextLimit(int iLimit) const;
	void ReadOnly(bool bReadOnly = true) const;
	void Select(int iFirstChar = 0, int iLastChar = -1) const;
	void Selected(int& nStart, int& nEnd) const;
	void Text(const char* pszText);
	void ReplaceSel(const char* pszText, bool bCanUndo = true);
	void Append(const char* pszText);
	int  TextLength() const;
	CString Text() const;

	//
	// Custom methods.
	//
	void Filter(const char* pszFilter, bool bAllow = true);
	void Filter(char cFilter, bool bAllow = true);

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
	virtual bool FilterKey(char cChar);

	//
	// Internal methods.
	//
	void AllocFilterMap();
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

inline void	CEditBox::Select(int iFirstChar, int iLastChar) const
{
	SendMessage(EM_SETSEL, iFirstChar, iLastChar);
}

inline void CEditBox::Selected(int& nStart, int& nEnd) const
{
	DWORD dwFirst, dwLast;

	SendMessage(EM_GETSEL, (WPARAM)&dwFirst, (LPARAM)&dwLast);

	nStart = dwFirst;
	nEnd   = dwLast;
}

inline void CEditBox::Text(const char* pszText)
{
	Title(pszText);
}

inline void CEditBox::ReplaceSel(const char* pszText, bool bCanUndo)
{
	SendMessage(EM_REPLACESEL, bCanUndo, (LPARAM)pszText);
}

inline int CEditBox::TextLength() const
{
	return (int)SendMessage(WM_GETTEXTLENGTH, 0, 0L);
}

inline CString CEditBox::Text() const
{
	return Title();
}

#endif //EDITBOX_HPP
