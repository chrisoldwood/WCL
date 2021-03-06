/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PATHEDITBOX.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPathEditBox class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PATHEDITBOX_HPP
#define PATHEDITBOX_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "EditBox.hpp"

/******************************************************************************
** 
** This edit box derived control is used for entering file paths.
**
*******************************************************************************
*/

class CPathEditBox : public CEditBox
{
public:
	//
	// Constructors/Destructor.
	//
	CPathEditBox();
	~CPathEditBox();
	
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

#endif //PATHEDITBOX_HPP
