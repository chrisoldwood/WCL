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
	CPopupMenu Popup(int nPos);

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

inline CPopupMenu CFrameMenu::Popup(int nPos)
{
	return CPopupMenu(::GetSubMenu(m_hMenu, nPos));
}

#endif //FRAMEMENU_HPP
