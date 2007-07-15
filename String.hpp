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
#ifndef WCL_STRING_HPP
#define WCL_STRING_HPP

// Forward declarations.
class CStrArray;

namespace WCL
{
class IInputStream;
class IOutputStream;
}

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
	CString(const char* pszBuffer, uint iChars);
	CString(const CString& strSrc);
	~CString();

	void BufferSize(uint iSize);
	void LoadRsc(uint iRscID);

	//
	// Attributes.
	//
	bool Empty() const;
	int  Length() const;
	const char* Ptr() const;

	//
	// Mutation.
	//
	void     Insert(int nPos, const char* pszString);
	void     Delete(int nFirst, int nCount = 1);
	void     Replace(char cOldChar, char cNewChar);
	void     Replace(char cChar, const char* pszString);
	void     Replace(const char* pszOldString, const char* pszNewString, bool bIgnoreCase = true);
	CString& RepCtrlChars();
	CString& Trim(bool bLeft = true, bool bRight = true);
	CString& ToLower();
	CString& ToUpper();

 	//
	// Searching.
	//
	int Find(char cChar, int nStart = 0) const;
	int Find(const char* pszStr, int nStart = 0) const;
	int Count(char cChar) const;
	int Count(char cChar, int nStart, int nEnd) const;

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
	void FormatEx(const char* pszFormat, va_list args);

	static CString Fmt(const char* pszFormat, ...);
	static CString FmtEx(const char* pszFormat, va_list args);

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
	bool operator ==(const CString& strString) const;
	bool operator !=(const char* pszString) const;
	bool operator !=(const CString& strString) const;

	int Compare(const char* pszString, bool bIgnoreCase = true) const;
	int Compare(const char* pszString, int nChars, bool bIgnoreCase = true) const;

	//
	// Mutation operators.
	//
	void operator +=(const char* pszString);
	void operator +=(char cChar);

protected:
	/******************************************************************************
	** 
	** This is the structure used to hold the actual string data.
	**
	*******************************************************************************
	*/

	struct StringData
	{
		uint32	m_nAllocSize;	// Size of allocated buffer.
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

	//
	// Persistance.
	//
	friend void operator >>(WCL::IInputStream&  rStream, CString& rString);
	friend void operator <<(WCL::IOutputStream& rStream, const CString& rString);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CString::CString()
	: m_pszData(pszNULL)
{
}

inline CString::CString(uint iRscID)
	: m_pszData(pszNULL)
{
	LoadRsc(iRscID);
}

inline CString::CString(const char* pszBuffer)
	: m_pszData(pszNULL)
{
	Copy(pszBuffer, strlen(pszBuffer));
}

inline CString::CString(const char* pszBuffer, uint iChars)
	: m_pszData(pszNULL)
{
	Copy(pszBuffer, iChars);
}

inline CString::CString(const CString& strSrc)
	: m_pszData(pszNULL)
{
	Copy(strSrc.m_pszData, strSrc.Length());
}

inline CString::~CString()
{
	Free();
}

inline bool CString::Empty() const
{
	ASSERT(m_pszData);

	return (m_pszData[0] == '\0');
}

inline int CString::Length() const
{
	ASSERT(m_pszData);

	return strlen(m_pszData);
}

inline CString& CString::ToLower()
{
	_strlwr(m_pszData);

	return *this;
}

inline CString& CString::ToUpper()
{
	_strupr(m_pszData);

	return *this;
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

inline const char* CString::Ptr() const
{
	ASSERT(m_pszData);
	
	return m_pszData;
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

inline bool CString::operator ==(const CString& strString) const
{
	return (strcmp(m_pszData, strString) == 0);
}

inline bool CString::operator !=(const char* pszString) const
{
	return (strcmp(m_pszData, pszString) != 0);
}

inline bool CString::operator !=(const CString& strString) const
{
	return (strcmp(m_pszData, strString) != 0);
}

inline int CString::Compare(const char* pszString, bool bIgnoreCase) const
{
	return (bIgnoreCase) ? stricmp(m_pszData, pszString) : strcmp(m_pszData, pszString);
}

inline int CString::Compare(const char* pszString, int nChars, bool bIgnoreCase) const
{
	return (bIgnoreCase) ? strnicmp(m_pszData, pszString, nChars) : strncmp(m_pszData, pszString, nChars);
}

inline void CString::Copy(const char* lpszBuffer)
{
	Copy(lpszBuffer, strlen(lpszBuffer));
}

inline CString::StringData* CString::GetData() const
{
	return (StringData*) (m_pszData - sizeof(uint32));
}

/******************************************************************************
** 
** Global string operators.
**
*******************************************************************************
*/

inline CString operator+(const CString& strLHS, const char* pszRHS)
{
	CString str;

	str  = strLHS;
	str += pszRHS;

	return str;
}

inline CString operator+(const char* pszLHS, const CString& strRHS)
{
	CString str;

	str  = pszLHS;
	str += strRHS;

	return str;
}

inline CString operator+(const CString& strLHS, const CString& strRHS)
{
	CString str;

	str  = strLHS;
	str += strRHS;

	return str;
}

#endif // WCL_STRING_HPP
