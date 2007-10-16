////////////////////////////////////////////////////////////////////////////////
//! \file   Stream.cpp
//! \brief  The CStream class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Stream.hpp"

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

CStream::CStream()
	: m_nMode(NULL)
	, m_nFormat(0)
	, m_nVersion(0)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

CStream::~CStream()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Read a line of text. This returns the line of text without the ending line
//! terminators.

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

////////////////////////////////////////////////////////////////////////////////
//! Write a line of text. This writes a line of text and appends the line
//! terminator.

void CStream::WriteLine(const char* pszLine)
{
	Write(pszLine, strlen(pszLine));
	Write("\r\n", 2);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the stream contents format.

uint32 CStream::Format() const
{
	return m_nFormat;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the stream contents format.

void CStream::SetFormat(uint32 nFormat)
{
	m_nFormat = nFormat;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the stream contents version.

uint32 CStream::Version() const
{
	return m_nVersion;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the stream contents version.

void CStream::SetVersion(uint32 nVersion)
{
	m_nVersion = nVersion;
}
