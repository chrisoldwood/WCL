/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PTRARRAY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPtrArray class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PTRARRAY_HPP
#define PTRARRAY_HPP

/******************************************************************************
** 
** This is an array collection that stores generic pointers.
**
*******************************************************************************
*/

class CPtrArray : public CArray
{
protected:
	//
	// Constructors/Destructor.
	//
	CPtrArray();
	~CPtrArray();

	//
	// Methods.
	//
	void* Item(int nIndex) const;
	void* operator[](int nIndex) const;

	void Set(int nIndex, const void* pItem);
	int  Add(const void* pItem);
	void Insert(int nIndex, const void* pItem);
	void Remove(int nIndex);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CPtrArray::CPtrArray() : CArray(sizeof(void*))
{
}

inline CPtrArray::~CPtrArray()
{
}

inline void* CPtrArray::Item(int nIndex) const
{
	return *((void**)CArray::Item(nIndex));
}

inline void* CPtrArray::operator[](int nIndex) const
{
	return CPtrArray::Item(nIndex);
}

inline void CPtrArray::Set(int nIndex, const void* pItem)
{
	CArray::Set(nIndex, &pItem);
}

inline int CPtrArray::Add(const void* pItem)
{
	return CArray::Add(&pItem);
}

inline void CPtrArray::Insert(int nIndex, const void* pItem)
{
	CArray::Insert(nIndex, &pItem);
}

inline void CPtrArray::Remove(int nIndex)
{
	CArray::Remove(nIndex);
}

#endif //PTRARRAY_HPP
