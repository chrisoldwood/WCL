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
	rStream >> m_Date;
	rStream >> m_Time;
}

void CDateTime::operator >>(CStream& rStream) const
{
	rStream << m_Date;
	rStream << m_Time;
}
