/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BUSYCURSOR.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CBusyCursor class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BUSYCURSOR_HPP
#define BUSYCURSOR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** Shows the hourglass cursor on construction and restores it on destruction.
**
*******************************************************************************
*/

class CBusyCursor
{
public:
	//
	// Constructors/Destructor.
	//
	CBusyCursor();
	~CBusyCursor();

	void Restore();
	
protected:
	//
	// Members.
	//
	HCURSOR	m_hOldCursor;	// The old cursor.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //BUSYCURSOR_HPP
