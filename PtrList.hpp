/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PTRLIST.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPtrList, CPtrListItem & CPtrListIter class declarations.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PTRLIST_HPP
#define PTRLIST_HPP

/******************************************************************************
** 
** A generic collection class used to hold a pointer to something.
**
*******************************************************************************
*/

class CPtrList : public CList
{
protected:
	//
	// Constructors/Destructor.
	//
	CPtrList();
	~CPtrList();
	
	//
	// Methods.
	//
	int  AddToHead(void* pData);
	int  AddToTail(void* pData);
	int  InsertBefore(void* pPosItem, void* pData);
	int  InsertAfter(void* pPosItem, void* pData);
	int  Remove(void* pData);
	void RemoveAll();
};

/******************************************************************************
** 
** A node in the generic pointer list collection.
**
*******************************************************************************
*/

class CPtrListItem : public CListItem
{
public:
	//
	// Constructors/Destructor.
	//
	CPtrListItem(void* pData);
	virtual ~CPtrListItem();

	//
	// Methods.
	//
	virtual bool operator==(const CListItem& rRHS) const;

	//
	// Members.
	//
	void*	m_pData;
};

/******************************************************************************
** 
** An iterator for the generic pointer list collection.
**
*******************************************************************************
*/

class CPtrListIter : public CListIter
{
public:
	//
	// Constructors/Destructor.
	//
	CPtrListIter(const CPtrList& rList);
	~CPtrListIter();

	//
	// Methods.
	//
	void* Next();
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

inline CPtrList::CPtrList()
{
}

inline CPtrList::~CPtrList()
{
}

inline CPtrListItem::CPtrListItem(void* pData)
	: m_pData(pData)
{
}

inline CPtrListItem::~CPtrListItem()
{
}

inline bool CPtrListItem::operator==(const CListItem& rRHS) const
{
	CPtrListItem* pRHS = (CPtrListItem*) &rRHS;

	return (m_pData == pRHS->m_pData);
}

inline CPtrListIter::CPtrListIter(const CPtrList& rList)
	: CListIter(rList)
{
}

inline CPtrListIter::~CPtrListIter()
{
}

inline int CPtrList::AddToHead(void* pData)
{
	return CList::AddToHead(*(new CPtrListItem(pData)));
}

inline int CPtrList::AddToTail(void* pData)
{
	return CList::AddToTail(*(new CPtrListItem(pData)));
}

inline int CPtrList::InsertBefore(void* pPosItem, void* pData)
{
	CPtrListItem* pNewItem = new CPtrListItem(pData);

	if (pPosItem == NULL)
		return CList::InsertBefore(NULL, *pNewItem);

	CPtrListItem PosItem(pPosItem);

	return CList::InsertBefore(&PosItem, *pNewItem);
}

inline int CPtrList::InsertAfter(void* pPosItem, void* pData)
{
	CPtrListItem* pNewItem = new CPtrListItem(pData);

	if (pPosItem == NULL)
		return CList::InsertAfter(NULL, *pNewItem);

	CPtrListItem PosItem(pPosItem);

	return CList::InsertAfter(&PosItem, *pNewItem);
}

inline int CPtrList::Remove(void* pData)
{
	return CList::Remove(CPtrListItem(pData));
}

inline void CPtrList::RemoveAll()
{
	CList::RemoveAll();
}

inline void* CPtrListIter::Next()
{
	CPtrListItem* pItem = (CPtrListItem*) CListIter::Next();

	return (pItem != NULL) ? pItem->m_pData : NULL;
}

#ifdef _DEBUG
#undef new
#endif

#endif //PTRLIST_HPP
