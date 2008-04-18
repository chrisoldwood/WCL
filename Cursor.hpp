/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CURSOR.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CCursor class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CURSOR_HPP
#define CURSOR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Point.hpp"

/******************************************************************************
** 
** This class wraps a standard GDI cursor.
**
*******************************************************************************
*/

class CCursor
{
public:
	//
	// Constructors/Destructor.
	//
	CCursor();
	~CCursor();

	void LoadRsc(uint nRscID);
	void LoadRsc(const tchar* pszRsc);
	
	//
	// Member access.
	//
	HCURSOR Handle() const;

	//
	// Class methods.
	//

	//! Get the current cursor postion in screen co-ordinates.
	static CPoint CurrentPos();

	//! Get the current cursor postion in window co-ordinates.
	static CPoint CurrentPos(HWND hWnd);

protected:
	//
	// Members.
	//
	HCURSOR	m_hCursor;
	bool	m_bOwner;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HCURSOR CCursor::Handle() const
{
	return m_hCursor;
}

#endif //CURSOR_HPP
