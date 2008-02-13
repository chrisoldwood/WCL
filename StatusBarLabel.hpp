/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATUSBARLABEL.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CStatusBarLabel class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATUSBARLABEL_HPP
#define STATUSBARLABEL_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StatusBarPanel.hpp"

/******************************************************************************
** 
** A status bar field which contains text.
**
*******************************************************************************
*/

class CStatusBarLabel : public CStatusBarPanel
{
public:
	//
	// Constructors/Destructor.
	//
	CStatusBarLabel(size_t nChars);
	virtual	~CStatusBarLabel();
	
	//
	// Methods.
	//
	void SetLabel(const tchar* pszLabel);

protected:
	//
	// Members.
	//
	size_t	m_nChars;			// Width in characters.
	CString	m_strLabel;			// Text value.

	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnPaint(CDC& rDC);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // STATUSBARLABEL_HPP
