/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ARRAY.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CArray class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	nItemSize	The size of an item.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CArray::CArray(int nItemSize)
	: m_pData(NULL)
	, m_nSize(0)
	, m_nAllocSize(0)
	, m_nItemSize(nItemSize)
{
	ASSERT(m_nItemSize > 0);
}

/******************************************************************************
** Method:		Copy constructor.
**
** Description:	Copies the other array.
**
** Parameters:	.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CArray::CArray(const CArray& rArray)
	: m_pData(NULL)
	, m_nSize(rArray.m_nSize)
	, m_nAllocSize(rArray.m_nAllocSize)
	, m_nItemSize(rArray.m_nItemSize)
{
	// Array not empty?
	if (rArray.m_pData != NULL)
	{
		// Calculate number of bytes to allocate.
		int nBytes = m_nAllocSize * m_nItemSize;

		// Allocate the array.
		m_pData = (byte*) realloc(m_pData, nBytes);

		// Copy the data.
		memcpy(m_pData, rArray.m_pData, nBytes);
	}
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

CArray::~CArray()
{
	RemoveAll();
}

/******************************************************************************
** Method:		Reserve()
**
** Description:	Reserve space for at least the number of items requested.
**
** Parameters:	nSize	The number of items to reserve space for.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CArray::Reserve(int nSize)
{
	// Buffer already big enough?
	if (nSize <= m_nAllocSize)
		return;

	// Round size to a multiple of 4.
	m_nAllocSize = (nSize + 3) & ~3;

	// Calculate number of bytes to allocate.
	int nBytes = m_nAllocSize * m_nItemSize;

	// Allocate it...
	m_pData = (byte*) realloc(m_pData, nBytes);
	ASSERT(m_pData);
}

/******************************************************************************
** Method:		Set()
**
** Description:	Sets an item in the array.
**
** Parameters:	nIndex	The item to set.
**				pItem	A pointer to the items value.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CArray::Set(int nIndex, const void* pItem)
{
	ASSERT((nIndex >= 0) && (nIndex <= m_nSize));

	// Calculate offset to the position.
	byte* pPos = m_pData + (nIndex * m_nItemSize);

	// Copy the new item into the array.
	memcpy(pPos, pItem, m_nItemSize);
}

/******************************************************************************
** Method:		Add()
**
** Description:	Appends an item to the array.
**
** Parameters:	pItem	A pointer to the item to add.
**
** Returns:		The position where the item was added.
**
*******************************************************************************
*/

int CArray::Add(const void* pItem)
{
	// Increase buffer by 1.
	Reserve(m_nSize+1);

	// Calculate offset of end of array.
	byte* pPos = m_pData + (m_nSize * m_nItemSize);

	// Copy the item.
	memcpy(pPos, pItem, m_nItemSize);

	return m_nSize++;
}

/******************************************************************************
** Method:		Insert()
**
** Description:	Inserts an item into the array.
**
** Parameters:	nIndex	The index where to insert at.
**				pItem	A pointer to the item to insert.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CArray::Insert(int nIndex, const void* pItem)
{
	ASSERT((nIndex >= 0) && (nIndex <= m_nSize));

	// Increase buffer by 1.
	Reserve(m_nSize+1);

	// Calculate offset to insert position.
	byte* pPos = m_pData + (nIndex * m_nItemSize);

	// Calculate the size of bytes to move up.
	int nBytes = (m_nSize - nIndex) * m_nItemSize;

	// Move all existing items up one.
	memmove(pPos + m_nItemSize, pPos, nBytes);

	// Copy the new item into the array.
	memcpy(pPos, pItem, m_nItemSize);

	m_nSize++;
}

/******************************************************************************
** Method:		Remove()
**
** Description:	Removes an item from the array.
**
** Parameters:	nIndex	The index of the item to remove.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CArray::Remove(int nIndex)
{
	ASSERT((nIndex >= 0) && (nIndex < m_nSize));

	// Calculate offset to the item.
	byte* pPos = m_pData + (nIndex * m_nItemSize);

	// Calculate the size of bytes to move down.
	int nBytes = (m_nSize - nIndex - 1) * m_nItemSize;

	// Move all existing items down one.
	memmove(pPos, pPos + m_nItemSize, nBytes);

	m_nSize--;
}

/******************************************************************************
** Method:		RemoveAll()
**
** Description:	Free up resources.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CArray::RemoveAll()
{
	// Free the array buffer.
	if (m_pData != NULL)
	{
		free(m_pData);
		m_pData = NULL;
	}

	// Reset size members.
	m_nSize      = 0;
	m_nAllocSize = 0;
}
