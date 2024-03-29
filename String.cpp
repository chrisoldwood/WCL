/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRING.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CString class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "String.hpp"
#include <stdio.h>
#include <stdarg.h>
#include "Buffer.hpp"
#include "Module.hpp"
#include "IInputStream.hpp"
#include "IOutputStream.hpp"
#include <Core/StringUtils.hpp>
#include <tchar.h>
#include <Core/BadLogicException.hpp>
#include <Core/AnsiWide.hpp>

/******************************************************************************
**
** Class variables.
**
*******************************************************************************
*/

CString::StringData CString::strNULL;

tchar* CString::pszNULL = strNULL.m_acData;

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads a string from the resource file and copies it to the
**				internal buffer.
**
** Parameters:	iRscID	The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::LoadRsc(uint iRscID)
{
	// Initial buffer size.
	size_t nChars = 32;

	BufferSize(nChars+1);

	// Load until buffer is big enough.
	while(static_cast<size_t>(::LoadString(CModule::This().Handle(), iRscID, m_pszData, static_cast<int>(nChars+1))) == nChars)
	{
		nChars *= 2;
		BufferSize(nChars+1);
	}
}

/******************************************************************************
** Method:		BufferSize()
**
** Description:	Ensure enough space is allocated for the string and the null
**				terminator.
**
** Parameters:	iSize	The buffer length in characters, inc a null terminator.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::BufferSize(size_t nChars)
{
	ASSERT(nChars > 0);

	StringData* pData = GetData();

	// Increase buffer size?
	if (pData->m_nAllocSize < nChars)
	{
		Free();

		size_t nBytes = Core::numBytes<tchar>(nChars);

		// Allocate new buffer.
		pData = static_cast<StringData*>(malloc(nBytes + sizeof(StringData)));
		ASSERT(pData != nullptr);

		pData->m_nAllocSize = nChars;
		pData->m_acData[0]  = TXT('\0');

		m_pszData = pData->m_acData;
	}
}

/******************************************************************************
** Method:		Copy()
**
** Description:	Allocates space for and copies the string.
**
** Parameters:	lpszBuffer	The source string.
**				iChars		The number of chars to copy.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::Copy(const tchar* lpszBuffer, size_t nChars)
{
	ASSERT(lpszBuffer);

	// Empty string?
	if (*lpszBuffer == TXT('\0'))
	{
		Free();
		return;
	}

	// Copy.
	BufferSize(nChars+1);
	tstrncpy(m_pszData, lpszBuffer, nChars);

	// Ensure string is terminated.
	m_pszData[nChars] = TXT('\0');
}

/******************************************************************************
** Method:		Free()
**
** Description:	Free up the memory used by the string. This is used internally
**				to ensure there is no memory used by the library when the
**				memory checking functions are called.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::Free()
{
	ASSERT(m_pszData);

	// Not empty string?
	if (m_pszData != pszNULL)
		free(GetData());

	m_pszData = pszNULL;
}

#if (defined NDEBUG) && (__GNUC__ >= 8) // GCC 8+
// error: ... offset 0 from the object at '<unknown>' is out of the bounds of referenced subobject 'CString::StringData::m_acData'...
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif

/******************************************************************************
** Method:		Operator +=()
**
** Description:	Concatenate the supplied string onto the existing one. Growing
**				the buffer if necessary.
**
** Parameters:	rFile	A reference to the file.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::operator +=(const tchar* pszString)
{
	ASSERT(m_pszData);
	ASSERT(pszString);

	// Ignore empty strings.
	if (*pszString == TXT('\0'))
		return;

	size_t iStrLen   = Length();
	size_t iParamLen = tstrlen(pszString);

	StringData* pOldData = GetData();

	// Buffer big enough?
	if (pOldData->m_nAllocSize < (iStrLen+iParamLen+1))
	{
		// Detach old buffer.
		m_pszData = pszNULL;

		// Allocate a new buffer.
		BufferSize(iStrLen+iParamLen+1);

		// Copy old string and cat new one.
		tstrcpy(m_pszData, pOldData->m_acData);
		tstrcat(m_pszData, pszString);

		// Free old string, if not empty string.
		if (pOldData != &strNULL)
			free(pOldData);
	}
	else
	{
		// Just append.
		tstrcat(m_pszData, pszString);
	}
}

/******************************************************************************
** Method:		Operator +=()
**
** Description:	Concatenate the supplied character onto the existing string.
**				It grows the buffer if necessary.
**
** Parameters:	rFile	A reference to the file.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::operator +=(tchar cChar)
{
	// Ignore EOS characters.
	if (cChar == TXT('\0'))
		return;

	size_t iStrLen = Length();

	StringData* pOldData = GetData();

	// Buffer big enough?
	if (pOldData->m_nAllocSize < (iStrLen+2))
	{
		// Detach old buffer.
		m_pszData = pszNULL;

		// Allocate a new buffer.
		BufferSize(iStrLen+2);

		// Copy old string and cat new one.
		tstrcpy(m_pszData, pOldData->m_acData);
		m_pszData[iStrLen]   = cChar;
		m_pszData[iStrLen+1] = TXT('\0');

		// Free old string, if not empty string.
		if (pOldData != &strNULL)
			free(pOldData);
	}
	else
	{
		// Just append.
		m_pszData[iStrLen]   = cChar;
		m_pszData[iStrLen+1] = TXT('\0');
	}
}

#if (defined NDEBUG) && (__GNUC__ >= 8) // GCC 8+
#pragma GCC diagnostic pop
#endif

////////////////////////////////////////////////////////////////////////////////
//! Read a string in from a binary input stream.

template<>
void CString::ReadString<char>(WCL::IInputStream& stream)
{
	uint32 numChars = 0;

	stream >> numChars;

	if (numChars != 0)
	{
		BufferSize(numChars);

#ifdef ANSI_BUILD
		stream.Read(m_pszData, Core::numBytes<char>(numChars));
#else
		CBuffer buffer(Core::numBytes<char>(numChars));
		void* rawBuffer = buffer.Buffer();
		stream.Read(rawBuffer, Core::numBytes<char>(numChars));

		const char* charBuffer = static_cast<const char*>(rawBuffer);
		Core::ansiToWide(charBuffer, charBuffer+numChars, m_pszData);
#endif
	}
}

template<>
void CString::ReadString<wchar_t>(WCL::IInputStream& stream)
{
	uint32 numChars = 0;

	stream >> numChars;

	if (numChars != 0)
	{
		BufferSize(numChars);

#ifdef ANSI_BUILD
		CBuffer buffer(Core::numBytes<wchar_t>(numChars));
		void* rawBuffer = buffer.Buffer();
		stream.Read(rawBuffer, Core::numBytes<wchar_t>(numChars));

		const wchar_t* charBuffer = static_cast<const wchar_t*>(rawBuffer);
		Core::wideToAnsi(charBuffer, charBuffer+numChars, m_pszData);
#else
		stream.Read(m_pszData, Core::numBytes<wchar_t>(numChars));
#endif
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Write a string out to a binary output stream.

template<>
void CString::WriteString<char>(WCL::IOutputStream& stream) const
{
	uint32 numChars = static_cast<uint32>(GetData()->m_nAllocSize);

	stream << numChars;

	if (numChars != 0)
	{
		stream.Write(T2A(m_pszData), Core::numBytes<char>(numChars));
	}
}

template<>
void CString::WriteString<wchar_t>(WCL::IOutputStream& stream) const
{
	uint32 numChars = static_cast<uint32>(GetData()->m_nAllocSize);

	stream << numChars;

	if (numChars != 0)
	{
		stream.Write(T2W(m_pszData), Core::numBytes<wchar_t>(numChars));
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read a string in from a binary input stream.

void operator >>(WCL::IInputStream& stream, CString& string)
{
	string.ReadString<tchar>(stream);
}

////////////////////////////////////////////////////////////////////////////////
//! Write a string out to a binary output stream.

void operator <<(WCL::IOutputStream& stream, const CString& string)
{
	string.WriteString<tchar>(stream);
}

/******************************************************************************
** Method:		Format()
**
** Description:	Format the string using sprintf() style variable args..
**
** Parameters:	See sprintf().
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::Format(const tchar* pszFormat, ...)
{
	va_list	args;
	va_start(args, pszFormat);

	FormatEx(pszFormat, args);

	va_end(args);
}

/******************************************************************************
** Method:		FormatEx()
**
** Description:	Format the string using sprintf() style variable args.
**
** Parameters:	See sprintf().
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::FormatEx(const tchar* pszFormat, va_list args)
{
#ifdef _MSC_VER

	// Allocate the buffer.
	size_t nLength = _vsctprintf(pszFormat, args);

	BufferSize(nLength+1);

	// Format string.
	int nResult = _vsntprintf(m_pszData, nLength, pszFormat, args);

	ASSERT(static_cast<size_t>(nResult) == nLength);

	// Check for buffer overrun.
	if (nResult < 0)
		throw Core::BadLogicException(Core::fmt(TXT("Insufficient buffer size calculated in CString::FormatEx(). Result: %d"), nResult));

	m_pszData[nResult] = TXT('\0');

#else

	// Allocate an initial buffer.
	size_t nLength = 256;

	BufferSize(nLength+1);

	int nResult = -1;

	// Format the string, growing the buffer and repeating if necessary.
	while ((nResult = _vsntprintf(m_pszData, nLength, pszFormat, args)) == -1)
	{
		nLength *= 2;
		BufferSize(nLength+1);
	}

	ASSERT(static_cast<size_t>(nResult) <= nLength);

	// Handle any errors.
	if (nResult < 0)
		throw Core::BadLogicException(Core::fmt(TXT("Insufficient buffer size calculated in CString::FormatEx(). Result: %d"), nResult));

	m_pszData[nResult] = TXT('\0');

#endif
}

/******************************************************************************
** Methods:		Fmt()
**				FmtEx()
**
** Description:	Format the string using sprintf() style variable args..
**
** Parameters:	See sprintf().
**
** Returns:		The formatted string.
**
*******************************************************************************
*/

