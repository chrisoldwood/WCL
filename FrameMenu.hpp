/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FRAMEMENU.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CFrameMenu class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FRAMEMENU_HPP
#define FRAMEMENU_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Menu.hpp"
#include "PopupMenu.hpp"

/******************************************************************************
**
** This is a menu derived class for frame window menus.
**
*******************************************************************************
*/

class CFrameMenu : public CMenu
{
public:
	//
	// Constructors/Destructor.
	//
	CFrameMenu();
	~CFrameMenu();

	void LoadRsc(uint iRscID);

	//
	// Methods.
	//
//	CPopupMenu Popup(uint nPos);

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/
/*
inline CPopupMenu CFrameMenu::Popup(uint nPos)
{
	return CPopupMenu(::GetSubMenu(m_hMenu, nPos));
}
*/
#endif //FRAMEMENU_HPP
