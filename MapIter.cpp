/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAPITER.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CMapIter class definition.
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

CMapIter::CMapIter(const CMap& oMap)
	: m_oMap(oMap)
	, m_nBucket(-1)
	, m_pCurrent(NULL)
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

CMapIter::~CMapIter()
{
}

/******************************************************************************
** Method:		Next()
**
** Description:	Get the next item from the map.
**
** Parameters:	None.
**
** Returns:		The next item or NULL.
**
*******************************************************************************
*/

CMapItem* CMapIter::Next()
{
	// Map empty?
	if (m_oMap.m_pMap == NULL)
		return NULL;

	// Traversing bucket chain?
	if ( (m_pCurrent != NULL) && (m_pCurrent->m_pNext != NULL) )
	{
		m_pCurrent = m_pCurrent->m_pNext;

		return m_pCurrent;
	}

	m_nBucket++;

	// Try next bucket.
	while (m_nBucket < m_oMap.m_iSize)
	{
		m_pCurrent = m_oMap.m_pMap[m_nBucket];

		if (m_pCurrent != NULL)
			return m_pCurrent;

		m_nBucket++;
	}

	return NULL;
}
