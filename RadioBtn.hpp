/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		RADIOBTN.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CRadioBtn class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef RADIOBTN_HPP
#define RADIOBTN_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"

/******************************************************************************
** 
** This is a radio button control.
**
*******************************************************************************
*/

class CRadioBtn : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CRadioBtn();

	//
	// Standard methods.
	//
	void Check(bool bCheck = true) const;
	bool IsChecked() const;

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

inline void CRadioBtn::Check(bool bCheck) const
{
	SendMessage(BM_SETCHECK, bCheck, 0);
}

inline bool CRadioBtn::IsChecked() const
{
	return static_cast<bool>(SendMessage(BM_GETCHECK, 0, 0));
}

#endif //RADIOBTN_HPP
