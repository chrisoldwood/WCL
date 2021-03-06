/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SCREENDC.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CScreenDC class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SCREENDC_HPP
#define SCREENDC_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "DC.hpp"

// Forward declaration.
class CWnd;

/******************************************************************************
**
** This is a Device derived class that is appropriate for drawing to the
** display such as painting windows.
**
*******************************************************************************
*/

class CScreenDC : public CDC
{
public:
	//
	// Constructors/Destructor.
	//
	CScreenDC();
	CScreenDC(const CWnd& rWnd);
	CScreenDC(PAINTSTRUCT& psPaint);
	CScreenDC(HDC hDC);
	virtual	~CScreenDC();

	// RTTI
	virtual	Device Type() const;

protected:
	//
	// Members.
	//
	HWND	m_hWnd;		// Window handle of windows' device context.

private:
	// NotCopyable.
	CScreenDC(const CScreenDC&);
	CScreenDC& operator=(const CScreenDC&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //SCREENDC_HPP
