/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRING.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CString class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <stdio.h>
#include <stdarg.h>

/******************************************************************************
**
** Class variables.
**
*******************************************************************************
*/

CString::StringData CString::strNULL;

char* CString::pszNULL = strNULL.m_acData;

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
	int iBufSize = 4;
	BufferSize(iBufSize);

	// Load until buffer is big enough.
	while(::LoadString(CModule::This().Handle(), iRscID, m_pszData, iBufSize) == (iBufSize-1))
	{
		iBufSize *= 2;
		BufferSize(iBufSize);
	}
}

/******************************************************************************
** Method:		BufferSize()
**
** Description:	Ensure enough space is allocated for the string.
**
** Parameters:	iSize
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::BufferSize(uint iSize)
{
	ASSERT(iSize);

	StringData* pData = GetData();

	// Increase buffer size?
	if (pData->m_nSize < iSize)
	{
		Free();
		
		// Allocate new buffer.
		pData = (StringData*) malloc(iSize + sizeof(StringData));
		ASSERT(pData != NULL);

		pData->m_nRefs     = 0;
		pData->m_nSize     = iSize;
		pData->m_acData[0] = '\0';

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

void CString::Copy(const char* lpszBuffer, uint iChars)
{
	ASSERT(lpszBuffer);

	// NULL string?
	if (*lpszBuffer == '\0')
	{
		Free();
		return;
	}

	// Copy.
	BufferSize(iChars+1);
	strncpy(m_pszData, lpszBuffer, iChars);

	// Ensure string is terminated.
	m_pszData[iChars] = '\0';
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

void CString::operator +=(const char* pszString)
{
	ASSERT(m_pszData);
	ASSERT(pszString);

	// Ignore NULL strings.
	if (*pszString == '\0')
		return;

	uint iStrLen   = Length();
	uint iParamLen = strlen(pszString);
	
	StringData* pOldData = GetData();

	// Buffer big enough?
	if (pOldData->m_nSize < (iStrLen+iParamLen+1))
	{
		// Detach old buffer.
		m_pszData = pszNULL;

		// Allocate a new buffer.
		BufferSize(iStrLen+iParamLen+1);
		
		// Copy old string and cat new one.
		strcpy(m_pszData, pOldData->m_acData);
		strcat(m_pszData, pszString);
		
		// Free old string, if not empty string.
		if (pOldData != &strNULL)
			free(pOldData);
	}
	else
	{
		// Just append.
		strcat(m_pszData, pszString);
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

void CString::operator +=(char cChar)
{
	// Ignore EOS characters.
	if (cChar == '\0')
		return;

	uint iStrLen = Length();
	
	StringData* pOldData = GetData();

	// Buffer big enough?
	if (pOldData->m_nSize < (iStrLen+2))
	{
		// Detach old buffer.
		m_pszData = pszNULL;

		// Allocate a new buffer.
		BufferSize(iStrLen+2);
		
		// Copy old string and cat new one.
		strcpy(m_pszData, pOldData->m_acData);
		m_pszData[iStrLen]   = cChar;
		m_pszData[iStrLen+1] = '\0';
		
		// Free old string, if not empty string.
		if (pOldData != &strNULL)
			free(pOldData);
	}
	else
	{
		// Just append.
		m_pszData[iStrLen]   = cChar;
		m_pszData[iStrLen+1] = '\0';
	}
}

/******************************************************************************
** Method:		operator>>()
**
** Description:	Load the string in from a stream. This reads the buffer size,
**				allocates the space and reads the whole string.
**
** Parameters:	rStream		The stream to read from.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::operator <<(CStream& rStream)
{
	uint32 iSize = 0;

	rStream >> iSize;

	if (iSize)
	{
		BufferSize(iSize);
		rStream.Read(m_pszData, iSize);
	}
}

/******************************************************************************
** Method:		operator<<()
**
** Description:	Save the string out to a stream. This stores the size of the
**				buffer followed by the buffer.
**
** Parameters:	rStream		The stream to write to.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CString::operator >>(CStream& rStream) const
{
	StringData* pData = GetData();

	rStream << pData->m_nSize;

	if (pData->m_nSize)
		rStream.Write(m_pszData, pData->m_nSize);
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

void CString::Format(const char* pszFormat, ...)
{
	// Setup arguments.
	va_list	args;
	va_start(args, pszFormat);

	int nMaxLength  = 0;
	int nRealLength = 0;

	// Parse the string to calculate its max length.
	for (const char* pszBuf = pszFormat; *pszBuf != '\0'; pszBuf++)
	{
		// Is not a format start char OR is a "%%" sequence?
		if ( (*pszBuf != '%') || (*(++pszBuf) == '%') )
		{
			nMaxLength++;
			continue;
		}

		// Process flags.
		while ( (*pszBuf == '-') || (*pszBuf == '+') || (*pszBuf == '0')
			 || (*pszBuf == ' ') || (*pszBuf == '#') )
		{
			// Allow for "0x"
			if (*pszBuf == '#') 
				nMaxLength += 2;

			pszBuf++;
		}

		int nWidth = 0;

		// Width is an argument?
		if (*pszBuf == '*')
			nWidth = va_arg(args, int);
		else
			nWidth = atoi(pszBuf);

		// Skip width chars.
		while ( (*pszBuf == '*') || (isdigit(*pszBuf)) )
			pszBuf++;

		int nPrecision = 0;

		// Precision specified?
		if (*pszBuf == '.')
		{
			pszBuf++;

			// Precision is an argument?
			if (*pszBuf == '*')
				nPrecision = va_arg(args, int);
			else
				nPrecision = atoi(pszBuf);

			// Skip precision chars.
			while ( (*pszBuf == '*') || (isdigit(*pszBuf)) )
				pszBuf++;
		}

		// Skip optional prefixes.
		if ( (*pszBuf == 'h') || (*pszBuf == 'l') || (*pszBuf == 'F')
		  || (*pszBuf == 'N') || (*pszBuf == 'L') )
		{
			pszBuf++;
		}

		// Default value length to specifiers.
		int nValLength = nWidth + nPrecision;

		// Process type.
		switch (*pszBuf)
		{
			// Single char.
			case 'c':
				{
					va_arg(args, char);
					nValLength = 1;
				}
				break;

			// String.
			case 's':
				{
					const char* psz = va_arg(args, const char*);
					nValLength = max(strlen(psz), (size_t)nValLength);
				}
				break;

			// Integral number.
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
				{
					va_arg(args, int);
					nValLength = max(32, nValLength);
				}
				break;

			// Floating point number.
			case 'e':
			case 'f':
			case 'g':
			case 'G':
				{
					va_arg(args, double);
					nValLength = max(32, nValLength);
				}
				break;

			// Pointer.
			case 'p':
				{
					va_arg(args, void*);
					nValLength = max(32, nValLength);
				}
				break;

			// Chars written so far.
			case 'n':
				{
					va_arg(args, int*);
				}
				break;

			default:
				{
					ASSERT(false);
				}
				break;
		}

		// Add length of value on.
		nMaxLength += nValLength;
	}

	// Reset arguments.
    va_end(args);
	va_start(args, pszFormat);
	
	// Set the buffer size.
	BufferSize(nMaxLength+1);

	// Format string.
	nRealLength = vsprintf(m_pszData, pszFormat, args);
	ASSERT(nRealLength <= nMaxLength);

	va_end(args);
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

int CString::Find(char cChar, int nStart) const
{
	ASSERT( (nStart >= 0) && (nStart <= Length()) );

	const char* psz = strchr(m_pszData + nStart, cChar);

	return (psz == NULL) ? -1 : (psz - m_pszData);
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

int CString::Find(const char* pszStr, int nStart) const
{
	ASSERT( (nStart >= 0) && (nStart <= Length()) );

	const char* psz = strstr(m_pszData + nStart, pszStr);

	return (psz == NULL) ? -1 : (psz - m_pszData);
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

int CString::Count(char cChar) const
{
	int nMatches = 0;
	int nPos     = -1;

	while ((nPos = Find(cChar, nPos+1)) != -1)
		nMatches++;

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

CString CString::Left(int nCount)
{
	ASSERT( (nCount >= 0) && (nCount <= Length()) );

	// Empty string?
	if ( (nCount == 0) || (Length() == 0) )
		return "";

	CString str;

	str.BufferSize(nCount+1);
	strncpy(str.m_pszData, m_pszData, nCount);
	str.m_pszData[nCount] = '\0';

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

CString CString::Mid(int nFirst, int nCount)
{
	ASSERT( (nFirst >= 0) && (nFirst <= Length()) );
	ASSERT( (nCount >= 0) && (nCount <= Length()) );
	ASSERT( (nFirst + nCount) <= Length() ); 

	// Empty string?
	if ( (nCount == 0) || (Length() == 0) )
		return "";

	CString str;

	str.BufferSize(nCount+1);
	strncpy(str.m_pszData, m_pszData+nFirst, nCount);
	str.m_pszData[nCount] = '\0';

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

CString CString::Right(int nCount)
{
	ASSERT( (nCount >= 0) && (nCount <= Length()) );

	// Empty string?
	if ( (nCount == 0) || (Length() == 0) )
		return "";

	CString str;

	str.BufferSize(nCount+1);
	strncpy(str.m_pszData, m_pszData+Length()-nCount, nCount);
	str.m_pszData[nCount] = '\0';

	return str;
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

void CString::Delete(int nFirst, int nCount)
{
	ASSERT(nFirst >= 0);
	ASSERT(nCount >= 0);

	// Ignore, if doing nothing.
	if (nCount <= 0)
		return;

	// Get current length.
	int nLength = Length();

	ASSERT(nFirst < nLength);
	ASSERT((nFirst+nCount) <= nLength);

	// Emptying string?
	if ( (nFirst == 0) && (nCount == nLength) )
	{
		Free();
		return;
	}

	char* pszDst = m_pszData + nFirst;
	char* pszSrc = pszDst + nCount;

	// Move string contents down.
	strcpy(pszDst, pszSrc);
}

/******************************************************************************
** Method:		Split()
**
** Description:	Splits a string into separate fields.
**
** Parameters:	pszSeps		The list of separators.
**				astrFields	The array into which the fields are returned.
**
** Returns:		The number of fields.
**
*******************************************************************************
*/

uint CString::Split(const char* pszSeps, CStrArray& astrFields)
{
	ASSERT(pszSeps != NULL);

	int nSepPos = -1;
	int nLength = Length();

	// Until EoS...
	while (nSepPos < (nLength-1))
	{
		int nFirstChar = nSepPos + 1;

		// Find next occurence of a separator.
		nSepPos = strcspn(m_pszData + nFirstChar, pszSeps) + nFirstChar;

		int nCount = nSepPos - nFirstChar;

		// Extract string.
		CString strField(m_pszData + nFirstChar, nCount);

		// Add to fields collection.
		astrFields.Add(strField);
	}

	return astrFields.Size();
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
		int nChars = 0;

		for (char* psz = m_pszData; (*psz != '\0') && (isspace(*psz)); ++psz)
			nChars++;

		Delete(0, nChars);
	}

	int nLength = Length();

	// Trim trailing?
	if (bRight)
	{
		int nChars = 0;

		for (char* psz = m_pszData+nLength-1; (psz >= m_pszData) && (isspace(*psz)); --psz)
			nChars++;

		Delete(nLength-nChars, nChars);
	}

	return *this;
}
