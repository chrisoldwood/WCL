/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		HANDLEMAP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CHandleMap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef HANDLEMAP_HPP
#define HANDLEMAP_HPP

/******************************************************************************
** 
** This is the base class used for items stored in a handle map collection.
**
*******************************************************************************
*/

class CHandleMapItem : public CMapItem
{
public:
	//
	// Constructors/Destructor.
	//
	CHandleMapItem(HANDLE hHandle, void* pObject);
	virtual ~CHandleMapItem();

	//
	// Methods.
	//
	virtual uint Key() const;
	virtual bool operator==(const CMapItem& rRHS) const;

	//
	// Members.
	//
	HANDLE	m_hHandle;
	void*	m_pObject;
};

/******************************************************************************
** 
** This is the map used to link generic handles to objects.
**
*******************************************************************************
*/

class CHandleMap : public CMap
{
public:
	//
	// Constructors/Destructor.
	//
	CHandleMap(int iSize);
	~CHandleMap();

	//
	// Methods.
	//
	void  Add(HANDLE hHandle, void* pObject);
	void  Remove(HANDLE hHandle);
	void* Find(HANDLE hHandle) const;

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CHandleMap::CHandleMap(int iSize)
	: CMap(iSize)
{
}

inline CHandleMap::~CHandleMap()
{
}

inline void CHandleMap::Add(HANDLE hHandle, void* pObject)
{
	ASSERT(hHandle != NULL);

	CMap::Add(*(new CHandleMapItem(hHandle, pObject)));
}

inline void CHandleMap::Remove(HANDLE hHandle)
{
	ASSERT(hHandle != NULL);

	CMap::Remove(CHandleMapItem(hHandle, NULL));
}

inline void* CHandleMap::Find(HANDLE hHandle) const
{
	ASSERT(hHandle);

	CHandleMapItem* pItem = (CHandleMapItem*) CMap::Find(CHandleMapItem(hHandle, NULL));

	return (pItem != NULL) ? pItem->m_pObject : NULL;
}

inline CHandleMapItem::CHandleMapItem(HANDLE hHandle, void* pObject)
	: m_hHandle(hHandle)
	, m_pObject(pObject)
{
}

inline CHandleMapItem::~CHandleMapItem()
{
}

inline uint CHandleMapItem::Key() const
{
	return (uint)m_hHandle;
}

inline bool CHandleMapItem::operator==(const CMapItem& rRHS) const
{
	CHandleMapItem* pRHS = (CHandleMapItem*) &rRHS;

	return (m_hHandle == pRHS->m_hHandle);
}

#endif //HANDLEMAP_HPP
