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
