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
#include <errno.h>

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

CString CStrCvt::FormatUInt(uint nValue)
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
** Method:		FormatDate/DateTime()
**
** Description:	Convert a time_t value to a string.
**
** Parameters:	tValue		The value.
**
** Returns:		The value as a string.
**
*******************************************************************************
*/

CString CStrCvt::FormatDate(time_t tValue)
{
	char szValue[100];

	strftime(szValue, 100, "%Y-%m-%d", localtime(&tValue));

	return szValue;
}

CString CStrCvt::FormatDateTime(time_t tValue)
{
	char szValue[100];

	strftime(szValue, 100, "%Y-%m-%d %H:%M:%S", localtime(&tValue));

	return szValue;
}

/******************************************************************************
** Method:		FormatError()
**
** Description:	Converts a system error code to a string.
**
** Parameters:	dwError		The error code.
**
** Returns:		The error as string.
**
*******************************************************************************
*/

CString CStrCvt::FormatError(DWORD dwError)
{
	CString strError;
	char*   pszError;

	// Format string using default language.
	::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&pszError, 0, NULL);

	// Copy message and free buffer.
	strError = pszError;
	::LocalFree(pszError);

	// Trim excess whitespace.
	strError.Trim();

	return strError;
}

/******************************************************************************
** Method:		ParseInt()
**
** Description:	Convert a string to an integer value.
**
** Parameters:	pszString	The string.
**				nFlags		Any flags to control the parsing.
**
** Returns:		The value.
**
** Exceptions:	CStrCvtException on error.
**
*******************************************************************************
*/

int CStrCvt::ParseInt(const char* pszString, int nFlags)
{
	ASSERT(pszString != NULL);
	ASSERT((nFlags == PARSE_ANY_FORMAT) || (nFlags == PARSE_OCTAL_ONLY) || (nFlags == PARSE_DECIMAL_ONLY) || (nFlags == PARSE_HEX_ONLY));

	errno = 0;

	char* pcEndChar = NULL;

	int nValue = strtol(pszString, &pcEndChar, nFlags);
	
	if (*pcEndChar != '\0')
		throw CStrCvtException(CStrCvtException::E_INVALID_FORMAT);

	ASSERT((errno == 0) || (errno == ERANGE));

	if (errno == ERANGE)
		throw CStrCvtException(CStrCvtException::E_INVALID_RANGE);

	return nValue;
}

uint CStrCvt::ParseUInt(const char* pszString, int nFlags)
{
	ASSERT(pszString != NULL);
	ASSERT((nFlags == PARSE_ANY_FORMAT) || (nFlags == PARSE_OCTAL_ONLY) || (nFlags == PARSE_DECIMAL_ONLY) || (nFlags == PARSE_HEX_ONLY));

	errno = 0;

	char* pcEndChar = NULL;

	uint nValue = strtoul(pszString, &pcEndChar, nFlags);
	
	if (*pcEndChar != '\0')
		throw CStrCvtException(CStrCvtException::E_INVALID_FORMAT);

	ASSERT((errno == 0) || (errno == ERANGE));

	if (errno == ERANGE)
		throw CStrCvtException(CStrCvtException::E_INVALID_RANGE);

	return nValue;
}

/******************************************************************************
** Method:		ParseLong()
**
** Description:	Convert a string to a long value.
**
** Parameters:	pszString	The string.
**				nFlags		Any flags to control the parsing.
**
** Returns:		The value.
**
** Exceptions:	CStrCvtException on error.
**
*******************************************************************************
*/

long CStrCvt::ParseLong(const char* pszString, int nFlags)
{
	return ParseInt(pszString, nFlags);
}

/******************************************************************************
** Method:		ParseDouble()
**
** Description:	Convert a string to a double value.
**
** Parameters:	pszString	The string.
**				nFlags		Any flags to control the parsing.
**
** Returns:		The value.
**
** Exceptions:	CStrCvtException on error.
**
*******************************************************************************
*/

double CStrCvt::ParseDouble(const char* pszString, int /*nFlags*/)
{
	ASSERT(pszString != NULL);

	errno = 0;

	char* pcEndChar = NULL;

	double dValue = strtod(pszString, &pcEndChar);
	
	if (*pcEndChar != '\0')
		throw CStrCvtException(CStrCvtException::E_INVALID_FORMAT);

	ASSERT((errno == 0) || (errno == ERANGE));

	if (errno == ERANGE)
		throw CStrCvtException(CStrCvtException::E_INVALID_RANGE);

	return dValue;
}
