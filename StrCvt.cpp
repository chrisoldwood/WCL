/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRCVT.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CStrCvt class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		FormatInt()
**
** Description:	Convert an integer value to a string.
**
** Parameters:	nValue		The value.
**
** Returns:		The value as a string.
**
*******************************************************************************
*/

CString CStrCvt::FormatInt(int nValue)
{
	char szValue[50];

	return ltoa(nValue, szValue, 10);
}

/******************************************************************************
** Method:		FormatLong()
**
** Description:	Convert a long value to a string.
**
** Parameters:	nValue		The value.
**
** Returns:		The value as a string.
**
*******************************************************************************
*/

CString CStrCvt::FormatLong(long lValue)
{
	char szValue[50];

	return ltoa(lValue, szValue, 10);
}

/******************************************************************************
** Method:		FormatDouble()
**
** Description:	Convert a double value to a string.
**
** Parameters:	dValue		The value.
**
** Returns:		The value as a string.
**
*******************************************************************************
*/

CString CStrCvt::FormatDouble(double dValue)
{
	char szValue[50];

	return _gcvt(dValue, 15, szValue);
}

/******************************************************************************
** Method:		ParseInt()
**
** Description:	Convert a string to an integer value.
**
** Parameters:	pszString	The string.
**
** Returns:		The value.
**
** Exceptions:	CStrCvtException on error.
**
*******************************************************************************
*/

int CStrCvt::ParseInt(const char* pszString)
{
	ASSERT(pszString != NULL);

	char* pcEndChar = NULL;

	int nValue = strtol(pszString, &pcEndChar, 0);
	
	if (*pcEndChar != '\0')
		throw CStrCvtException(CStrCvtException::E_INVALID_FORMAT);

	return nValue;
}

/******************************************************************************
** Method:		ParseLong()
**
** Description:	Convert a string to a long value.
**
** Parameters:	pszString	The string.
**
** Returns:		The value.
**
** Exceptions:	CStrCvtException on error.
**
*******************************************************************************
*/

long CStrCvt::ParseLong(const char* pszString)
{
	return ParseInt(pszString);
}

/******************************************************************************
** Method:		ParseDouble()
**
** Description:	Convert a string to a double value.
**
** Parameters:	pszString	The string.
**
** Returns:		The value.
**
** Exceptions:	CStrCvtException on error.
**
*******************************************************************************
*/

double CStrCvt::ParseDouble(const char* pszString)
{
	ASSERT(pszString != NULL);

	char* pcEndChar = NULL;

	double dValue = strtod(pszString, &pcEndChar);
	
	if (*pcEndChar != '\0')
		throw CStrCvtException(CStrCvtException::E_INVALID_FORMAT);

	return dValue;
}
