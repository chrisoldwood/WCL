/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TIME.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CTime & CTimeSpan class definitions.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Time.hpp"
#include "StrCvt.hpp"
#include "IInputStream.hpp"
#include "IOutputStream.hpp"

/******************************************************************************
**
** Constants.
**
*******************************************************************************
*/

// ISO Format string buffer size.
const uint FMT_BUF_SIZE = 100;

/******************************************************************************
** Method:		Set()
**
** Description:	Sets the time to the current system time.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTime::Set()
{
	SYSTEMTIME	Time;

	::GetLocalTime(&Time);

	Set(Time.wHour, Time.wMinute, Time.wSecond);
}

/******************************************************************************
** Method:		Set()
**
** Description:	Sets the time.
**
** Parameters:	iHours, iMins, iSeconds		The time.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTime::Set(int iHours, int iMins, int iSecs)
{
	ASSERT( (iHours >= 0) && (iHours <= 23) );
	ASSERT( (iMins  >= 0) && (iMins  <= 59) );
	ASSERT( (iSecs  >= 0) && (iSecs  <= 59) );

	m_tTime = (iHours * SECS_PER_HOUR) + (iMins * SECS_PER_MIN) + iSecs;
}

/******************************************************************************
** Method:		Get()
**
** Description:	Gets the time.
**
** Parameters:	iHours, iMins, iSeconds		The returned time.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTime::Get(int& iHours, int& iMins, int& iSecs) const
{
	iSecs  = static_cast<int>(m_tTime % 60);
	iMins  = static_cast<int>((m_tTime % SECS_PER_HOUR) / SECS_PER_MIN);
	iHours = static_cast<int>(m_tTime / SECS_PER_HOUR);
}

/******************************************************************************
** Method:		Current()
**
** Description:	Get the current time.
**
** Parameters:	None.
**
** Returns:		The current time.
**
*******************************************************************************
*/

CTime CTime::Current()
{
	CTime Now;

	Now.Set();

	return Now;
}

/******************************************************************************
** Method:		FieldSeparator()
**
** Description:	Gets the separator used between time fields.
**
** Parameters:	None.
**
** Returns:		The separator characters.
**
*******************************************************************************
*/

CString CTime::FieldSeparator()
{
	// Get the size of the buffer and allocate one.
	int nChars = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, NULL, 0);

	char* pszBuffer = static_cast<char*>(alloca(nChars+1));

	pszBuffer[0] = '\0';

	// Get the locale string.
	::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, pszBuffer, nChars+1);

	return pszBuffer;
}

/******************************************************************************
** Method:		ToString()
**
** Description:	Converts the time to a string.
**
** Parameters:	nFormat		The string format.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CTime::ToString(int nFormat) const
{
	ASSERT((nFormat == FMT_ISO) || (nFormat == FMT_WIN_SHORT) || (nFormat == FMT_WIN_LONG));

	int iHours, iMins, iSecs;

	// Get the time components.
	Get(iHours, iMins, iSecs);

	char* pszValue = "";

	// ISO standard format?
	if (nFormat == FMT_ISO)
	{
		pszValue = (char*) alloca(FMT_BUF_SIZE);

		_snprintf(pszValue, FMT_BUF_SIZE, "%02d:%02d:%02d", iHours, iMins, iSecs);
	}
	// Windows locale derived format?
	else if ((nFormat == FMT_WIN_SHORT) || (nFormat == FMT_WIN_LONG))
	{
		int nTimeFmt = TIME_FORCE24HOURFORMAT | TIME_NOTIMEMARKER;

		if (nFormat == FMT_WIN_SHORT)
			nTimeFmt |= TIME_NOSECONDS;

		SYSTEMTIME st = { 0 };

		// Convert from time to SYSTEMTIME.
		// NB: Pretends its a time_t on 01/01/1970.
		st.wYear   = 1970;
		st.wMonth  = 1;
		st.wDay    = 1;
		st.wHour   = static_cast<WORD>(iHours);
		st.wMinute = static_cast<WORD>(iMins);
		st.wSecond = static_cast<WORD>(iSecs);

		// Calculate buffer size.
		int nTimeBufSize = ::GetTimeFormat(LOCALE_USER_DEFAULT, nTimeFmt, &st, NULL, pszValue, 0);

		pszValue = (char*) alloca(nTimeBufSize);

		// Format the string.
		::GetTimeFormat(LOCALE_USER_DEFAULT, nTimeFmt, &st, NULL, pszValue, nTimeBufSize);
	}
	// Unsupported format.
	else
	{
		ASSERT_FALSE();
	}

	return pszValue;
}

/******************************************************************************
** Method:		FromString()
**
** Description:	Converts a formatted string to a time. It expects a string
**				formated as HH:MM[:SS].
**
** Parameters:	pszTime		The time.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CTime::FromString(const char* pszTime)
{
	ASSERT(pszTime != NULL);

	int nLength = strlen(pszTime);

	// Check length is at least "00:00" and at most "00:00:00".
	if ( (nLength < 5) || (nLength > 8) )
		return false;

	char szTime[FMT_BUF_SIZE];
	
	// Copy to non-const buffer.
	strcpy(szTime, pszTime);
	
	// Break up string into time components.
	const char* pszHours = strtok(szTime, ":");
	const char* pszMins  = strtok(NULL,   ":");
	const char* pszSecs  = strtok(NULL,   ":");

	// Got at least 2 string parts?
	if ( (pszHours == NULL) || (pszMins == NULL) )
		return false;

	// Secs not specified?
	if (pszSecs == NULL)
		pszSecs = "0";

	// Convert to numbers.
	int	iHours = CStrCvt::ParseInt(pszHours, CStrCvt::PARSE_DECIMAL_ONLY);
	int iMins  = CStrCvt::ParseInt(pszMins,  CStrCvt::PARSE_DECIMAL_ONLY);
	int iSecs  = CStrCvt::ParseInt(pszSecs,  CStrCvt::PARSE_DECIMAL_ONLY);

	// Validate each componet.
	if ( (iHours < 0) || (iHours > 23) )	return false;
	if ( (iMins  < 0) || (iMins  > 59) )	return false;
	if ( (iSecs  < 0) || (iSecs  > 59) )	return false;

	// Valid, set it.
	Set(iHours, iMins, iSecs);

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

#pragma warning(push)
// conditional expression is constant (caused by the ASSERTs).
#pragma warning(disable:4127)

void operator >>(WCL::IInputStream& rStream, CTime& rTime)
{
	ASSERT(sizeof(rTime.m_tTime) == sizeof(time_t));

	rStream.Read(&rTime.m_tTime, sizeof(rTime.m_tTime));
}

void operator <<(WCL::IOutputStream& rStream, const CTime& rTime)
{
	ASSERT(sizeof(rTime.m_tTime) == sizeof(time_t));

	rStream.Write(&rTime.m_tTime, sizeof(rTime.m_tTime));
}

// C4127
#pragma warning(pop)
