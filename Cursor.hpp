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
	void LoadRsc(const char* pszRsc);
	
	//
	// Member access.
	//
	HCURSOR Handle() const;

	//
	// Class methods.
	//
	static CPoint CurrentPos();

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

inline void CCursor::LoadRsc(const char* pszRsc)
{
	ASSERT(m_hCursor == NULL);

	m_hCursor = ::LoadCursor(NULL, pszRsc);
	m_bOwner  = false;

	ASSERT(m_hCursor != NULL);
}

inline HCURSOR CCursor::Handle() const
{
	return m_hCursor;
}

inline CPoint CCursor::CurrentPos()
{
	CPoint ptCursor;

	::GetCursorPos(&ptCursor);

	return ptCursor;
}

#endif //CURSOR_HPP
