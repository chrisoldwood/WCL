/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		HINTBAR.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CHintBar class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef HINTBAR_HPP
#define HINTBAR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "CtrlWnd.hpp"

/******************************************************************************
** 
** This is a child window used to display hints.
**
*******************************************************************************
*/

class CHintBar : public CCtrlWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CHintBar();

	//
	// Member setting.
	//
	void Hint(uint iRscID);
	void Hint(const tchar* pszHint);
	
protected:
	//
	// Members.
	//
	CString m_strHint;
	
	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual	void OnPaint(CDC& rDC);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //HINTBAR_HPP
