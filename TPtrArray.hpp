/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TPTRARRAY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The TPtrArray template class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TPTRARRAY_HPP
#define TPTRARRAY_HPP

/******************************************************************************
** 
** This is a template class used for pointer based arrays.
**
*******************************************************************************
*/

template<class T> class TPtrArray : protected CPtrArray
{
public:
	//
	// Methods.
	//
	int Size() const;

	T& Item(int nIndex) const;
	T& operator[](int nIndex) const;

	void Set(int nIndex, T& Item);
	int  Add(T& Item);
	void Insert(int nIndex, T& Item);

	void Remove(int nIndex);
	void RemoveAll();

	void Delete(int nIndex);
	void DeleteAll();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

template<class T> inline int TPtrArray<T>::Size() const
{
	return CPtrArray::Size();
}

template<class T> inline T& TPtrArray<T>::Item(int nIndex) const
{
	return *((T*)CPtrArray::Item(nIndex));
}

template<class T> inline T& TPtrArray<T>::operator[](int nIndex) const
{
	return *((T*)CPtrArray::Item(nIndex));
}

template<class T> inline void TPtrArray<T>::Set(int nIndex, T& Item)
{
	CPtrArray::Set(nIndex, &Item);
}

template<class T> inline int TPtrArray<T>::Add(T& Item)
{
	return CPtrArray::Add(&Item);
}

template<class T> inline void TPtrArray<T>::Insert(int nIndex, T& Item)
{
	CPtrArray::Insert(nIndex, &Item);
}

template<class T> inline void TPtrArray<T>::Remove(int nIndex)
{
	CPtrArray::Remove(nIndex);
}

template<class T> inline void TPtrArray<T>::RemoveAll()
{
	CPtrArray::RemoveAll();
}

template<class T> inline void TPtrArray<T>::Delete(int nIndex)
{
	delete &Item(nIndex);
	Remove(nIndex);
}

template<class T> inline void TPtrArray<T>::DeleteAll()
{
	for (int i = 0; i < Size(); i++)
		delete &Item(i);

	RemoveAll();
}

#endif //TPTRARRAY_HPP
