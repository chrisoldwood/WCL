/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDate class definitions.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Date.hpp"
#include <time.h>
#include "StrCvt.hpp"
#include "IInputStream.hpp"
#include "IOutputStream.hpp"
#include <stdio.h>
#include <tchar.h>
#include <Core/AnsiWide.hpp>
#include <Core/StringUtils.hpp>
#include <Core/BadLogicException.hpp>
#include <malloc.h>
#include <Core/InvalidArgException.hpp>

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) // GCC 4.2+
// missing initializer for member 'X'
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

/******************************************************************************
**
** Constants.
**
*******************************************************************************
*/

const int DAYS_PER_YEAR      = 365;
const int DAYS_PER_LEAP_YEAR = 366;
const int DAYS_PER_4_YEARS   = (DAYS_PER_YEAR * 3) + DAYS_PER_LEAP_YEAR;

// ISO Format string size in characters "dddd-dd-dd".
const size_t ISO_FMT_MAX_LEN = 10;

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Days per month for both leap and non leap years.
static int DaysPerMonth[2][12] = {
// Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
{   31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
{   31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };

/******************************************************************************
** Method:		Constructors
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDate::CDate()
	: m_tDate(0)
{
}

CDate::CDate(WCL::Seconds tDate)
	: m_tDate()
{
	Set(tDate);
}

CDate::CDate(int iDay, int iMonth, int iYear)
	: m_tDate()
{
	Set(iDay, iMonth, iYear);
}

/******************************************************************************
** Method:		Set()
**
** Description:	Sets the date to the current system date.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDate::Set()
{
	SYSTEMTIME	Date;

	::GetLocalTime(&Date);

	Set(Date.wDay, Date.wMonth, Date.wYear);
}

/******************************************************************************
** Method:		Set()
**
** Description:	Sets the date.
**
** Parameters:	iDay, iMonth, iYear		The date.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDate::Set(int iDay, int iMonth, int  iYear)
{
	ASSERT( (iYear  >= MIN_YEAR)  && (iYear  <= MAX_YEAR) );
	ASSERT( (iMonth >= MIN_MONTH) && (iMonth <= MAX_MONTH) );
	ASSERT( (iDay   >= MIN_DAY)   && (iDay   <= DaysInMonth(iMonth, iYear)) );

	tm oTM;

	oTM.tm_mday  = iDay;
	oTM.tm_mon   = iMonth-1;
	oTM.tm_year  = iYear - 1900;
	oTM.tm_hour  = 0;
	oTM.tm_min   = 0;
	oTM.tm_sec   = 0;
	oTM.tm_isdst = 0;

	m_tDate = mktime(&oTM);

	// Do what _mkgmtime() does.
	m_tDate -= _timezone;

	ASSERT(m_tDate != -1);
}

/******************************************************************************
** Method:		Get()
**
** Description:	Gets the date.
**
** Parameters:	iDay, iMonth, iYear		The returned date.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDate::Get(int& iDay, int& iMonth, int& iYear) const
{
	tm oTM = *gmtime(&m_tDate);

	iDay   = oTM.tm_mday;
	iMonth = oTM.tm_mon + 1;
	iYear  = oTM.tm_year + 1900;
}

/******************************************************************************
** Method:		Current()
**
** Description:	Get the current date.
**
** Parameters:	None.
**
** Returns:		The current date.
**
*******************************************************************************
*/

CDate CDate::Current()
{
	CDate Now;

	Now.Set();

	return Now;
}

/******************************************************************************
** Method:		DateFormatOrder()
**
** Description:	Gets the order of the day, month & year for a date in short
**				date format.
**
** Parameters:	None.
**
** Returns:		The date order.
**
*******************************************************************************
*/

CDate::DateOrder CDate::DateFormatOrder()
{
	DateOrder eOrder = YEAR_MONTH_DAY;

	// Get the size of the buffer and allocate one.
	int nChars = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IDATE, nullptr, 0);

	tchar* pszBuffer = static_cast<tchar*>(alloca(Core::numBytes<tchar>(nChars+1)));

	pszBuffer[0] = TXT('\0');

	// Get the locale string.
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IDATE, pszBuffer, nChars+1) != 0)
	{
		eOrder = static_cast<DateOrder>(_ttoi(pszBuffer));

		if ((eOrder != MONTH_DAY_YEAR) && (eOrder != DAY_MONTH_YEAR) && (eOrder != YEAR_MONTH_DAY))
			throw Core::BadLogicException(Core::fmt(TXT("Unsupported locale date order '%s'"), pszBuffer));
	}

	return eOrder;
}

