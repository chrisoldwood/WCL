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

// Forward declarations.
class CPopupMenu;

/******************************************************************************
** 
** The base class for menus.
**
*******************************************************************************
*/

class CMenu
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
	// Item by command methods.
	//
	void SetCmdText(uint iCmdID, const char* pszText);
	void EnableCmd(uint iCmdID, bool bEnable = true);
	void CheckCmd(uint iCmdID, bool bCheck = true);
	
	//
	// Item by position methods.
	//
	void    EnableItem(int nPos, bool bEnable = true);
	CString GetItemText(int nPos);
	void    SetItemPopup(int nPos, const CPopupMenu& rMenu, const char* pszText);

protected:
	//
	// Members.
	//
	HMENU	m_hMenu;
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

inline void CMenu::SetCmdText(uint iCmdID, const char* pszText)
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

inline void CMenu::EnableItem(int nPos, bool bEnable)
{
	uint iValue = bEnable ? (MF_BYPOSITION | MF_ENABLED) : (MF_BYPOSITION | MF_DISABLED | MF_GRAYED);

	::EnableMenuItem(m_hMenu, nPos, iValue);
}

#endif //MENU_HPP