CString CString::Fmt(const tchar* pszFormat, ...)
{
	CString str;

	va_list	args;
	va_start(args, pszFormat);

	str.FormatEx(pszFormat, args);

	va_end(args);

	return str;
}

CString CString::FmtEx(const tchar* pszFormat, va_list args)
{
	CString str;

	str.FormatEx(pszFormat, args);

	return str;
}

/******************************************************************************
** Method:		Find()
**
** Description:	Finds the first occurence of the character in the string
**				starting from the position specified.
**
** Parameters:	cChar	The character to find.
**
** Returns:		The zero based index of the character OR
**				-1 if the character was not found.
**
*******************************************************************************
*/

size_t CString::Find(tchar cChar, size_t nStart) const
{
	ASSERT(nStart <= Length());

	const tchar* psz = tstrchr(m_pszData + nStart, cChar);

	return (psz == nullptr) ? Core::npos : (psz - m_pszData);
}

/******************************************************************************
** Method:		Find()
**
** Description:	Finds the first occurence of the substring in the string
**				starting from the position specified.
**
** Parameters:	pszStr	The substring to find.
**
** Returns:		The zero based index of the character OR
**				-1 if the character was not found.
**
*******************************************************************************
*/

size_t CString::Find(const tchar* pszStr, size_t nStart) const
{
	ASSERT(nStart <= Length());

	const tchar* psz = tstrstr(m_pszData + nStart, pszStr);

	return (psz == nullptr) ? Core::npos : (psz - m_pszData);
}

