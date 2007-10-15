/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROGRESSBAR.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CProgressBar class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"
#include <commctrl.h>

/******************************************************************************
** 
** This is a progress bar control.
**
*******************************************************************************
*/

class CProgressBar : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CProgressBar();

	//
	// Standard methods.
	//
	void Pos(int nPos);
	void Range(int nMin, int nMax);

	void IncPos(int nInc);

	void StepSize(int nStepSize);
	void StepPos();

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

inline void CProgressBar::Pos(int nPos)
{
	SendMessage(PBM_SETPOS, nPos, 0);
}

inline void CProgressBar::Range(int nMin, int nMax)
{
	SendMessage(PBM_SETRANGE, 0, MAKELPARAM(nMin, nMax));
}

inline void CProgressBar::IncPos(int nInc)
{
	SendMessage(PBM_DELTAPOS, nInc, 0);
}

inline void CProgressBar::StepSize(int nStepSize)
{
	SendMessage(PBM_SETSTEP, nStepSize, 0);
}

inline void CProgressBar::StepPos()
{
	SendMessage(PBM_SETSTEP, 0, 0);
}

#endif //PROGRESSBAR_HPP