/******************************************************************************
** Method:		FieldSeparator()
**
** Description:	Gets the separator used between date fields.
**
** Parameters:	None.
**
** Returns:		The separator characters.
**
*******************************************************************************
*/

CString CDate::FieldSeparator()
{
	// Get the size of the buffer and allocate one.
	int nChars = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDATE, nullptr, 0);

	tchar* pszBuffer = static_cast<tchar*>(alloca(Core::numBytes<tchar>(nChars+1)));

	pszBuffer[0] = TXT('\0');

	// Get the locale string.
	::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDATE, pszBuffer, nChars+1);

	return pszBuffer;
}

/******************************************************************************
** Method:		DayOfWeekName()
**
** Description:	Gets the name for the day of the week specified.
**
** Parameters:	nDay		The day of the week [0..6] = [Mon..Sun].
**				bFullName	Get the full name (true) or short name (false).
**
** Returns:		The name.
**
*******************************************************************************
*/

CString CDate::DayOfWeekName(int nDay, bool bFullName)
{
	ASSERT((nDay >= 0) && (nDay <= 6));

	// Map day to locale type ID.
	int nLCType = (bFullName) ? (LOCALE_SDAYNAME1 + nDay) : (LOCALE_SABBREVDAYNAME1 + nDay);

	// Get the size of the buffer and allocate one.
	int nChars = ::GetLocaleInfo(LOCALE_USER_DEFAULT, nLCType, nullptr, 0);

	tchar* pszBuffer = static_cast<tchar*>(alloca(Core::numBytes<tchar>(nChars+1)));

	pszBuffer[0] = TXT('\0');

	// Get the locale string.
	::GetLocaleInfo(LOCALE_USER_DEFAULT, nLCType, pszBuffer, nChars+1);

	return pszBuffer;
}

/******************************************************************************
** Method:		MonthName()
**
** Description:	Gets the name for the day of the week specified.
**
** Parameters:	nMonth		The month [0..11] = [Jan..Dec].
**				bFullName	Get the full name (true) or short name (false).
**
** Returns:		The name.
**
*******************************************************************************
*/

CString CDate::MonthName(int nMonth, bool bFullName)
{
	ASSERT((nMonth >= 0) && (nMonth <= 11));

	// Map month to locale type ID.
	int nLCType = (bFullName) ? (LOCALE_SMONTHNAME1 + nMonth) : (LOCALE_SABBREVMONTHNAME1 + nMonth);

	// Get the size of the buffer and allocate one.
	int nChars = ::GetLocaleInfo(LOCALE_USER_DEFAULT, nLCType, nullptr, 0);

	tchar* pszBuffer = static_cast<tchar*>(alloca(Core::numBytes<tchar>(nChars+1)));

	pszBuffer[0] = TXT('\0');

	// Get the locale string.
	::GetLocaleInfo(LOCALE_USER_DEFAULT, nLCType, pszBuffer, nChars+1);

	return pszBuffer;
}

/******************************************************************************
** Method:		DayOfWeekStr()
**
** Description:	Converts the day of the week to a string.
**
** Parameters:	bFullName	Get the full name (true) or short name (false).
**
** Returns:		The name of the day.
**
*******************************************************************************
*/

CString CDate::DayOfWeekStr(bool bFullName) const
{
	return DayOfWeekName(DayOfWeek(), bFullName);
}

/******************************************************************************
** Method:		MonthStr()
**
** Description:	Converts the month to a string.
**
** Parameters:	bFullName	Get the full name (true) or short name (false).
**
** Returns:		The name of the month.
**
*******************************************************************************
*/

CString CDate::MonthStr(bool bFullName) const
{
	return MonthName(Month(), bFullName);
}

