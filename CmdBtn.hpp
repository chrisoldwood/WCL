/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CMDBTN.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CCmdButton class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CMDBTN_HPP
#define CMDBTN_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Button.hpp"
#include "WclTypes.hpp"

/******************************************************************************
**
** This is a bitmap based button control used on a tool bar.
**
*******************************************************************************
*/

class CCmdButton : public CButton
{
public:
	//
	// Constructors/Destructor.
	//
	CCmdButton();

protected:
	//
	// Members.
	//
	bool	m_bOnToolbar;
	bool	m_bTimerOn;

	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnNCDestroy();
	virtual void OnDrawItem(uint iID, uint iAction, uint iState, CDC& rDC, uint iItem, const CRect& rcItem);
	virtual void OnMouseMove(const CPoint& ptCursor, WCL::KeyFlags iKeyFlags);
	virtual void OnTimer(WCL::TimerID iTimerID);

	//
	// Class members.
	//
	static CCmdButton* g_pActiveBtn;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //CMDBTN_HPP
