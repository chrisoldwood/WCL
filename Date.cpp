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
** Method:		ToString()
**
** Description:	Converts the date to a formatted string.
**
** Parameters:	nFields		The fields to use in the string.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CDate::ToString(int nFields) const
{
	CString strDate;
	int		iDay, iMonth, iYear;
	CString strDay, strMonth, strYear, strYr;

	// Get the date components.
	Get(iDay, iMonth, iYear);

	// Get weekday and short year.
	int iWkDay = DayOfWeek();
	int iYr    = iYear % 100;

	// Convert components to strings.
	strDay.Format("%02d/", iDay);
	strMonth.Format("%02d/", iMonth);
	strYear.Format("%02d", iYear);
	strYr.Format("%02d", iYr);

	// Format the string.
	if (nFields & SD)
	{
		strDate += DayNames[0][iWkDay];
		strDate += ' ';
	}

	if (nFields & LD)
	{
		strDate += DayNames[1][iWkDay];
		strDate += ' ';
	}

	if (nFields & DD)
		strDate += strDay;

	if (nFields & SM)
		strDate += MonthNames[0][iMonth-1];

	if (nFields & LM)
		strDate += MonthNames[1][iMonth-1];

	if (nFields & MM)
		strDate += strMonth;

	if (nFields & YY)
		strDate += strYr;

	if (nFields & Y4)
		strDate += strYear;

	int nLen = strDate.Length();

	// Strip trailing '/' or ' ', if one.
	if ( (strDate[nLen-1] == '/') || (strDate[nLen-1] == ' ') )
		strDate[nLen-1] = '\0';

	return strDate;
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
	char szDate[20];
	
	// Check length is at least "0/0/0000" and at most "00/00/0000".
	if ( (strlen(pszDate) < 8) || (strlen(pszDate) > 10) )
		return false;

	// Copy to tmp buffer.
	strcpy(szDate, pszDate);
	
	// Break up string.
	char* pszDay   = strtok(szDate, "/");
	char* pszMonth = strtok(NULL,   "/");
	char* pszYear  = strtok(NULL,   "/");

	// Got all 3 string parts?
	if ( (pszDay == NULL) || (pszMonth == NULL) || (pszYear == NULL) )
		return false;

	// Convert to numbers.
	int	iDate  = atoi(pszDay);
	int iMonth = atoi(pszMonth);
	int iYear  = atoi(pszYear);
	
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