/******************************************************************************
** Method:		ToString()
**
** Description:	Converts the date to a formatted string.
**
** Parameters:	nFormat		The string format.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CDate::ToString(int nFormat) const
{
	ASSERT((nFormat == FMT_ISO) || (nFormat == FMT_WIN_SHORT) || (nFormat == FMT_WIN_LONG));

	int iDay, iMonth, iYear;

	// Get the date components.
	Get(iDay, iMonth, iYear);

	// ISO standard format?
	if (nFormat == FMT_ISO)
	{
		tchar* pszValue = static_cast<tchar*>(alloca(Core::numBytes<tchar>(ISO_FMT_MAX_LEN+1)));

		int nResult = _sntprintf(pszValue, ISO_FMT_MAX_LEN+1, TXT("%04d-%02d-%02d"), iYear, iMonth, iDay);

		ASSERT(nResult >= 0);

		if (nResult < 0)
			throw Core::BadLogicException(Core::fmt(TXT("Insufficient buffer size used in CDate::ToString(). Result: %d"), nResult));

		return pszValue;
	}
	// Windows locale derived format?
	else if ((nFormat == FMT_WIN_SHORT) || (nFormat == FMT_WIN_LONG))
	{
		int nDateFmt = DATE_LONGDATE;

		if (nFormat == FMT_WIN_SHORT)
			nDateFmt = DATE_SHORTDATE;

		SYSTEMTIME st = { 0 };

		// Convert from time_t to SYSTEMTIME.
		st.wYear  = static_cast<WORD>(iYear);
		st.wMonth = static_cast<WORD>(iMonth);
		st.wDay   = static_cast<WORD>(iDay);

		// Calculate buffer size.
		size_t nChars = ::GetDateFormat(LOCALE_USER_DEFAULT, nDateFmt, &st, nullptr, nullptr, 0);

		tchar* pszValue = static_cast<tchar*>(alloca(Core::numBytes<tchar>(nChars)));

		// Format the string.
		::GetDateFormat(LOCALE_USER_DEFAULT, nDateFmt, &st, nullptr, pszValue, static_cast<int>(nChars));

		return pszValue;
	}

	throw Core::InvalidArgException(TXT("Invalid string format requested"));
}

/******************************************************************************
** Method:		FromString()
**
** Description:	Converts a formatted string to a date. It expects a string
**				formatted as DD/MM/YYYY.
**
** Parameters:	pszDate		The date.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CDate::FromString(const tchar* pszDate)
{
	ASSERT(pszDate != nullptr);

	size_t nLength = tstrlen(pszDate);

	// Check length is exactly "YYYY-MM-DD".
	if (nLength != ISO_FMT_MAX_LEN)
		return false;

	tchar szDate[ISO_FMT_MAX_LEN+1] = { 0 };

	// Copy to non-const buffer.
	tstrncpy(szDate, pszDate, ISO_FMT_MAX_LEN);

	// Break up string.
	const tchar* pszYear  = tstrtok(szDate,  TXT("-"));
	const tchar* pszMonth = tstrtok(nullptr, TXT("-"));
	const tchar* pszDay   = tstrtok(nullptr, TXT("-"));

	// Got all 3 string parts?
	if ( (pszDay == nullptr) || (pszMonth == nullptr) || (pszYear == nullptr) )
		return false;

	// Convert to numbers.
	int	iDate  = CStrCvt::ParseInt(pszDay,   CStrCvt::PARSE_DECIMAL_ONLY);
	int iMonth = CStrCvt::ParseInt(pszMonth, CStrCvt::PARSE_DECIMAL_ONLY);
	int iYear  = CStrCvt::ParseInt(pszYear,  CStrCvt::PARSE_DECIMAL_ONLY);

	// Validate each componet.
	if ( (iYear  < MIN_YEAR) || (iYear  > MAX_YEAR) )					return false;
	if ( (iMonth < 1)        || (iMonth > 12) )							return false;
	if ( (iDate  < 1)        || (iDate  > DaysInMonth(iMonth, iYear)) )	return false;

	// Valid, set it.
	Set(iDate, iMonth, iYear);

	return true;
}

/******************************************************************************
** Methods:		operator>>()
**				operator<<()
**
** Description:	Methods to read/write to/from a stream.
**
** Parameters:	rStream		The stream to read/write to/from.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void operator >>(WCL::IInputStream& rStream, CDate& rDate)
{
	STATIC_ASSERT(sizeof(rDate.m_tDate) == sizeof(time_t));

	rStream.Read(&rDate.m_tDate, sizeof(rDate.m_tDate));
}

void operator <<(WCL::IOutputStream& rStream, const CDate& rDate)
{
	STATIC_ASSERT(sizeof(rDate.m_tDate) == sizeof(time_t));

	rStream.Write(&rDate.m_tDate, sizeof(rDate.m_tDate));
}

/******************************************************************************
** Method:		DaysInMonth()
**
** Description:	Calculates the number of days in the given month and year.
**
** Parameters:	iMonth		The month.
**				iYear		The year.
**
** Returns:		The number of days.
**
*******************************************************************************
*/

int CDate::DaysInMonth(int iMonth, int iYear) const
{
	ASSERT( (iYear  >= MIN_YEAR) && (iYear  <= MAX_YEAR) );
	ASSERT( (iMonth >= 1)        && (iMonth <= 12) );

	// Is a leap year?
	int iIndex = ((iYear % 4) == 0) ? 1 : 0;

	return DaysPerMonth[iIndex][iMonth-1];
}
