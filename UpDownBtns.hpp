/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		UPDOWNBTNS.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CUpDownBtns class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef UPDOWNBTNS_HPP
#define UPDOWNBTNS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"
#include <commctrl.h>

/******************************************************************************
** 
** This is an up-down buttons control.
**
*******************************************************************************
*/

class CUpDownBtns : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CUpDownBtns();

	//
	// Standard methods.
	//
	bool PosValid();

	int  Pos();
	void Pos(int nPos);

	void Range(int nMin, int nMax);

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

inline bool CUpDownBtns::PosValid()
{
	return (HIWORD(SendMessage(UDM_GETPOS, 0, 0)) == 0);
}

inline int CUpDownBtns::Pos()
{
	LRESULT result = SendMessage(UDM_GETPOS, 0, 0);

	return static_cast<int>(result);
}

inline void CUpDownBtns::Pos(int nPos)
{
	SendMessage(UDM_SETPOS, 0, MAKELONG(nPos, 0));
}

inline void CUpDownBtns::Range(int nMin, int nMax)
{
	SendMessage(UDM_SETRANGE, 0, MAKELONG(nMin, nMax));
}

#endif //UPDOWNBTNS_HPP
