/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CTRLWND.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CCtrlWnd class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CTRLWND_HPP
#define CTRLWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "PopupWnd.hpp"

/******************************************************************************
**
** This is the base class for all window child controls.
**
*******************************************************************************
*/

class CCtrlWnd : public CPopupWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CCtrlWnd();
	virtual ~CCtrlWnd();

	virtual bool PreRegister();
	virtual bool Create(CMsgWnd& rParent, uint iID, const CRect& rcPos);
	virtual bool Create(CMsgWnd& rParent, uint iID, const CRect& rcPos, DWORD dwExStyle, DWORD dwStyle);
	virtual bool Create(CMsgWnd& rParent, uint iID, HWND hWnd);

protected:
	//
	// Members.
	//
	uint		m_iID;
	CMsgWnd*	m_pParent;
	CRect		m_rcPos;

	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

private:
	// NotCopyable.
	CCtrlWnd(const CCtrlWnd&);
	CCtrlWnd& operator=(const CCtrlWnd&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //CTRLWND_HPP
