/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRCVT.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CStrCvt class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StrCvt.hpp"
#include <errno.h>
#include <time.h>
#include "StrCvtException.hpp"
#include <tchar.h>
#include <Core/AnsiWide.hpp>
#include <stdexcept>
#include <limits>

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
	const size_t MAX_CHARS = std::numeric_limits<int>::digits10+1;

	tchar szValue[MAX_CHARS+1] = { 0 };

	return _ltot(nValue, szValue, 10);
}

CString CStrCvt::FormatUInt(uint nValue)
{
	const size_t MAX_CHARS = std::numeric_limits<uint>::digits10+1;

	tchar szValue[MAX_CHARS+1] = { 0 };

	return _ltot(nValue, szValue, 10);
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
	const size_t MAX_CHARS = std::numeric_limits<long>::digits10+1;

	tchar szValue[MAX_CHARS+1] = { 0 };

	return _ltot(lValue, szValue, 10);
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
	char szValue[_CVTBUFSIZE];

	return A2T(_gcvt(dValue, 16, szValue));
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
	const size_t MAX_CHARS = 10;
	tchar szValue[MAX_CHARS+1];

	if (_tcsftime(szValue, MAX_CHARS+1, TXT("%Y-%m-%d"), localtime(&tValue)) == 0)
		throw std::logic_error(T2A(TXT("Insufficient buffer size used in CStrCvt::FormatDate()")));

	return szValue;
}

CString CStrCvt::FormatDateTime(time_t tValue)
{
	const size_t MAX_CHARS = 19;
	tchar szValue[MAX_CHARS+1];

	if (_tcsftime(szValue, MAX_CHARS+1, TXT("%Y-%m-%d %H:%M:%S"), localtime(&tValue)) == 0)
		throw std::logic_error(T2A(TXT("Insufficient buffer size used in CStrCvt::FormatDateTime()")));

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
	tchar*  pszError;

	// Format string using default language.
	::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<tchar*>(&pszError), 0, NULL);

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

int CStrCvt::ParseInt(const tchar* pszString, int nFlags)
{
	ASSERT(pszString != NULL);
	ASSERT((nFlags == PARSE_ANY_FORMAT) || (nFlags == PARSE_OCTAL_ONLY) || (nFlags == PARSE_DECIMAL_ONLY) || (nFlags == PARSE_HEX_ONLY));

	errno = 0;

	tchar* pcEndChar = NULL;

	int nValue = tstrtol(pszString, &pcEndChar, nFlags);
	
	if (*pcEndChar != TXT('\0'))
		throw CStrCvtException(CStrCvtException::E_INVALID_FORMAT);

	ASSERT((errno == 0) || (errno == ERANGE));

	if (errno == ERANGE)
		throw CStrCvtException(CStrCvtException::E_INVALID_RANGE);

	return nValue;
}

uint CStrCvt::ParseUInt(const tchar* pszString, int nFlags)
{
	ASSERT(pszString != NULL);
	ASSERT((nFlags == PARSE_ANY_FORMAT) || (nFlags == PARSE_OCTAL_ONLY) || (nFlags == PARSE_DECIMAL_ONLY) || (nFlags == PARSE_HEX_ONLY));

	errno = 0;

	tchar* pcEndChar = NULL;

	uint nValue = tstrtoul(pszString, &pcEndChar, nFlags);
	
	if (*pcEndChar != TXT('\0'))
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

long CStrCvt::ParseLong(const tchar* pszString, int nFlags)
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

double CStrCvt::ParseDouble(const tchar* pszString, int /*nFlags*/)
{
	ASSERT(pszString != NULL);

	errno = 0;

	tchar* pcEndChar = NULL;

	double dValue = tstrtod(pszString, &pcEndChar);
	
	if (*pcEndChar != TXT('\0'))
		throw CStrCvtException(CStrCvtException::E_INVALID_FORMAT);

	ASSERT((errno == 0) || (errno == ERANGE));

	if (errno == ERANGE)
		throw CStrCvtException(CStrCvtException::E_INVALID_RANGE);

	return dValue;
}
