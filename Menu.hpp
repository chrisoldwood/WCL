/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MENU.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMenu class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MENU_HPP
#define MENU_HPP

#if _MSC_VER > 1000
#pragma once
#endif

// Forward declarations.
class CPopupMenu;

/******************************************************************************
**
** The base class for menus.
**
*******************************************************************************
*/

class CMenu /*: private NotCopyable*/
{
public:
	//
	// Constructors/Destructor.
	//
	CMenu();
	CMenu(HMENU	hMenu);
	virtual ~CMenu();

	//
	// Member access.
	//
	HMENU Handle() const;

	//
	// General methods.
	//
	void InsertCmd(uint nPos, uint iCmdID, const tchar* pszText);
	void AppendCmd(uint iCmdID, const tchar* pszText);
	void AppendCmd(uint commandId, const tstring& text);

	//
	// Item by command methods.
	//
	void SetCmdText(uint iCmdID, const tchar* pszText);
	void EnableCmd(uint iCmdID, bool bEnable = true);
	void CheckCmd(uint iCmdID, bool bCheck = true);
	void RemoveCmd(uint iCmdID);

	//
	// Item by position methods.
	//
	int     ItemCount() const;
	void    EnableItem(int nPos, bool bEnable = true);
	CString GetItemText(int nPos);
	CPopupMenu GetItemPopup(int nPos);
	void    SetItemPopup(int nPos, const CPopupMenu& rMenu, const tchar* pszText);
	void    RemoveItem(int nPos);

protected:
	//
	// Members.
	//
	HMENU	m_hMenu;

private:
	// NotCopyable.
	CMenu(const CMenu&);
	CMenu& operator=(const CMenu&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HMENU CMenu::Handle() const
{
	return m_hMenu;
}

inline void CMenu::InsertCmd(uint nPos, uint iCmdID, const tchar* pszText)
{
	::InsertMenu(m_hMenu, nPos, MF_BYPOSITION | MF_STRING, iCmdID, pszText);
}

inline void CMenu::AppendCmd(uint iCmdID, const tchar* pszText)
{
	::AppendMenu(m_hMenu, MF_STRING, iCmdID, pszText);
}

inline void CMenu::AppendCmd(uint commandId, const tstring& text)
{
	::AppendMenu(m_hMenu, MF_STRING, commandId, text.c_str());
}

inline void CMenu::SetCmdText(uint iCmdID, const tchar* pszText)
{
	::ModifyMenu(m_hMenu, iCmdID, MF_BYCOMMAND | MF_STRING, iCmdID, pszText);
}

inline void CMenu::EnableCmd(uint iCmdID, bool bEnable)
{
	uint iValue = bEnable ? (MF_BYCOMMAND | MF_ENABLED) : (MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	::EnableMenuItem(m_hMenu, iCmdID, iValue);
}

inline void CMenu::CheckCmd(uint iCmdID, bool bCheck)
{
	uint iValue = bCheck ? MF_CHECKED : MF_UNCHECKED;

	::CheckMenuItem(m_hMenu, iCmdID, MF_BYCOMMAND | iValue);
}

inline void CMenu::RemoveCmd(uint iCmdID)
{
	::RemoveMenu(m_hMenu, iCmdID, MF_BYCOMMAND);
}

inline int CMenu::ItemCount() const
{
	return ::GetMenuItemCount(m_hMenu);
}

inline void CMenu::EnableItem(int nPos, bool bEnable)
{
	uint iValue = bEnable ? (MF_BYPOSITION | MF_ENABLED) : (MF_BYPOSITION | MF_DISABLED | MF_GRAYED);

	::EnableMenuItem(m_hMenu, nPos, iValue);
}

inline void CMenu::RemoveItem(int nPos)
{
	::RemoveMenu(m_hMenu, nPos, MF_BYPOSITION);
}

#endif //MENU_HPP
