/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DECIMALBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDecimalBox class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <stdio.h>

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDecimalBox::CDecimalBox(bool bSigned, int nIntDigits, int nDecDigits)
	: m_bSigned(bSigned)
	, m_nIntDigits(nIntDigits)
	, m_nDecDigits(nDecDigits)
	, m_nMaxChars(nIntDigits + nDecDigits)
{
	// Setup character filter.
	CString strFilter("0123456789");

	if (m_bSigned)
	{
		strFilter += "+-";
		m_nMaxChars++;
	}

	if (nDecDigits)
	{
		strFilter += '.';
		m_nMaxChars++;
	}

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
** Method:		Value()
**
** Description:	Gets the value.
**
** Parameters:	None.
**
** Returns:		The value.
**
*******************************************************************************
*/

double CDecimalBox::Value() const
{
	return atof(Text());
}

/******************************************************************************
** Method:		Value()
**
** Description:	Sets the value.
**
** Parameters:	dValue	The value.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDecimalBox::Value(double dValue)
{
	char szText[50];

	sprintf(szText, "%.*f", m_nDecDigits, dValue);

	Text(szText);
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

bool CDecimalBox::FilterKey(char cChar)
{
	// Check base class first.
	if (CEditBox::FilterKey(cChar))
		return true;

	// Is a decimal point or sign character?
	if ( (cChar == '.') || (cChar == '+') || (cChar == '-') )
	{
		char szText[50];

		// Get the current text.
		SendMessage(WM_GETTEXT, 50, (LPARAM)(LPCSTR)szText);

		// Is a decimal point AND already have one?
		if ( (cChar == '.') && (strchr(szText, '.') != NULL) )
			return true;
	}

	return false;
}
