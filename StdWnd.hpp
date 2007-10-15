/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STDWND.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CStdWnd class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STDWND_HPP
#define STDWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "CtrlWnd.hpp"

/******************************************************************************
** 
** This is the base class for all built-in window controls.
**
*******************************************************************************
*/

class CStdWnd : public CCtrlWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CStdWnd();
	virtual	~CStdWnd();

protected:
	//
	// Window creation template methods.
	//
	virtual bool Register(WNDCLASS& rParams);

	//
	// Message handlers.
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //STDWND_HPP
