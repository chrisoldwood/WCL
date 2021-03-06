/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CHECKBOX.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CCheckBox class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"

/******************************************************************************
**
** This is a check-box control.
**
*******************************************************************************
*/

class CCheckBox : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CCheckBox();

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

inline void CCheckBox::Check(bool bCheck) const
{
	SendMessage(BM_SETCHECK, bCheck, 0);
}

inline bool CCheckBox::IsChecked() const
{
	return static_cast<bool>(SendMessage(BM_GETCHECK, 0, 0));
}

#endif //CHECKBOX_HPP
