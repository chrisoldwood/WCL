/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATETIME.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDateTime & CDateTimeSpan class definitions.
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

// ISO Format string buffer size.
const uint FMT_BUF_SIZE = 100;

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

bool CDateTime::FromString(const char* pszDateTime)
{
	ASSERT(pszDateTime != NULL);

	int nLength = strlen(pszDateTime);

	// Check length is exactly "YYYY-MM-DDT00:00:00".
	if (nLength != 19)
		return false;

	char szDateTime[FMT_BUF_SIZE];

	// Copy to non-const buffer.
	strcpy(szDateTime, pszDateTime);

	// Break up string.
	const char* pszDate = strtok(szDateTime, "T");
	const char* pszTime = strtok(NULL,       "T");

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

void CDateTime::operator <<(CStream& rStream)
{
	rStream.Read(&m_tDateTime, sizeof(m_tDateTime));
}

void CDateTime::operator >>(CStream& rStream) const
{
	rStream.Write(&m_tDateTime, sizeof(m_tDateTime));
}
