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
	CDecimalBox(bool bSigned, int nIntDigits, int nDecDigits = 0, int nFlags = 0x00);
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
	int		m_nIntDigits;	// Number of integer digits.
	int		m_nDecDigits;	// Number of decimal digits.
	int		m_nMaxChars;	// Maximum number of chars.
	int		m_nFlags;		// Options.

	//
	// Message handlers.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual bool FilterKey(char cChar);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //DECIMALBOX_HPP
