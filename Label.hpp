/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LABEL.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CLabel class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef LABEL_HPP
#define LABEL_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"

/******************************************************************************
** 
** This is a text label.
**
*******************************************************************************
*/

class CLabel : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CLabel();

	//
	// Standard methods.
	//
	void Text(const tchar* pszText);

	//! Set the text of the control.
	void setText(const tstring& text);

protected:
	//
	// Members.
	//
	
	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CLabel::Text(const tchar* pszText)
{
	Title(pszText);
}

////////////////////////////////////////////////////////////////////////////////
//! Set the text of the control.

inline void CLabel::setText(const tstring& text)
{
	setTitle(text);
}

#endif //LABEL_HPP
