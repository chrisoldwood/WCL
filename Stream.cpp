////////////////////////////////////////////////////////////////////////////////
//! \file   Stream.cpp
//! \brief  The CStream class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Stream.hpp"
#include <Core/AnsiWide.hpp>

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
//! Template helper function to read a line of text from the stream. It returns
//! the number of characters read.

template<typename CharT>
size_t CStream::ReadLine(std::vector<CharT>& vBuffer)
{
	if (!IsEOF())
	{
		CharT cChar;
		
		do
		{
			// Read a char.
			Read(&cChar, sizeof(CharT));

			// Append char if not CR or LF.
			if ( (cChar != '\r') && (cChar != '\n') )
				vBuffer.push_back(cChar);
		}
		// Until we reach EOF or EOL.
		while ( (!IsEOF()) && (cChar != '\r') && (cChar != '\n') );

		// Skip LF char, if CR found.
		if ( (!IsEOF()) && (cChar == '\r') )
			Read(&cChar, sizeof(CharT));
	}

	return vBuffer.size();
}

////////////////////////////////////////////////////////////////////////////////
//! Read a line of text. This returns the line of text without the line
//! terminator.

CString CStream::ReadLine(TextFormat eFormat)
{
	CString strLine;

	if (eFormat == ANSI_TEXT)
	{
		std::vector<char> vBuffer;

		// Read a line of ANSI chars.
		if (ReadLine(vBuffer) == 0)
			return TXT("");

		size_t      nChars   = vBuffer.size();
		const char* pszBegin = &vBuffer.front();
		const char* pszEnd   = pszBegin + nChars;

		// Allocate the return buffer.
		strLine.BufferSize(nChars+1);

#ifdef ANSI_BUILD
		std::copy(pszBegin, pszEnd, strLine.Buffer());
#else
		Core::AnsiToWide(pszBegin, pszEnd, strLine.Buffer());
#endif
	}
	else // (eFormat == UNICODE_TEXT)
	{
		std::vector<wchar_t> vBuffer;

		// Read a line of ANSI chars.
		if (ReadLine(vBuffer) == 0)
			return TXT("");

		size_t         nChars   = vBuffer.size();
		const wchar_t* pszBegin = &vBuffer.front();
		const wchar_t* pszEnd   = pszBegin + nChars;

		// Allocate the return buffer.
		strLine.BufferSize(nChars+1);

#ifdef ANSI_BUILD	
		Core::WideToAnsi(pszBegin, pszEnd, strLine.Buffer());
#else
		std::copy(pszBegin, pszEnd, strLine.Buffer());
#endif
	}

	return strLine;
}

////////////////////////////////////////////////////////////////////////////////
//! Write a line of text. This writes a line of text and appends the line
//! terminator.

void CStream::WriteLine(const CString& str, TextFormat eFormat)
{
	size_t nChars = str.Length();

	if (eFormat == ANSI_TEXT)
	{
#ifdef ANSI_BUILD
		Write(str.Buffer(), Core::NumBytes<char>(nChars));
#else
		Write(T2A(str), Core::NumBytes<char>(nChars));
#endif

		Write("\r\n",  Core::NumBytes<char>(2));
	}
	else // (eFormat == UNICODE_TEXT)
	{
#ifdef ANSI_BUILD
		Write(T2W(str), Core::NumBytes<wchar_t>(nChars));
#else
		Write(str.Buffer(), Core::NumBytes<wchar_t>(nChars));
#endif

		Write(L"\r\n", Core::NumBytes<wchar_t>(2));
	}
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
