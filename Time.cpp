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
#include <stdio.h>
#include <tchar.h>
#include <Core/AnsiWide.hpp>
#include <Core/StringUtils.hpp>
#include <stdexcept>

/******************************************************************************
**
** Constants.
**
*******************************************************************************
*/

// ISO Format min string size in characters "dd:dd".
const size_t ISO_FMT_MIN_LEN = 5;
// ISO Format string size in characters "dd:dd:dd".
const size_t ISO_FMT_MAX_LEN = 8;

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

	tchar* pszBuffer = static_cast<tchar*>(alloca(Core::NumBytes<tchar>(nChars+1)));

	pszBuffer[0] = TXT('\0');

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

	tchar* pszValue = TXT("");

	// ISO standard format?
	if (nFormat == FMT_ISO)
	{
		pszValue = static_cast<tchar*>(alloca(Core::NumBytes<tchar>(ISO_FMT_MAX_LEN+1)));

		int nResult = _sntprintf(pszValue, ISO_FMT_MAX_LEN+1, TXT("%02d:%02d:%02d"), iHours, iMins, iSecs);

		ASSERT(nResult >= 0);

		if (nResult < 0)
			throw std::logic_error(T2A(Core::Fmt(TXT("Insufficient buffer size used in CTime::ToString(). Result: %d"), nResult)));
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
		size_t nChars = ::GetTimeFormat(LOCALE_USER_DEFAULT, nTimeFmt, &st, NULL, pszValue, 0);

		pszValue = static_cast<tchar*>(alloca(Core::NumBytes<tchar>(nChars)));

		// Format the string.
		::GetTimeFormat(LOCALE_USER_DEFAULT, nTimeFmt, &st, NULL, pszValue, nChars);
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

bool CTime::FromString(const tchar* pszTime)
{
	ASSERT(pszTime != NULL);

	int nLength = tstrlen(pszTime);

	// Check length is at least "00:00" and at most "00:00:00".
	if ( (nLength < ISO_FMT_MIN_LEN) || (nLength > ISO_FMT_MAX_LEN) )
		return false;

	tchar szTime[ISO_FMT_MAX_LEN+1] = { 0 };
	
	// Copy to non-const buffer.
	tstrncpy(szTime, pszTime, ISO_FMT_MAX_LEN);
	
	// Break up string into time components.
	const tchar* pszHours = tstrtok(szTime, TXT(":"));
	const tchar* pszMins  = tstrtok(NULL,   TXT(":"));
	const tchar* pszSecs  = tstrtok(NULL,   TXT(":"));

	// Got at least 2 string parts?
	if ( (pszHours == NULL) || (pszMins == NULL) )
		return false;

	// Secs not specified?
	if (pszSecs == NULL)
		pszSecs = TXT("0");

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
