/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TLIST.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The TList class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TLIST_HPP
#define TLIST_HPP

/******************************************************************************
** 
** This is a template class used for lists of primitive types.
**
*******************************************************************************
*/

template<class T>
class TList : public CList
{
public:
	//
	// Constructors/Destructor.
	//
	TList();
	~TList();
	
	//
	// Methods.
	//
	int  AddToHead(T Value);
	int  AddToTail(T Value);
	void RemoveAll();
};

/******************************************************************************
** 
** This is the class used for items stored in the list.
**
*******************************************************************************
*/

template<class T>
class TListItem : public CListItem
{
public:
	//
	// Constructors/Destructor.
	//
	TListItem(T Value);
	virtual ~TListItem();

	//
	// Methods.
	//
	virtual bool operator==(const CListItem& rRHS) const;

	//
	// Members.
	//
	T	m_Value;
};

/******************************************************************************
** 
** The class used to iterate a list collection.
**
*******************************************************************************
*/

template<class T>
class TListIter : public CListIter
{
public:
	//
	// Constructors/Destructor.
	//
	TListIter(const TList<T>& rList);
	virtual ~TListIter();

	//
	// Methods.
	//
	bool Next(T& Value);
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

template<class T>
inline TList<T>::TList()
{
}

template<class T>
inline TList<T>::~TList()
{
}

template<class T>
inline int  TList<T>::AddToHead(T Value)
{
	return CList::AddToHead(*(new TListItem<T>(Value)));
}

template<class T>
inline int  TList<T>::AddToTail(T Value)
{
	return CList::AddToTail(*(new TListItem<T>(Value)));
}

template<class T>
inline void TList<T>::RemoveAll()
{
	CList::RemoveAll();
}

template<class T>
inline TListItem<T>::TListItem(T Value)
	: m_Value(Value)
{
}

template<class T>
inline TListItem<T>::~TListItem()
{
}

template<class T>
inline bool TListItem<T>::operator==(const CListItem& rRHS) const
{
	const TListItem<T>* pRHS = static_cast<const TListItem<T>*>(&rRHS);

	return (m_Value == pRHS->m_Value);
}

template<class T>
inline TListIter<T>::TListIter(const TList<T>& rList)
	: CListIter(rList)
{
}

template<class T>
inline TListIter<T>::~TListIter()
{
}

template<class T>
inline bool TListIter<T>::Next(T& Value)
{
	CListItem* pItem = CListIter::Next();

	if (pItem != NULL)
		Value = static_cast<TListItem<T>*>(pItem)->m_Value;

	return (pItem != NULL);
}

#ifdef _DEBUG
#undef new
#endif

#endif // TLIST_HPP
