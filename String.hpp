/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRING.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CString class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STRING_HPP
#define STRING_HPP

// Forward declarations.
class CStream;

/******************************************************************************
** 
** This is a simple string container class.
**
*******************************************************************************
*/

class CString
{
public:
	//
	// Constructors/Destructor.
	//
	CString();
	CString(uint iRscID);
	CString(const char* pszBuffer);
	CString(const CString& strSrc);
	~CString();

	void BufferSize(uint iSize);
	void LoadRsc(uint iRscID);

	//
	// Attributes.
	//
	int Length() const;

	//
	// Searching.
	//
	int Find(char cChar, int nStart = 0) const;
	int Count(char cChar) const;

	//
	// Extraction.
	//
	CString Left(int nCount);
	CString Mid(int nFirst, int nCount);
	CString Right(int nCount);

	//
	// Formating.
	//
	void Format(const char* pszFormat, ...);

	//
	// Core operators.
	//
	char& operator[](int nChar);

	const CString& operator=(const CString& strSrc);
	const CString& operator=(const char* pszBuffer);

	operator const char*() const;
	
	//
	// Comparison.
	//
	bool operator ==(const char* pszString) const;
	bool operator !=(const char* pszString) const;

	int Compare(const char* pszString, bool bIgnoreCase = true) const;

	//
	// Mutation operators.
	//
	void operator +=(const char* pszString);
	void operator +=(char cChar);

	//
	// Persistance.
	//
	void operator <<(CStream& rStream);
	void operator >>(CStream& rStream) const;
	
protected:
	/******************************************************************************
	** 
	** This is the structure used to hold the actual string data.
	**
	*******************************************************************************
	*/

	struct StringData
	{
		uint32	m_nRefs;		// Reference count (Unused).
		uint32	m_nSize;		// Size of allocated buffer.
		char	m_acData[1];	// Start of string data.
	};

	//
	// Members.
	//
	char*	m_pszData;			// Pointer to StringData buffer.

	//
	// Internal methods.
	//
	StringData* GetData() const;
	void Copy(const char* lpszBuffer);
	void Copy(const char* lpszBuffer, uint iChars);
	void Free();

	// NULL string.
	static StringData strNULL;
	static char*      pszNULL;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline int CString::Length() const
{
	ASSERT(m_pszData);

	return strlen(m_pszData);
}

inline const CString& CString::operator=(const CString& strSrc)
{
	Copy(strSrc.m_pszData, strSrc.Length());
	return *this;
}

inline const CString& CString::operator=(const char* pszBuffer)
{
	ASSERT(pszBuffer);

	Copy(pszBuffer, strlen(pszBuffer));
	return *this;
}

inline CString::operator const char*() const
{
	ASSERT(m_pszData);
	
	return m_pszData;
}

inline char& CString::operator[](int nChar)
{
	ASSERT( (nChar >=0) && (nChar < Length()) );

	return m_pszData[nChar];
}

inline bool CString::operator ==(const char* pszString) const
{
	return (strcmp(m_pszData, pszString) == 0);
}

inline bool CString::operator !=(const char* pszString) const
{
	return (strcmp(m_pszData, pszString) != 0);
}

inline int CString::Compare(const char* pszString, bool bIgnoreCase) const
{
	return (bIgnoreCase) ? stricmp(m_pszData, pszString) : strcmp(m_pszData, pszString);
}

inline void CString::Copy(const char* lpszBuffer)
{
	Copy(lpszBuffer, strlen(lpszBuffer));
}

inline CString::StringData* CString::GetData() const
{
	return (StringData*) (m_pszData - (2 * sizeof(uint32)));
}

#endif //STRING_HPP
