/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LIST.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CList, CListItem & CListIter class definitions.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CList::CList()
	: m_pHead(NULL)
	, m_pTail(NULL)
	, m_nLength(0)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	Frees the list items.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CList::~CList()
{
	RemoveAll();
}

/******************************************************************************
** Method:		AddToHead()
**
** Description:	Adds an item to the head of the list.
**
** Parameters:	rItem	The item to add.
**
** Returns:		The position of insertion.
**
*******************************************************************************
*/

int CList::AddToHead(CListItem& rItem)
{
	// Append to head.
	rItem.m_pNext = m_pHead;
	m_pHead = &rItem;

	// Update tail, if empty.
	if (m_pTail == NULL)
		m_pTail = m_pHead;

	// Update length;
	m_nLength++;

	return 0;
}

/******************************************************************************
** Method:		AddToTail()
**
** Description:	Adds an item to the tail of the list.
**
** Parameters:	rItem	The item to add.
**
** Returns:		The position of insertion.
**
*******************************************************************************
*/

int CList::AddToTail(CListItem& rItem)
{
	// Append to tail.
	if (m_pTail != NULL)
		m_pTail->m_pNext = &rItem;

	// Update tail.
	m_pTail = &rItem;

	// Update head, if empty.
	if (m_pHead == NULL)
		m_pHead = m_pTail;

	// Update length;
	m_nLength++;

	return (m_nLength - 1);
}

/******************************************************************************
** Method:		InsertBefore()
**
** Description:	Inserts an item before another one in the list.
**
** Parameters:	pPosItem	The item to insert before.
**				rNewItem	The item to insert.
**
** Returns:		The position of insertion.
**
*******************************************************************************
*/

int CList::InsertBefore(CListItem* pPosItem, CListItem& rNewItem)
{
	// Insert at/before current head?
	if ( (pPosItem == NULL) || (*pPosItem == *m_pHead) )
		return AddToHead(rNewItem);

	CListItem*  pTmp   = m_pHead;
	CListItem** ppPrev = &m_pHead;
	int			nPos   = 0;

	// Find the item to insert before.
	while ( (pTmp) && (*pTmp != *pPosItem) )
	{
		ppPrev = &pTmp->m_pNext;
		pTmp   = pTmp->m_pNext;
		nPos++;
	}

	ASSERT(pTmp);

	// Insert.
	*ppPrev          = &rNewItem;
	rNewItem.m_pNext = pTmp;

	// Update length;
	m_nLength++;

	return nPos;
}

/******************************************************************************
** Method:		InsertAfter()
**
** Description:	Inserts an item after another one in the list.
**
** Parameters:	pPosItem	The item to insert after.
**				rNewItem	The item to insert.
**
** Returns:		The position of insertion.
**
*******************************************************************************
*/

int CList::InsertAfter(CListItem* pPosItem, CListItem& rNewItem)
{
	// Insert at head?
	if (pPosItem == NULL)
		return AddToHead(rNewItem);

	// Insert after tail?
	if (*pPosItem == *m_pTail)
		return AddToTail(rNewItem);

	ASSERT_FALSE();

	// Update length;
	m_nLength++;

	return -1;
}

/******************************************************************************
** Method:		Remove()
**
** Description:	Removes an item from the list.
**
** Parameters:	rItem	The item to remove.
**
** Returns:		The position of deletion.
**
*******************************************************************************
*/

int CList::Remove(const CListItem& rItem)
{
	CListItem*  pTmp   = m_pHead;
	CListItem*  pPrev  = m_pHead;
	CListItem** ppPrev = &m_pHead;
	int			nPos   = 0;

	// Find item.
	while ( (pTmp != NULL) && (rItem != *pTmp) )
	{
		pPrev  = pTmp;
		ppPrev = &pTmp->m_pNext;
		pTmp   = pTmp->m_pNext;
		nPos++;
	}

	ASSERT(pTmp);

	// Remove.
	*ppPrev = pTmp->m_pNext;

	// Fixup tail, if required.
	if (pTmp == m_pTail)
		m_pTail = pPrev;

	// Fixup head, if required.
	if (m_pHead == NULL)
		m_pTail = NULL;

	delete pTmp;

	// Update length;
	m_nLength--;

	return nPos;
}

/******************************************************************************
** Method:		RemoveAll()
**
** Description:	Removes all items from the list.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CList::RemoveAll()
{
	CListItem* pItem = m_pHead;

	// Free the list.
	while (pItem)
	{
		CListItem* pTmp = pItem;
		pItem = pItem->m_pNext;
		delete pTmp;
	}

	// Reset members.
	m_pHead   = NULL;
	m_pTail   = NULL;
	m_nLength = 0;
}

/******************************************************************************
** Method:		Find()
**
** Description:	Finds an item in the list.
**
** Parameters:	rItem	The item to find.
**
** Returns:		The item or NULL.
**
*******************************************************************************
*/

CListItem* CList::Find(const CListItem& rItem) const
{
	CListItem* pTmp = m_pHead;

	while( (pTmp) && (*pTmp != rItem) )
		pTmp = pTmp->m_pNext;

	return pTmp;
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CListItem::CListItem()
	: m_pNext(NULL)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CListItem::~CListItem()
{
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	rList	The list to iterate.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CListIter::CListIter(const CList& rList)
	: m_pNext(rList.m_pHead)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CListIter::~CListIter()
{
}
