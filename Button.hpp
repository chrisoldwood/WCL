/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BUTTON.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CButton class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BUTTON_HPP
#define BUTTON_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"

/******************************************************************************
** 
** This is a button control.
**
*******************************************************************************
*/

class CButton : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CButton();

	//
	// Standard methods.
	//

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

#endif //BUTTON_HPP
