/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TARRAY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The TArray template class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TARRAY_HPP
#define TARRAY_HPP

/******************************************************************************
** 
** This is a template class used for arrays of primitive types.
**
*******************************************************************************
*/

template<class T> class TArray : protected CArray
{
public:
	//
	// Constructors/Destructor.
	//
	TArray();
	~TArray();

	//
	// Methods.
	//
	int Size() const;

	T At(int nIndex) const;
	T operator[](int nIndex) const;

	void Set(int nIndex, T Item);
	int  Add(T Item);
	void Insert(int nIndex, T Item);

	void Remove(int nIndex);
	void RemoveAll();

	int  Find(T Item) const;
	void Swap(int nIndex1, int nIndex2);
};

/******************************************************************************
** 
** This is a TArray based class used for arrays of pointers to objects.
**
*******************************************************************************
*/

template<class T> class TPtrArray : public TArray<T*>
{
public:
	//
	// Methods.
	//
	void Delete(int nIndex);
	void DeleteAll();
};

/******************************************************************************
** 
** This is a TPtrArray based class used for arrays of references to objects.
**
*******************************************************************************
*/

template<class T> class TRefArray : public TPtrArray<T>
{
public:
	//
	// Methods.
	//
	T& At(int nIndex) const;
	T& operator[](int nIndex) const;

	void Set(int nIndex, T& rItem);
	void Set(int nIndex, T* pItem);
	int  Add(T& pItem);
	int  Add(T* rItem);
	void Insert(int nIndex, T& rItem);
	void Insert(int nIndex, T* pItem);
};

/******************************************************************************
**
** Implementation of TArray inline functions.
**
*******************************************************************************
*/

template<class T> inline TArray<T>::TArray<T>()
	: CArray(sizeof(T))
{
}

template<class T> inline TArray<T>::~TArray<T>()
{
}

template<class T> inline int TArray<T>::Size() const
{
	return CArray::Size();
}

template<class T> inline T TArray<T>::At(int nIndex) const
{
	return *((T*)CArray::At(nIndex));
}

template<class T> inline T TArray<T>::operator[](int nIndex) const
{
	return *((T*)CArray::At(nIndex));
}

template<class T> inline void TArray<T>::Set(int nIndex, T Item)
{
	CArray::Set(nIndex, &Item);
}

template<class T> inline int TArray<T>::Add(T Item)
{
	return CArray::Add(&Item);
}

template<class T> inline void TArray<T>::Insert(int nIndex, T Item)
{
	CArray::Insert(nIndex, &Item);
}

template<class T> inline void TArray<T>::Remove(int nIndex)
{
	CArray::Remove(nIndex);
}

template<class T> inline void TArray<T>::RemoveAll()
{
	CArray::RemoveAll();
}

template<class T> inline int TArray<T>::Find(T Item) const
{
	for (int i = 0; i < Size(); i++)
	{
		if (At(i) == Item)
			return i;
	}

	return -1;
}

template<class T> inline void TArray<T>::Swap(int nIndex1, int nIndex2)
{
	T Item1 = At(nIndex1);
	T Item2 = At(nIndex2);

	Set(nIndex1, Item2);
	Set(nIndex2, Item1);
}

/******************************************************************************
**
** Implementation of TPtrArray inline functions.
**
*******************************************************************************
*/

template<class T> inline void TPtrArray<T>::Delete(int nIndex)
{
	delete TArray<T*>::At(nIndex);
	Remove(nIndex);
}

template<class T> inline void TPtrArray<T>::DeleteAll()
{
	for (int i = 0; i < Size(); i++)
		delete TArray<T*>::At(i);

	RemoveAll();
}

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

template<class T> inline T& TRefArray<T>::At(int nIndex) const
{
	return *(TPtrArray<T>::At(nIndex));
}

template<class T> inline T& TRefArray<T>::operator[](int nIndex) const
{
	return *(TPtrArray<T>::At(nIndex));
}

template<class T> inline void TRefArray<T>::Set(int nIndex, T& rItem)
{
	TPtrArray<T>::Set(nIndex, &rItem);
}

template<class T> inline void TRefArray<T>::Set(int nIndex, T* pItem)
{
	ASSERT(pItem != NULL);

	TPtrArray<T>::Set(nIndex, pItem);
}

template<class T> inline int TRefArray<T>::Add(T& rItem)
{
	return TPtrArray<T>::Add(&rItem);
}

template<class T> inline int TRefArray<T>::Add(T* pItem)
{
	ASSERT(pItem != NULL);

	return TPtrArray<T>::Add(pItem);
}

template<class T> inline void TRefArray<T>::Insert(int nIndex, T& rItem)
{
	TPtrArray<T>::Insert(nIndex, &rItem);
}

template<class T> inline void TRefArray<T>::Insert(int nIndex, T* pItem)
{
	ASSERT(pItem != NULL);

	TPtrArray<T>::Insert(nIndex, pItem);
}

#endif //TARRAY_HPP
