/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMap class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	iSize	The size of the map.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMap::CMap(int iSize)
	: m_iSize(iSize)
	, m_pMap(NULL)
	, m_iCount(0)
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

CMap::~CMap()
{
	RemoveAll();

	ASSERT(m_iCount == 0);
	ASSERT(m_pMap   == NULL);
}

/******************************************************************************
** Method:		Add()
**
** Description:	Adds an item to the map.
**
** Parameters:	rItem	The item to add.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMap::Add(CMapItem& rItem)
{
	// Map allocated?
	if (m_iCount == 0)
		m_pMap = (CMapItem**) calloc(m_iSize, sizeof(CMapItem*));
	
	ASSERT(m_pMap);

	// Calculate map bucket.
	int i = Hash(rItem);
	
	ASSERT((i >= 0) && (i < m_iSize));

	// Add to head of collision chain.
	rItem.m_pNext = m_pMap[i];
	m_pMap[i] = &rItem;

	m_iCount++;
}

/******************************************************************************
** Method:		Remove()
**
** Description:	Removes an item from the map.
**
** Parameters:	rItem	The item to remove.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMap::Remove(const CMapItem& rItem)
{
	ASSERT(m_pMap);
	ASSERT(m_iCount);

	// Calculate map bucket.
	int i = Hash(rItem);
	
	ASSERT((i >= 0) && (i < m_iSize));
	
	// Get head of collision chain.
	CMapItem*  pItem  = m_pMap[i];
	CMapItem** ppPrev = &m_pMap[i];

	// Find item.
	while ( (pItem) && (rItem != *pItem) )
	{
		ppPrev = &pItem->m_pNext;
		pItem  = pItem->m_pNext;
	}

	ASSERT(pItem);

	// Remove.
	*ppPrev = pItem->m_pNext;
	delete pItem;

	// Map now empty?
	if (--m_iCount == 0)
	{
		free(m_pMap);
		m_pMap = NULL;
	}
}

/******************************************************************************
** Method:		RemoveAll()
**
** Description:	Removes all items from the map.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMap::RemoveAll()
{
	// Map not already empty?
	if (m_iCount != 0)
	{
		// For all buckets.
		for (int i = 0; i < m_iSize; i++)
		{
			CMapItem* pItem = m_pMap[i];

			// Run down the chain.
			while (pItem != NULL)
			{
				CMapItem* pNextItem = pItem->m_pNext;
				
				delete pItem;
				m_iCount--;

				pItem = pNextItem;
			}
		}

		free(m_pMap);
		m_pMap = NULL;
	}
}

/******************************************************************************
** Method:		Find()
**
** Description:	Finds an item in the map.
**
** Parameters:	rItem	The item to find.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMapItem* CMap::Find(const CMapItem& rItem) const
{
	ASSERT(m_pMap);
	ASSERT(m_iCount);

	// Calculate map bucket.
	int i = Hash(rItem);
	
	ASSERT((i >= 0) && (i < m_iSize));

	// Get head of collision chain.
	CMapItem* pItem = m_pMap[i];

	// Find item.
	while ( (pItem) && (rItem != *pItem) )
		pItem = pItem->m_pNext;

	return pItem;
}

/******************************************************************************
** Method:		Hash()
**
** Description:	Calculates the collision bucket for the given item.
**
** Parameters:	rItem	The item to hash.
**
** Returns:		The bucket array index.
**
*******************************************************************************
*/

int CMap::Hash(const CMapItem& rItem) const
{
	return (rItem.Key() % m_iSize);
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

CMapItem::CMapItem()
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

CMapItem::~CMapItem()
{
}
