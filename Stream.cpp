/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STREAM.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CStream class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStream::CStream()
	: m_nMode(NULL)
	, m_nFormat(0)
	, m_nVersion(0)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStream::~CStream()
{
}

/******************************************************************************
** Method:		ReadLine()
**
** Description:	Read a line of text from the stream.
**
** Parameters:	None.
**
** Returns:		A line of text without the CRLF pair.
**
*******************************************************************************
*/

CString CStream::ReadLine()
{
	CString strLine;

	if (!IsEOF())
	{
		char cChar;
		
		do
		{
			// Read a char.
			Read(&cChar, sizeof(cChar));

			// Append char if not CR or LF.
			if ( (cChar != '\r') && (cChar != '\n') )
				strLine += cChar;
		}
		// Until we reach EOF or EOL.
		while ( (!IsEOF()) && (cChar != '\r') && (cChar != '\n') );

		// Skip LF char, if CR found.
		if ( (!IsEOF()) && (cChar == '\r') )
			Read(&cChar, sizeof(cChar));
	}

	return strLine;
}

/******************************************************************************
** Method:		WriteLine()
**
** Description:	Write a line of text to the stream appending a CRLF pair.
**
** Parameters:	pszLine		The line of text.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStream::WriteLine(const char* pszLine)
{
	Write(pszLine, strlen(pszLine));
	Write("\r\n", 2);
}
