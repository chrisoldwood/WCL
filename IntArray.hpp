/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		INTARRAY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CIntArray class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef INTARRAY_HPP
#define INTARRAY_HPP

/******************************************************************************
** 
** This is an array collection that stores ints.
**
*******************************************************************************
*/

class CIntArray : public CArray
{
public:
	//
	// Constructors/Destructor.
	//
	CIntArray();
	~CIntArray();

	//
	// Methods.
	//
	int Item(int nIndex) const;
	int operator[](int nIndex) const;

	void Set(int nIndex, int nItem);
	int  Add(int nItem);
	void Insert(int nIndex, int nItem);
	void Remove(int nIndex);

	int Find(int nItem) const;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CIntArray::CIntArray() : CArray(sizeof(int))
{
}

inline CIntArray::~CIntArray()
{
}

inline int CIntArray::Item(int nIndex) const
{
	return *((int*)CArray::Item(nIndex));
}

inline int CIntArray::operator[](int nIndex) const
{
	return CIntArray::Item(nIndex);
}

inline void CIntArray::Set(int nIndex, int nItem)
{
	CArray::Set(nIndex, &nItem);
}

inline int CIntArray::Add(int nItem)
{
	return CArray::Add(&nItem);
}

inline void CIntArray::Insert(int nIndex, int nItem)
{
	CArray::Insert(nIndex, &nItem);
}

inline void CIntArray::Remove(int nIndex)
{
	CArray::Remove(nIndex);
}

inline int CIntArray::Find(int nItem) const
{
	for (int i = 0; i < Size(); i ++)
	{
		if (Item(i) == nItem)
			return i;
	}

	return -1;
}

#endif //INTARRAY_HPP
