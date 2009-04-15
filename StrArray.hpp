/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRARRAY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CStrArray class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_STRARRAY_HPP
#define WCL_STRARRAY_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <vector>

/******************************************************************************
** 
** This is an array collection that stores strings.
**
** NB: This class was originally based on a TPtrArray<CString>.
**
*******************************************************************************
*/

class CStrArray
{
public:
	//
	// Constructors/Destructor.
	//
	CStrArray();
	CStrArray(const CStrArray& oRHS);
	~CStrArray();

	//
	// Operators.
	//
	CStrArray& operator=(const CStrArray& oRHS);

	//
	// Methods.
	//
	bool Empty() const;
	size_t Size() const;

	const CString& At(size_t nIndex) const;
	const CString& operator[](size_t nIndex) const;

	void Set(size_t nIndex, const CString& rString);
	size_t Add(const CString& rString);
	void Insert(size_t nIndex, const CString& rString);

	void Delete(size_t nIndex);
	void DeleteAll();

	size_t Find(const tchar* pszString, bool bIgnoreCase = false) const;

private:
	//! The underlying array type..
	typedef std::vector<CString*> StringVector;
	//! A const iterator for the strings vector.
	typedef StringVector::const_iterator CIter;

	//
	// Members.
	//
	StringVector	m_vStrings;		//!< The underlying collection of strings.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CStrArray::CStrArray()
{
}

inline CStrArray::CStrArray(const CStrArray& oRHS)
{
	for (CIter it = oRHS.m_vStrings.begin(); it != oRHS.m_vStrings.end(); ++it)
		m_vStrings.push_back(new CString(*(*it)));
}

inline CStrArray::~CStrArray()
{
	DeleteAll();
}

inline CStrArray& CStrArray::operator=(const CStrArray& oRHS)
{
	if (this != &oRHS)
	{
		DeleteAll();

		for (CIter it = oRHS.m_vStrings.begin(); it != oRHS.m_vStrings.end(); ++it)
			m_vStrings.push_back(new CString(*(*it)));
	}

	return *this;
}

inline bool CStrArray::Empty() const
{
	return m_vStrings.empty();
}

inline size_t CStrArray::Size() const
{
	return m_vStrings.size();
}

inline const CString& CStrArray::At(size_t nIndex) const
{
	ASSERT(nIndex < Size());

	return *(m_vStrings.at(nIndex));
}

inline const CString& CStrArray::operator[](size_t nIndex) const
{
	ASSERT(nIndex < Size());

	return *(m_vStrings[nIndex]);
}

inline void CStrArray::Set(size_t nIndex, const CString& rString)
{
	ASSERT(nIndex < Size());

	*(m_vStrings[nIndex]) = rString;
}

inline size_t CStrArray::Add(const CString& rString)
{
	m_vStrings.push_back(new CString(rString));

	return m_vStrings.size()-1;
}

inline void CStrArray::Insert(size_t nIndex, const CString& rString)
{
	ASSERT(nIndex <= Size());

	m_vStrings.insert(m_vStrings.begin()+nIndex, new CString(rString));
}

inline void CStrArray::Delete(size_t nIndex)
{
	ASSERT(nIndex < Size());

	delete m_vStrings[nIndex];
	m_vStrings.erase(m_vStrings.begin()+nIndex);
}

inline void CStrArray::DeleteAll()
{
	for (CIter it = m_vStrings.begin(); it != m_vStrings.end(); ++it)
		delete *it;

	m_vStrings.clear();
}

inline size_t CStrArray::Find(const tchar* pszString, bool bIgnoreCase) const
{
	ASSERT(pszString != NULL);

	for (CIter it = m_vStrings.begin(); it != m_vStrings.end(); ++it)
	{
		CString* pString = *it;

		if (pString->Compare(pszString, bIgnoreCase) == 0)
			return std::distance(m_vStrings.begin(), it);
	}

	return Core::npos;
}

#endif // WCL_STRARRAY_HPP