/******************************************************************************
** Method:		Count()
**
** Description:	Counts the number of times the specified character occurs in
**				the string.
**
** Parameters:	cChar	The character to count.
**
** Returns:		The number of occurrences.
**
*******************************************************************************
*/

size_t CString::Count(tchar cChar) const
{
	size_t nMatches = 0;
	size_t nPos     = Core::npos;

	while ((nPos = Find(cChar, nPos+1)) != Core::npos)
		++nMatches;

	return nMatches;
}

/******************************************************************************
** Method:		Count()
**
** Description:	Counts the number of times the specified character occurs in
**				part of the string.
**
** Parameters:	cChar	The character to count.
**				nStart	The start character.
**				nEnd	The end character + 1.
**
** Returns:		The number of occurrences.
**
*******************************************************************************
*/

size_t CString::Count(tchar cChar, size_t nStart, size_t nEnd) const
{
	ASSERT(nEnd   <= Length());
	ASSERT(nStart <= nEnd);

	size_t       nMatches = 0;
	const tchar* pszStart = m_pszData+nStart;
	const tchar* pszEnd   = m_pszData+nEnd;

	while (pszStart < pszEnd)
	{
		if (*pszStart == cChar)
			++nMatches;

		++pszStart;
	}

	return nMatches;
}

