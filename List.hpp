/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LIST.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CList, CListItem & CListIter class declarations.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef LIST_HPP
#define LIST_HPP

/******************************************************************************
** 
** This class is used to store a node in the list collection.
**
*******************************************************************************
*/

class CListItem
{
public:
	//
	// Constructors/Destructor.
	//
	CListItem();
	virtual ~CListItem();

	//
	// Methods.
	//
	virtual bool operator==(const CListItem& rRHS) const = 0;
	virtual bool operator!=(const CListItem& rRHS) const;

	//
	// Members.
	//
	CListItem*	m_pNext;
};

/******************************************************************************
** 
** The is the base class for all list collections.
**
*******************************************************************************
*/

class CList
{
public:
	//
	// Methods.
	//
	int Length() const;

protected:
	//
	// Constructors/Destructor.
	//
	CList();
	~CList();
	
	//
	// Methods.
	//
	int AddToHead(CListItem& rItem);
	int AddToTail(CListItem& rItem);
	int InsertBefore(CListItem* pPosItem, CListItem& rNewItem);
	int InsertAfter(CListItem* pPosItem, CListItem& rNewItem);
	int Remove(const CListItem& rItem);
	void RemoveAll();
	CListItem* Find(const CListItem& rItem) const;

	//
	// Members.
	//
	CListItem*	m_pHead;
	CListItem*	m_pTail;
	int			m_nLength;

	// Friends.
	friend class CListIter;
};

/******************************************************************************
** 
** The class is used to iterate a list collection.
**
*******************************************************************************
*/

class CListIter
{
public:
	//
	// Constructors/Destructor.
	//
	CListIter(const CList& rList);
	virtual ~CListIter();

	//
	// Methods.
	//
	CListItem* Next();

protected:
	//
	// Members.
	//
	CListItem*	m_pNext;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline bool CListItem::operator!=(const CListItem& rRHS) const
{
	return !(*this == rRHS);
}

inline CListItem* CListIter::Next()
{
	CListItem* pCurrent = m_pNext;

	if (m_pNext)
		m_pNext = m_pNext->m_pNext;

	return pCurrent;
}

#endif //LIST_HPP
