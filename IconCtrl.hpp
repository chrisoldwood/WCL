/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ICONCTRL.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CIconCtrl class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ICONCTRL_HPP
#define ICONCTRL_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"

/******************************************************************************
** 
** This is a static control used to display an Icon.
**
*******************************************************************************
*/

class CIconCtrl : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CIconCtrl();
	
	//
	// Standard methods.
	//
	void Icon(HICON hIcon);
	void Icon(uint nRscID);

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

inline void CIconCtrl::Icon(HICON hIcon)
{
	::SendMessage(m_hWnd, STM_SETICON, reinterpret_cast<WPARAM>(hIcon), 0L);
}

#endif // ICONCTRL_HPP
