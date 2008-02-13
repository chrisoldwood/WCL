/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MENU.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMenu class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Menu.hpp"
#include "PopupMenu.hpp"

/******************************************************************************
** Method:		Constructor
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMenu::CMenu()
	: m_hMenu(NULL)
{
}

/******************************************************************************
** Method:		Constructor
**
** Description:	.
**
** Parameters:	hMenu	The handle to a menu.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMenu::CMenu(HMENU	hMenu)
	: m_hMenu(hMenu)
{
}

/******************************************************************************
** Method:		Destructor
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMenu::~CMenu()
{
}

/******************************************************************************
** Method:		GetItemPopup()
**
** Description:	Gets the popup menu at the position given.
**
** Parameters:	nPos	The position of the item.
**
** Returns:		The popup menu.
**
*******************************************************************************
*/

CPopupMenu CMenu::GetItemPopup(int nPos)
{
	ASSERT(m_hMenu != NULL);

	// Get the popup menu.
	HMENU hPopup = ::GetSubMenu(m_hMenu, nPos);

	ASSERT(hPopup != NULL);

	return CPopupMenu(hPopup);
}

/******************************************************************************
** Method:		SetItemPopup()
**
** Description:	Sets the popup menu at the position given.
**
** Parameters:	nPos	The position of the item.
**				rMenu	The popup menu to use.
**				pszText	The popup menus' name.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMenu::SetItemPopup(int nPos, const CPopupMenu& rMenu, const tchar* pszText)
{
	::ModifyMenu(m_hMenu, nPos, MF_BYPOSITION | MF_POPUP | MF_STRING, reinterpret_cast<uint>(rMenu.Handle()), pszText);
}

/******************************************************************************
** Method:		GetItemText()
**
** Description:	Gets the text for an item by position.
**
** Parameters:	nPos	The position of the item.
**
** Returns:		The items text.
**
*******************************************************************************
*/

CString CMenu::GetItemText(int nPos)
{
	CString str;
	size_t  nChars = ::GetMenuString(m_hMenu, nPos, NULL, 0, MF_BYPOSITION);

	// Get the string.
	str.BufferSize(nChars+1);

	::GetMenuString(m_hMenu, nPos, str.Buffer(), nChars+1, MF_BYPOSITION);

	return str;
}
