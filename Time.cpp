/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TIME.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CTime & CTimeSpan class definitions.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

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
	iSecs  = m_tTime % 60;
	iMins  = (m_tTime % SECS_PER_HOUR) / SECS_PER_MIN;
	iHours = m_tTime / SECS_PER_HOUR;
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
** Method:		ToString()
**
** Description:	Converts the time to a string.
**
** Parameters:	nFields		The fields to use in the string.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CTime::ToString(int nFields) const
{
	CString strTime;
	int		iHours, iMins, iSecs;
	CString strHours, strMins, strSecs;

	// Get the time components.
	Get(iHours, iMins, iSecs);

	// Convert components to strings.
	strHours.Format("%02d:", iHours);
	strMins.Format("%02d:", iMins);
	strSecs.Format("%02d", iSecs);

	// Format the string.
	if (nFields & HH)
		strTime += strHours;

	if (nFields & MM)
		strTime += strMins;

	if (nFields & SS)
		strTime += strSecs;

	int nLen = strTime.Length();

	// Strip trailing ':', if one.
	if (strTime[nLen-1] == ':')
		strTime[nLen-1] = '\0';

	return strTime;
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
	char szTime[10];
	
	// Check length is at least "0:0:0" and at most "00:00:00".
	if ( (strlen(pszTime) < 5) || (strlen(pszTime) > 8) )
		return false;

	// Copy to tmp buffer.
	strcpy(szTime, pszTime);
	
	// Break up string into time components.
	char* pszHours = strtok(szTime, ":");
	char* pszMins  = strtok(NULL,   ":");
	char* pszSecs  = strtok(NULL,   ":");

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

void CTime::operator <<(CStream& rStream)
{
	rStream.Read(&m_tTime, sizeof(m_tTime));
}

void CTime::operator >>(CStream& rStream) const
{
	rStream.Write(&m_tTime, sizeof(m_tTime));
}