/******************************************************************************
** Method:		Left()
**
** Description:	Extracts a substring based on the leftmost n characters.
**
** Parameters:	nCount		The number of characters to extract.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CString::Left(size_t nCount) const
{
	ASSERT(nCount <= Length());

	// Empty string?
	if ( (nCount == 0) || (Length() == 0) )
		return TXT("");

	CString str;

	str.BufferSize(nCount+1);
	tstrncpy(str.m_pszData, m_pszData, nCount);
	str.m_pszData[nCount] = TXT('\0');

	return str;
}

/******************************************************************************
** Method:		Mid()
**
** Description:	Extracts a substring based on the middlemost n characters
**				starting at the first character specified.
**
** Parameters:	nFirst		The first character in the substring.
**				nCount		The number of characters to extract.
**
** Returns:		The number of occurrences.
**
*******************************************************************************
*/

CString CString::Mid(size_t nFirst, size_t nCount) const
{
	ASSERT(nFirst <= Length());
	ASSERT(nCount <= Length());
	ASSERT((nFirst + nCount) <= Length());

	// Empty string?
	if ( (nCount == 0) || (Length() == 0) )
		return TXT("");

	CString str;

	str.BufferSize(nCount+1);
	tstrncpy(str.m_pszData, m_pszData+nFirst, nCount);
	str.m_pszData[nCount] = TXT('\0');

	return str;
}

