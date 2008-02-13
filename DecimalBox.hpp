/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DECIMALBOX.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDecimalBox class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef DECIMALBOX_HPP
#define DECIMALBOX_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "EditBox.hpp"

/******************************************************************************
** 
** This class is used for EditBoxes which only allow decimal numbers.
**
*******************************************************************************
*/

class CDecimalBox : public CEditBox
{
public:
	//
	// Constructors/Destructor.
	//
	CDecimalBox(bool bSigned, uint nIntDigits, uint nDecDigits = 0, uint nFlags = 0x00);
	~CDecimalBox();
	
	//
	// Methods.
	//
	double RealValue() const;
	void   RealValue(double dValue);

	int    IntValue() const;
	void   IntValue(int nValue);

	// Flags.
	enum Flags
	{
		DEFAULTS		= 0x00,
		NO_TRAIL_ZEROES	= 0x01,
//		ALLOW_FRACTIONS = 0x02,
	};

protected:
	//
	// Members.
	//
	bool	m_bSigned;		// Allow signed numbers?
	uint	m_nIntDigits;	// Number of integer digits.
	uint	m_nDecDigits;	// Number of decimal digits.
	uint	m_nMaxChars;	// Maximum number of chars.
	uint	m_nFlags;		// Options.

	//
	// Message handlers.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual bool FilterKey(tchar cChar);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //DECIMALBOX_HPP
