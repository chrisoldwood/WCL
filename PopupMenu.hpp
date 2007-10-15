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

#if _MSC_VER > 1000
#pragma once
#endif

#include "Menu.hpp"

// Forward declarations.
class CWnd;
class CPoint;

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
	CPopupMenu(uint iRscID);
	~CPopupMenu();

	void LoadRsc(uint iRscID);

	uint TrackMenu(CWnd& rParent, const CPoint& ptOrigin);

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