/******************************************************************************
** Method:		Right()
**
** Description:	Extracts a substring based on the rightmost n characters.
**
** Parameters:	nCount		The number of characters to extract.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CString::Right(size_t nCount) const
{
	ASSERT(nCount <= Length());

	// Empty string?
	if ( (nCount == 0) || (Length() == 0) )
		return TXT("");

	CString str;

	str.BufferSize(nCount+1);
	tstrncpy(str.m_pszData, m_pszData+Length()-nCount, nCount);
	str.m_pszData[nCount] = TXT('\0');

	return str;
}

/******************************************************************************
** Method:		Insert()
**
** Description:	Inserts the given string at the position specified.
**
** Parameters:	nPos		The position of the insertion.
**				pszString	The string to insert.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::Insert(size_t nPos, const tchar* pszString)
{
	ASSERT(pszString != nullptr);
	ASSERT(nPos <= tstrlen(m_pszData));

	// Get extra text length.
	size_t nTextLen = tstrlen(pszString);

	if (nTextLen == 0)
		return;

	// Get current length.
	size_t nThisLen = Length();

	// Appending?
	if (nPos == nThisLen)
	{
		// Use concat operator.
		operator+=(pszString);
	}
	// Inserting.
	else
	{
		StringData* pOldData = GetData();

		// Detach old buffer.
		m_pszData = pszNULL;

		// Allocate a new buffer.
		BufferSize(nThisLen+nTextLen+1);

		// Copy leading chars from old text.
		tstrncpy(m_pszData, pOldData->m_acData, nPos);

		// Copy new text.
		tstrncpy(m_pszData+nPos, pszString, nTextLen);

		// Copy trailing chars from old text.
		tstrncpy(m_pszData+nPos+nTextLen, pOldData->m_acData+nPos, nThisLen-nPos);

		// Terminate string.
		m_pszData[nThisLen+nTextLen] = TXT('\0');

		// Free old string, if not empty string.
		if (pOldData != &strNULL)
			free(pOldData);
	}
}

/******************************************************************************
** Method:		Delete()
**
** Description:	Deletes a number of characters, from the specified position.
**
** Parameters:	nFirst		The first character to be deleted.
**				nCount		The number of characters to delete.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::Delete(size_t nFirst, size_t nCount)
{
	// Ignore, if doing nothing.
	if (nCount <= 0)
		return;

	// Get current length.
	size_t nLength = Length();

	ASSERT(nFirst < nLength);
	ASSERT((nFirst+nCount) <= nLength);

	// Emptying string?
	if ( (nFirst == 0) && (nCount == nLength) )
	{
		Free();
		return;
	}

	tchar* pszDst = m_pszData + nFirst;
	tchar* pszSrc = pszDst + nCount;

	// Move string contents down.
	tstrcpy(pszDst, pszSrc);
}

/******************************************************************************
** Method:		Replace()
**
** Description:	Replaces a character with another character.
**
** Parameters:	cOldChar	The character to replace.
**				cNewChar	The character to replace it with.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::Replace(tchar cOldChar, tchar cNewChar)
{
	tchar* psz = m_pszData;

	while (*psz != TXT('\0'))
	{
		if (*psz == cOldChar)
			*psz = cNewChar;

		++psz;
	}
}

/******************************************************************************
** Method:		Replace()
**
** Description:	Replaces a character with a string.
**
** Parameters:	cChar		The character to replace.
**				pszString	The string to replace it with.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::Replace(tchar cChar, const tchar* pszString)
{
	ASSERT(pszString != nullptr);

	CString      str;
	const tchar* psz = m_pszData;

	while (*psz != TXT('\0'))
	{
		if (*psz == cChar)
			str += pszString;
		else
			str += *psz;

		++psz;
	}

	Copy(str);
}

/******************************************************************************
** Method:		Replace()
**
** Description:	Replaces one string with another string, ignoring case if
**				required.
**
** Parameters:	pszOldString	The string to replace.
**				pszNewString	The string to replace it with.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::Replace(const tchar* pszOldString, const tchar* pszNewString, bool bIgnoreCase)
{
	ASSERT(pszOldString != nullptr);
	ASSERT(pszNewString != nullptr);

	typedef int (*CompareFn)(const tchar*, const tchar*, size_t);

	CString      str;
	const tchar* psz = m_pszData;

	// Presize to current string length.
	str.BufferSize(Length()+1);

	// Choose the compare function.
	CompareFn lpfnCompare = (bIgnoreCase) ? tstrnicmp : tstrncmp;
	size_t    nCmpLen     = tstrlen(pszOldString);

	while (*psz != TXT('\0'))
	{
		// Found a match?
		if (lpfnCompare(psz, pszOldString, nCmpLen) == 0)
		{
			psz += tstrlen(pszOldString);
			str += pszNewString;
		}
		else
		{
			str += *psz;
			psz += 1;
		}
	}

	Copy(str);
}

/******************************************************************************
** Method:		RepCtrlChars()
**
** Description:	Replaces any control characters with its "C" equivalent.
**				e.g. 0x0A -> "\n"
**
** Parameters:	None.
**
** Returns:		This.
**
*******************************************************************************
*/

CString& CString::RepCtrlChars()
{
	Replace(TXT('\t'), TXT("\\t"));
	Replace(TXT('\r'), TXT("\\r"));
	Replace(TXT('\n'), TXT("\\n"));

	return *this;
}

/******************************************************************************
** Method:		Trim()
**
** Description:	Trims the leading and/or trailing whitespace from the string.
**
** Parameters:	bLeft	Trim leading whitespace.
**				bRight	Trim trailing whitespace.
**
** Returns:		This.
**
*******************************************************************************
*/

CString& CString::Trim(bool bLeft, bool bRight)
{
	// Trim leading?
	if (bLeft)
	{
		size_t nChars = 0;

		for (tchar* psz = m_pszData; (*psz != TXT('\0')) && (tisspace(static_cast<utchar>(*psz))); ++psz)
			++nChars;

		Delete(0, nChars);
	}

	size_t nLength = Length();

	// Trim trailing?
	if (bRight)
	{
		size_t nChars = 0;

		for (tchar* psz = m_pszData+nLength-1; (psz >= m_pszData) && (tisspace(static_cast<utchar>(*psz))); --psz)
			++nChars;

		Delete(nLength-nChars, nChars);
	}

	return *this;
}
