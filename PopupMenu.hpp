/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		POPUPMENU.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPopupMenu class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef POPUPMENU_HPP
#define POPUPMENU_HPP

/******************************************************************************
** 
** This is a menu derived class for popup (context) menus.
**
*******************************************************************************
*/

class CPopupMenu : public CMenu
{
public:
	//
	// Constructors/Destructor.
	//
	CPopupMenu();
	CPopupMenu(HMENU hMenu);
	~CPopupMenu();

	void LoadRsc(uint iRscID);

protected:
	//
	// Members.
	//
	HMENU	m_hParent;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //POPUPMENU_HPP
