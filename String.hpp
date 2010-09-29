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

#if _MSC_VER > 1000
#pragma once
#endif

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
	CString(const tchar* pszBuffer);
	CString(const tchar* pszBuffer, size_t iChars);
	CString(const CString& strSrc);
	~CString();

	void BufferSize(size_t nChars);
	void LoadRsc(uint iRscID);

	//
	// Attributes.
	//
	bool Empty() const;
	size_t Length() const;
	const tchar* c_str() const;
	tchar* Buffer() const;
	size_t Capacity() const;

	//
	// Iterators.
	//
	typedef const tchar* const_iterator;
	typedef tchar* iterator;

	const_iterator begin() const;
	const_iterator end() const;
	iterator begin();
	iterator end();

	//
	// Mutation.
	//
	void     Insert(size_t nPos, const tchar* pszString);
	void     Delete(size_t nFirst, size_t nCount = 1);
	void     Replace(tchar cOldChar, tchar cNewChar);
	void     Replace(tchar cChar, const tchar* pszString);
	void     Replace(const tchar* pszOldString, const tchar* pszNewString, bool bIgnoreCase = true);
	CString& RepCtrlChars();
	CString& Trim(bool bLeft = true, bool bRight = true);
	CString& ToLower();
	CString& ToUpper();

 	//
	// Searching.
	//
	size_t Find(tchar cChar, size_t nStart = 0) const;
	size_t Find(const tchar* pszStr, size_t nStart = 0) const;
	size_t Count(tchar cChar) const;
	size_t Count(tchar cChar, size_t nStart, size_t nEnd) const;

	//
	// Extraction.
	//
	CString Left(size_t nCount) const;
	CString Mid(size_t nFirst, size_t nCount) const;
	CString Right(size_t nCount) const;

	//
	// Formating.
	//
	void Format(const tchar* pszFormat, ...);
	void FormatEx(const tchar* pszFormat, va_list args);

	static CString Fmt(const tchar* pszFormat, ...);
	static CString FmtEx(const tchar* pszFormat, va_list args);

	//
	// Core operators.
	//
	tchar& operator[](size_t nChar);

	const CString& operator=(const CString& strSrc);
	const CString& operator=(const tchar* pszBuffer);
	const CString& operator=(const tstring& string);

	operator const tchar*() const;
	
	//
	// Comparison.
	//
	bool operator ==(const tchar* pszString) const;
	bool operator ==(const CString& strString) const;
	bool operator !=(const tchar* pszString) const;
	bool operator !=(const CString& strString) const;
	bool operator  <(const tchar* pszString) const;
	bool operator  <(const CString& strString) const;

	int Compare(const tchar* pszString, bool bIgnoreCase = true) const;
	int Compare(const tchar* pszString, size_t nChars, bool bIgnoreCase = true) const;

	//
	// Mutation operators.
	//
	void operator +=(const tchar* pszString);
	void operator +=(tchar cChar);
	void operator +=(const tstring& string);

protected:
	/******************************************************************************
	** 
	** This is the structure used to hold the actual string data.
	**
	*******************************************************************************
	*/

#pragma pack(push, 1)

	struct StringData
	{
		size_t	m_nAllocSize;	// Size of buffer in characters inc null terminator.
		tchar	m_acData[1];	// Start of string data.
	};

#pragma pack(pop)

	//
	// Members.
	//
	tchar*	m_pszData;			// Pointer to StringData buffer.

	//
	// Internal methods.
	//
	StringData* GetData() const;
	void Copy(const tchar* lpszBuffer);
	void Copy(const tchar* lpszBuffer, size_t nChars);
	void Free();

	// NULL string.
	static StringData strNULL;
	static tchar*     pszNULL;

	//
	// Persistance.
	// NB: We only define an ostream inserter for backwards compatability.
	//
	friend void operator >>(WCL::IInputStream&  rStream, CString& rString);
	friend void operator <<(WCL::IOutputStream& rStream, const CString& rString);
	friend tostream& operator<<(tostream& os, const CString& str);
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

inline CString::CString(const tchar* pszBuffer)
	: m_pszData(pszNULL)
{
	Copy(pszBuffer, tstrlen(pszBuffer));
}

inline CString::CString(const tchar* pszBuffer, size_t iChars)
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

	return (m_pszData[0] == TXT('\0'));
}

