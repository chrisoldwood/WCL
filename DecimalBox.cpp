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

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

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

CDecimalBox::CDecimalBox(bool bSigned, int nIntDigits, int nDecDigits, int nFlags)
	: m_bSigned(bSigned)
	, m_nIntDigits(nIntDigits)
	, m_nDecDigits(nDecDigits)
	, m_nMaxChars(nIntDigits + nDecDigits)
	, m_nFlags(nFlags)
{
	// Setup character filter.
	CString strFilter("0123456789");

	// Allow signed values?
	if (m_bSigned)
	{
		strFilter += "+-";
		m_nMaxChars++;
	}

	// Allow decimal point?
	if (nDecDigits)
	{
		strFilter += '.';
		m_nMaxChars++;
	}

	// Allow fractions?
	if (m_nFlags & ALLOW_FRACTIONS)
	{
		strFilter += "/ ";
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
	CString str = Text();

	// Not a fraction?
	if (str.Find('/') < 0)
		return atof(str);

	ASSERT(false);
	
	return atof(str);
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

	// Remove trailing zeroes?
	if (m_nFlags & NO_TRAIL_ZEROES)
	{
		char* pszDecPt = strchr(szText, '.');

		// Value has a decimal point?
		if (pszDecPt != NULL)
		{
			// Calculate the end of the string.
			char* pszEOS = pszDecPt + strlen(pszDecPt) - 1;

			// Remove trailing zeroes.
			while ( (pszEOS > pszDecPt) && (*pszEOS == '0') )
				*pszEOS-- = '\0';

			// Remove decimal point?
			if (pszEOS == pszDecPt)
				*pszDecPt = '\0';
		}
	}

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

	char szText[100];
	int	 nSelStart, nSelEnd;

	// Get the current text.
	SendMessage(WM_GETTEXT, 100, (LPARAM)(LPCSTR)szText);

	// Get the current selection.
	Selected(nSelStart, nSelEnd);

	int nSelChars = nSelEnd - nSelStart;

	// Is the sign char?
	if ( (cChar == '+') || (cChar == '-') )
	{
		// Caret not at start OR already have sign?
		if ( (nSelStart > 0) || (strchr(szText, '+') != NULL) || (strchr(szText, '-') != NULL) )
			return true;
	}

	// Is a decimal point AND already have one?
	if ( (cChar == '.') && (strchr(szText, '.') != NULL) )
		return true;

	// Is a fraction separator AND already have one?
	if ( (cChar == '/') && (strchr(szText, '/') != NULL) )
		return true;

	// Is a fraction separator AND already have one?
	if ( (cChar == ' ') && (strchr(szText, ' ') != NULL) )
		return true;

	// Allowing decimal places AND is a digit?
	if ( (m_nDecDigits > 0) && (isdigit(cChar)) )
	{
		// Get decimal point position.
		char* pszDecPt = strchr(szText, '.');

		// Is decimal point AND caret after it AND no selection
		// AND max decimal places entered?
		if ( (pszDecPt != NULL) && (nSelStart > (pszDecPt - szText)) && (nSelChars < 1)
		  && (strlen(pszDecPt + 1) >= (size_t)m_nDecDigits) )
			return true;
	}

	return false;
}
