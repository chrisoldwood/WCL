/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DECIMALBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDecimalBox class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "DecimalBox.hpp"
#include <stdio.h>
#include "StrCvt.hpp"
#include <tchar.h>
#include <Core/AnsiWide.hpp>
#include <Core/StringUtils.hpp>
#include <Core/BadLogicException.hpp>

////////////////////////////////////////////////////////////////////////////////
// Constants.

#ifdef _MSC_VER
static const size_t MAX_DBL_STR_LEN = _CVTBUFSIZE;
#else
static const size_t MAX_DBL_STR_LEN = 309 + 40; // == _CVTBUFSIZE [VS2003]
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	Constructor for defining real numbers.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDecimalBox::CDecimalBox(bool bSigned, uint nIntDigits, uint nDecDigits, uint nFlags)
	: m_bSigned(bSigned)
	, m_nIntDigits(nIntDigits)
	, m_nDecDigits(nDecDigits)
	, m_nMaxChars(nIntDigits + nDecDigits)
	, m_nFlags(nFlags)
{
	// Setup character filter.
	CString strFilter(TXT("0123456789"));

	// Allow signed values?
	if (m_bSigned)
	{
		strFilter += TXT("+-");
		++m_nMaxChars;
	}

	// Allow decimal point?
	if (nDecDigits)
	{
		strFilter += TXT('.');
		++m_nMaxChars;
	}
/*
	// Allow fractions?
	if (m_nFlags & ALLOW_FRACTIONS)
	{
		strFilter += "/ ";
		++m_nMaxChars;
	}
*/
	Filter(strFilter);
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDecimalBox::~CDecimalBox()
{
}

/******************************************************************************
** Method:		RealValue()
**
** Description:	Gets the value.
**
** Parameters:	None.
**
** Returns:		The value.
**
*******************************************************************************
*/

double CDecimalBox::RealValue() const
{
	return CStrCvt::ParseDouble(Text());
}

/******************************************************************************
** Method:		RealValue()
**
** Description:	Sets the value.
**
** Parameters:	dValue	The value.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDecimalBox::RealValue(double dValue)
{
	tchar szText[MAX_DBL_STR_LEN+1] = { 0 };

	int nResult = _sntprintf(szText, MAX_DBL_STR_LEN, TXT("%.*f"), m_nDecDigits, dValue);

	ASSERT(nResult >= 0);

	if (nResult < 0)
		throw Core::BadLogicException(Core::fmt(TXT("Insufficient buffer size used in CDecimalBox::RealValue(). Result: %d"), nResult));

	// Remove trailing zeroes?
	if (m_nFlags & NO_TRAIL_ZEROES)
	{
		tchar* pszDecPt = tstrchr(szText, TXT('.'));

		// Value has a decimal point?
		if (pszDecPt != NULL)
		{
			// Calculate the end of the string.
			tchar* pszEOS = pszDecPt + tstrlen(pszDecPt) - 1;

			// Remove trailing zeroes.
			while ( (pszEOS > pszDecPt) && (*pszEOS == TXT('0')) )
				*pszEOS-- = TXT('\0');

			// Remove decimal point?
			if (pszEOS == pszDecPt)
				*pszDecPt = TXT('\0');
		}
	}

	Text(szText);
}

/******************************************************************************
** Method:		IntValue()
**
** Description:	Gets the value as an integer.
**
** Parameters:	None.
**
** Returns:		The value.
**
*******************************************************************************
*/

int CDecimalBox::IntValue() const
{
	ASSERT(m_nDecDigits == 0);

	return CStrCvt::ParseInt(Text());
}

/******************************************************************************
** Method:		IntValue()
**
** Description:	Sets an integer value.
**
** Parameters:	nValue	The value.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDecimalBox::IntValue(int nValue)
{
	Text(CStrCvt::FormatInt(nValue));
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Set the text limit.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDecimalBox::OnCreate(const CRect&)
{
	TextLimit(m_nMaxChars);
}

/******************************************************************************
** Method:		FilterKey()
**
** Description:	Called on WM_CHAR to determine if the the keystroke should be
**				allowed or not.
**
** Parameters:	cChar	The character to test.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CDecimalBox::FilterKey(tchar cChar)
{
	// Check base class first.
	if (CEditBox::FilterKey(cChar))
		return true;

	tchar szText[MAX_DBL_STR_LEN+1] = { 0 };
	int	 nSelStart, nSelEnd;

	// Get the current text.
	Edit_GetText(m_hWnd, szText, MAX_DBL_STR_LEN);

	// Get the current selection.
	Selected(nSelStart, nSelEnd);

	int nSelChars = nSelEnd - nSelStart;

	// Is the sign char?
	if ( (cChar == TXT('+')) || (cChar == TXT('-')) )
	{
		// Caret not at start OR already have sign?
		if ( (nSelStart > 0) || (tstrchr(szText, TXT('+')) != NULL) || (tstrchr(szText, TXT('-')) != NULL) )
			return true;
	}

	// Is a decimal point AND already have one?
	if ( (cChar == TXT('.')) && (tstrchr(szText, TXT('.')) != NULL) )
		return true;

	// Is a fraction separator AND already have one?
	if ( (cChar == TXT('/')) && (tstrchr(szText, TXT('/')) != NULL) )
		return true;

	// Is a fraction separator AND already have one?
	if ( (cChar == TXT(' ')) && (tstrchr(szText, TXT(' ')) != NULL) )
		return true;

	// Allowing decimal places AND is a digit?
	if ( (m_nDecDigits > 0) && (isdigit(cChar)) )
	{
		// Get decimal point position.
		tchar* pszDecPt = tstrchr(szText, TXT('.'));

		// Is decimal point AND caret after it AND no selection
		// AND max decimal places entered?
		if ( (pszDecPt != NULL) && (nSelStart > (pszDecPt - szText)) && (nSelChars < 1)
		  && (tstrlen(pszDecPt + 1) >= m_nDecDigits) )
			return true;
	}

	return false;
}
