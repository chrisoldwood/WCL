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

class CStrArray : protected TPtrArray<CString>
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
	int Size() const;

	const CString& At(int nIndex) const;
	const CString& operator[](int nIndex) const;

	void Set(int nIndex, const CString& rString);
	int  Add(const CString& rString);
	void Insert(int nIndex, const CString& rString);

	void Delete(int nIndex);
	void DeleteAll();

	int Find(const char* pszString, bool bIgnoreCase = false) const;
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

inline CStrArray::~CStrArray()
{
	DeleteAll();
}

inline int CStrArray::Size() const
{
	return TPtrArray<CString>::Size();
}

inline const CString& CStrArray::At(int nIndex) const
{
	return *(TPtrArray<CString>::At(nIndex));
}

inline const CString& CStrArray::operator[](int nIndex) const
{
	return *(TPtrArray<CString>::At(nIndex));
}

inline void CStrArray::Set(int nIndex, const CString& rString)
{
	*(TPtrArray<CString>::At(nIndex)) = rString;
}

inline int CStrArray::Add(const CString& rString)
{
	return TPtrArray<CString>::Add(new CString(rString));
}

inline void CStrArray::Insert(int nIndex, const CString& rString)
{
	TPtrArray<CString>::Insert(nIndex, new CString(rString));
}

inline void CStrArray::Delete(int nIndex)
{
	TPtrArray<CString>::Delete(nIndex);
}

inline void CStrArray::DeleteAll()
{
	TPtrArray<CString>::DeleteAll();
}

inline int CStrArray::Find(const char* pszString, bool bIgnoreCase) const
{
	ASSERT(pszString != NULL);

	for (int i = 0; i < Size(); i++)
	{
		if (At(i).Compare(pszString, bIgnoreCase) == 0)
			return i;
	}

	return -1;
}

#endif //STRARRAY_HPP
