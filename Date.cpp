/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDate & CDateSpan class definitions.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
**
** Constants.
**
*******************************************************************************
*/

const int MIN_YEAR           = 1901;
const int MAX_YEAR           = 2099;
const int DAYS_PER_YEAR      = 365;
const int DAYS_PER_LEAP_YEAR = 366;
const int DAYS_PER_4_YEARS   = (DAYS_PER_YEAR * 3) + DAYS_PER_LEAP_YEAR;

// ISO Format string buffer size.
const uint FMT_BUF_SIZE = 100;

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

// Short and long names for days of the week.
static char* DayNames[2][7] = {
{ "Mon",    "Tue",     "Wed",       "Thu",      "Fri",    "Sat",      "Sun" },
{ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" } };

// Short and long names for the months.
static char* MonthNames[2][12] = {
{ "Jan",     "Feb",      "Mar",   "Apr",   "May", "Jun",  "Jul",  "Aug",    "Sep",       "Oct",     "Nov",      "Dec" },
{ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" } };

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
	ASSERT( (iYear  >= MIN_YEAR) && (iYear  <= MAX_YEAR) );
	ASSERT( (iMonth >= 1)        && (iMonth <= 12) );
	ASSERT( (iDay   >= 1)        && (iDay   <= DaysInMonth(iMonth, iYear)) );

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
** Method:		DayOfWeekStr()
**
** Description:	Converts the day of the week to a string.
**
** Parameters:	None.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CDate::DayOfWeekStr() const
{
	int nDay = DayOfWeek();

	ASSERT((nDay >= 0) && (nDay <= 6));

	return DayNames[0][nDay];	
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

	char* pszValue = "";

	// ISO standard format?
	if (nFormat == FMT_ISO)
	{
		pszValue = (char*) alloca(FMT_BUF_SIZE);

		_snprintf(pszValue, FMT_BUF_SIZE, "%04d-%02d-%02d", iYear, iMonth, iDay);
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
		int nBufSize = ::GetDateFormat(LOCALE_USER_DEFAULT, nDateFmt, &st, NULL, pszValue, 0);

		pszValue = (char*) alloca(nBufSize);

		// Format the string.
		::GetDateFormat(LOCALE_USER_DEFAULT, nDateFmt, &st, NULL, pszValue, nBufSize);
	}

	return pszValue;
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

bool CDate::FromString(const char* pszDate)
{
	ASSERT(pszDate != NULL);

	int nLength = strlen(pszDate);

	// Check length is exactly "YYYY-MM-DD".
	if (nLength != 10)
		return false;

	char szDate[FMT_BUF_SIZE];
	
	// Copy to non-const buffer.
	strcpy(szDate, pszDate);
	
	// Break up string.
	const char* pszYear  = strtok(szDate, "-");
	const char* pszMonth = strtok(NULL,   "-");
	const char* pszDay   = strtok(NULL,   "-");

	// Got all 3 string parts?
	if ( (pszDay == NULL) || (pszMonth == NULL) || (pszYear == NULL) )
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

void CDate::operator <<(CStream& rStream)
{
	rStream.Read(&m_tDate, sizeof(m_tDate));
}

void CDate::operator >>(CStream& rStream) const
{
	rStream.Write(&m_tDate, sizeof(m_tDate));
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
