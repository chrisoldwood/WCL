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
#ifndef STRARRAY_HPP
#define STRARRAY_HPP

/******************************************************************************
** 
** This is an array collection that stores strings.
**
*******************************************************************************
*/

class CStrArray : public CPtrArray
{
public:
	//
	// Constructors/Destructor.
	//
	CStrArray();
	~CStrArray();

	//
	// Methods.
	//
	CString& Item(int nIndex) const;
	CString& operator[](int nIndex) const;

	int  Add(const CString& rString);
	void Insert(int nIndex, const CString& rString);
	void Remove(int nIndex);

	int Find(const char* pszString, bool bIgnoreCase = false) const;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CString& CStrArray::Item(int nIndex) const
{
	return *(static_cast<CString*>(CPtrArray::Item(nIndex)));
}

inline CString& CStrArray::operator[](int nIndex) const
{
	return CStrArray::Item(nIndex);
}

inline int CStrArray::Add(const CString& rString)
{
	return CPtrArray::Add(new CString(rString));
}

inline void CStrArray::Insert(int nIndex, const CString& rString)
{
	CPtrArray::Insert(nIndex, new CString(rString));
}

inline void CStrArray::Remove(int nIndex)
{
	delete &Item(nIndex);
	CPtrArray::Remove(nIndex);
}

#endif //STRARRAY_HPP
