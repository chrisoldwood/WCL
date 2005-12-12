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
** NB: This class was originally based on a TPtrArray<CString>.
**
*******************************************************************************
*/

class CStrArray : protected std::vector<CString*>
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
	int Size() const;

	const CString& At(int nIndex) const;
	const CString& operator[](int nIndex) const;

	void Set(int nIndex, const CString& rString);
	int  Add(const CString& rString);
	void Insert(int nIndex, const CString& rString);

	void Delete(int nIndex);
	void DeleteAll();

	int Find(const char* pszString, bool bIgnoreCase = false) const;

private:
	// Template shorthands.
	typedef std::vector<CString*> CStringVector;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

inline CStrArray::CStrArray()
{
}

inline CStrArray::CStrArray(const CStrArray& oRHS)
{
	typedef CStringVector::const_iterator CIter;

	for (CIter oIter = oRHS.begin(); oIter != oRHS.end(); ++oIter)
		push_back(new CString(*(*oIter)));
}

inline CStrArray::~CStrArray()
{
	DeleteAll();
}

inline CStrArray& CStrArray::operator=(const CStrArray& oRHS)
{
	typedef CStringVector::const_iterator CIter;

	if (this != &oRHS)
	{
		DeleteAll();

		for (CIter oIter = oRHS.begin(); oIter != oRHS.end(); ++oIter)
			push_back(new CString(*(*oIter)));
	}

	return *this;
}

inline int CStrArray::Size() const
{
	return CStringVector::size();
}

inline const CString& CStrArray::At(int nIndex) const
{
	ASSERT((nIndex >= 0) && (nIndex < Size()));

	return *(CStringVector::at(nIndex));
}

inline const CString& CStrArray::operator[](int nIndex) const
{
	ASSERT((nIndex >= 0) && (nIndex < Size()));

	return *(CStringVector::operator[](nIndex));
}

inline void CStrArray::Set(int nIndex, const CString& rString)
{
	ASSERT((nIndex >= 0) && (nIndex < Size()));

	*(CStringVector::operator[](nIndex)) = rString;
}

inline int CStrArray::Add(const CString& rString)
{
	push_back(new CString(rString));

	return size()-1;
}

inline void CStrArray::Insert(int nIndex, const CString& rString)
{
	ASSERT((nIndex >= 0) && (nIndex <= Size()));

	insert(begin()+nIndex, new CString(rString));
}

inline void CStrArray::Delete(int nIndex)
{
	ASSERT((nIndex >= 0) && (nIndex < Size()));

	delete CStringVector::operator[](nIndex);
	erase(begin()+nIndex);
}

inline void CStrArray::DeleteAll()
{
	typedef CStringVector::const_iterator CIter;

	for (CIter oIter = begin(); oIter != end(); ++oIter)
		delete *oIter;

	clear();
}

inline int CStrArray::Find(const char* pszString, bool bIgnoreCase) const
{
	ASSERT(pszString != NULL);

	typedef CStringVector::const_iterator CIter;

	for (CIter oIter = begin(); oIter != end(); ++oIter)
	{
		CString* pString = *oIter;

		if (pString->Compare(pszString, bIgnoreCase) == 0)
			return oIter-begin();
	}

	return -1;
}

#ifdef _DEBUG
#undef new
#endif

#endif //STRARRAY_HPP
