/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TIME.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CTime class definitions.
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

// ISO Format min string size in characters "dd:dd".
const size_t ISO_FMT_MIN_LEN = 5;
// ISO Format string size in characters "dd:dd:dd".
const size_t ISO_FMT_MAX_LEN = 8;

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

CTime::CTime()
	: m_tTime(0)
{
}

CTime::CTime(WCL::Seconds tTime)
	: m_tTime()
{
	Set(tTime);
}

CTime::CTime(int iHours, int iMins, int iSecs)
	: m_tTime()
{
	Set(iHours, iMins, iSecs);
}

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
	ASSERT( (iHours >= MIN_HOURS) && (iHours <= MAX_HOURS) );
	ASSERT( (iMins  >= MIN_MINS)  && (iMins  <= MAX_MINS) );
	ASSERT( (iSecs  >= MIN_SECS)  && (iSecs  <= MAX_SECS) );

	m_tTime = (iHours * WCL::SECS_PER_HOUR) + (iMins * WCL::SECS_PER_MIN) + iSecs;
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
	iMins  = static_cast<int>((m_tTime % WCL::SECS_PER_HOUR) / WCL::SECS_PER_MIN);
	iHours = static_cast<int>(m_tTime / WCL::SECS_PER_HOUR);
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
	int nChars = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, nullptr, 0);

	tchar* pszBuffer = static_cast<tchar*>(alloca(Core::numBytes<tchar>(nChars+1)));

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

	// ISO standard format?
	if (nFormat == FMT_ISO)
	{
		tchar* pszValue = static_cast<tchar*>(alloca(Core::numBytes<tchar>(ISO_FMT_MAX_LEN+1)));

		int nResult = _sntprintf(pszValue, ISO_FMT_MAX_LEN+1, TXT("%02d:%02d:%02d"), iHours, iMins, iSecs);

		ASSERT(nResult >= 0);

		if (nResult < 0)
			throw Core::BadLogicException(Core::fmt(TXT("Insufficient buffer size used in CTime::ToString(). Result: %d"), nResult));

		return pszValue;
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
		size_t nChars = ::GetTimeFormat(LOCALE_USER_DEFAULT, nTimeFmt, &st, nullptr, nullptr, 0);

		tchar* pszValue = static_cast<tchar*>(alloca(Core::numBytes<tchar>(nChars)));

		// Format the string.
		::GetTimeFormat(LOCALE_USER_DEFAULT, nTimeFmt, &st, nullptr, pszValue, static_cast<int>(nChars));

		return pszValue;
	}

	throw Core::InvalidArgException(TXT("Invalid string format requested"));
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
	ASSERT(pszTime != nullptr);

	size_t nLength = tstrlen(pszTime);

	// Check length is at least "00:00" and at most "00:00:00".
	if ( (nLength < ISO_FMT_MIN_LEN) || (nLength > ISO_FMT_MAX_LEN) )
		return false;

	tchar szTime[ISO_FMT_MAX_LEN+1] = { 0 };

	// Copy to non-const buffer.
	tstrncpy(szTime, pszTime, ISO_FMT_MAX_LEN);

	// Break up string into time components.
	const tchar* pszHours = tstrtok(szTime,  TXT(":"));
	const tchar* pszMins  = tstrtok(nullptr, TXT(":"));
	const tchar* pszSecs  = tstrtok(nullptr, TXT(":"));

	// Got at least 2 string parts?
	if ( (pszHours == nullptr) || (pszMins == nullptr) )
		return false;

	// Secs not specified?
	if (pszSecs == nullptr)
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

void operator >>(WCL::IInputStream& rStream, CTime& rTime)
{
	STATIC_ASSERT(sizeof(rTime.m_tTime) == sizeof(time_t));

	rStream.Read(&rTime.m_tTime, sizeof(rTime.m_tTime));
}

void operator <<(WCL::IOutputStream& rStream, const CTime& rTime)
{
	STATIC_ASSERT(sizeof(rTime.m_tTime) == sizeof(time_t));

	rStream.Write(&rTime.m_tTime, sizeof(rTime.m_tTime));
}