inline size_t CString::Length() const
{
	ASSERT(m_pszData);

	return tstrlen(m_pszData);
}

inline CString& CString::ToLower()
{
	tstrlwr(m_pszData);

	return *this;
}

inline CString& CString::ToUpper()
{
	tstrupr(m_pszData);

	return *this;
}

inline const CString& CString::operator=(const CString& strSrc)
{
	Copy(strSrc.m_pszData, strSrc.Length());
	return *this;
}

inline const CString& CString::operator=(const tchar* pszBuffer)
{
	ASSERT(pszBuffer);

	Copy(pszBuffer, tstrlen(pszBuffer));
	return *this;
}

inline const CString& CString::operator=(const tstring& string)
{
	Copy(string.data(), string.length());
	return *this;
}

inline const tchar* CString::c_str() const
{
	ASSERT(m_pszData);
	
	return m_pszData;
}

inline tchar* CString::Buffer() const
{
	ASSERT(m_pszData);
	
	return m_pszData;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the capacity of the buffer in chars, inc the null termiantor. This is
//! the same value that would be passed to BufferSize().

inline size_t CString::Capacity() const
{
	return GetData()->m_nAllocSize;
}

inline CString::const_iterator CString::begin() const
{
	ASSERT(m_pszData != nullptr);
	
	return m_pszData;
}

inline CString::const_iterator CString::end() const
{
	ASSERT(m_pszData != nullptr);
	
	return (m_pszData + tstrlen(m_pszData));
}

inline CString::iterator CString::begin()
{
	ASSERT(m_pszData != nullptr);
	
	return m_pszData;
}

inline CString::iterator CString::end()
{
	ASSERT(m_pszData != nullptr);
	
	return (m_pszData + tstrlen(m_pszData));
}

inline CString::operator const tchar*() const
{
	ASSERT(m_pszData);
	
	return m_pszData;
}

inline tchar& CString::operator[](size_t nChar)
{
	ASSERT(nChar < Capacity());

	return m_pszData[nChar];
}

inline bool CString::operator ==(const tchar* pszString) const
{
	return (tstrcmp(m_pszData, pszString) == 0);
}

inline bool CString::operator ==(const CString& strString) const
{
	return (tstrcmp(m_pszData, strString) == 0);
}

inline bool CString::operator !=(const tchar* pszString) const
{
	return (tstrcmp(m_pszData, pszString) != 0);
}

inline bool CString::operator !=(const CString& strString) const
{
	return (tstrcmp(m_pszData, strString) != 0);
}

inline bool CString::operator <(const tchar* pszString) const
{
	return (tstrcmp(m_pszData, pszString) < 0);
}

inline bool CString::operator <(const CString& strString) const
{
	return (tstrcmp(m_pszData, strString.m_pszData) < 0);
}

inline int CString::Compare(const tchar* pszString, bool bIgnoreCase) const
{
	return (bIgnoreCase) ? tstricmp(m_pszData, pszString) : tstrcmp(m_pszData, pszString);
}

inline int CString::Compare(const tchar* pszString, size_t nChars, bool bIgnoreCase) const
{
	return (bIgnoreCase) ? tstrnicmp(m_pszData, pszString, nChars) : tstrncmp(m_pszData, pszString, nChars);
}

inline void CString::operator +=(const tstring& string)
{
	operator +=(string.c_str());
}

inline void CString::Copy(const tchar* lpszBuffer)
{
	Copy(lpszBuffer, tstrlen(lpszBuffer));
}

inline CString::StringData* CString::GetData() const
{
	byte* pData = reinterpret_cast<byte*>(m_pszData);

	return reinterpret_cast<StringData*>(pData - (sizeof(size_t)));
}

/******************************************************************************
** 
** Global string operators.
**
*******************************************************************************
*/

inline CString operator+(const CString& strLHS, const tchar* pszRHS)
{
	CString str;

	str  = strLHS;
	str += pszRHS;

	return str;
}

inline CString operator+(const tchar* pszLHS, const CString& strRHS)
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

////////////////////////////////////////////////////////////////////////////////
//! STL output stream inserter.

inline tostream& operator<<(tostream& os, const CString& str)
{
	os << str.c_str();
	return os;
}

#endif // WCL_STRING_HPP
