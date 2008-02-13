/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATETIME.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDateTime & CDateTimeSpan class definitions.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "DateTime.hpp"
#include <time.h>
#include "IInputStream.hpp"
#include "IOutputStream.hpp"

/******************************************************************************
**
** Constants.
**
*******************************************************************************
*/

// ISO Format string size in characters "dddd-dd-ddTdd:dd:dd".
const size_t ISO_FMT_MAX_LEN = 19;

/******************************************************************************
** Method:		Current()
**
** Description:	Get the current date & time.
**
** Parameters:	None.
**
** Returns:		The current date and time.
**
*******************************************************************************
*/

CDateTime CDateTime::Current()
{
	CDateTime Now;

	Now.Set();

	return Now;
}

/******************************************************************************
** Method:		FromLocalTime()
**
** Description:	Convets the local time stored in a time_t to our DateTime.
**
** Parameters:	tDateTime	The local time.
**
** Returns:		The DateTime.
**
*******************************************************************************
*/

CDateTime CDateTime::FromLocalTime(time_t tDateTime)
{
	tm* pDateTime = localtime(&tDateTime);

	return CDateTime(pDateTime->tm_mday, pDateTime->tm_mon+1, pDateTime->tm_year+1900,
						pDateTime->tm_hour, pDateTime->tm_min, pDateTime->tm_sec);
}

/******************************************************************************
** Method:		FromString()
**
** Description:	Converts the formatted string to a date & time.
**				NB: Only accepts ISO format.
**
** Parameters:	pszDateTime		The ISO formatted date and time.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CDateTime::FromString(const tchar* pszDateTime)
{
	ASSERT(pszDateTime != NULL);

	int nLength = tstrlen(pszDateTime);

	// Check length is exactly "YYYY-MM-DDT00:00:00".
	if (nLength != ISO_FMT_MAX_LEN)
		return false;

	tchar szDateTime[ISO_FMT_MAX_LEN+1] = { 0 };

	// Copy to non-const buffer.
	tstrncpy(szDateTime, pszDateTime, ISO_FMT_MAX_LEN);

	// Break up string.
	const tchar* pszDate = tstrtok(szDateTime, TXT("T"));
	const tchar* pszTime = tstrtok(NULL,       TXT("T"));

	CDate oDate;
	CTime oTime;

	// Failed to parse either date OR time?
	if (!oDate.FromString(pszDate) || !oTime.FromString(pszTime))
		return false;

	*this = CDateTime(oDate, oTime);

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

void operator >>(WCL::IInputStream& rStream, CDateTime& rDateTime)
{
	ASSERT(sizeof(rDateTime.m_tDateTime) == sizeof(time_t));

	rStream.Read(&rDateTime.m_tDateTime, sizeof(rDateTime.m_tDateTime));
}

void operator <<(WCL::IOutputStream& rStream, const CDateTime& rDateTime)
{
	ASSERT(sizeof(rDateTime.m_tDateTime) == sizeof(time_t));

	rStream.Write(&rDateTime.m_tDateTime, sizeof(rDateTime.m_tDateTime));
}

// C4127
#pragma warning(pop)
