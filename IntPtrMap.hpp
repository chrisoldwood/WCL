/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		INTPTRMAP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CIntPtrMap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef INTPTRMAP_HPP
#define INTPTRMAP_HPP

/******************************************************************************
** 
** This is the base class used for items stored in an int->ptr map collection.
**
*******************************************************************************
*/

class CIntPtrMapItem : public CMapItem
{
public:
	//
	// Constructors/Destructor.
	//
	CIntPtrMapItem(int iKey, void* pObject);
	virtual ~CIntPtrMapItem();

	//
	// Methods.
	//
	virtual uint Key() const;
	virtual bool operator==(const CMapItem& rRHS) const;

	//
	// Members.
	//
	int		m_iKey;
	void*	m_pObject;
};

/******************************************************************************
** 
** This is the map used to link int values to objects.
**
*******************************************************************************
*/

class CIntPtrMap : public CMap
{
public:
	//
	// Constructors/Destructor.
	//
	CIntPtrMap(int iSize);
	~CIntPtrMap();

	//
	// Methods.
	//
	void  Add(int iKey, void* pObject);
	void  Remove(int iKey);
	void* Find(int iKey) const;

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

inline CIntPtrMap::CIntPtrMap(int iSize)
	: CMap(iSize)
{
}

inline CIntPtrMap::~CIntPtrMap()
{
}

inline void CIntPtrMap::Add(int iKey, void* pObject)
{
	CMap::Add(*(new CIntPtrMapItem(iKey, pObject)));
}

inline void CIntPtrMap::Remove(int iKey)
{
	CMap::Remove(CIntPtrMapItem(iKey, NULL));
}

inline void* CIntPtrMap::Find(int iKey) const
{
	CIntPtrMapItem* pItem = (CIntPtrMapItem*) CMap::Find(CIntPtrMapItem(iKey, NULL));

	return (pItem != NULL) ? pItem->m_pObject : NULL;
}

inline CIntPtrMapItem::CIntPtrMapItem(int iKey, void* pObject)
	: m_iKey(iKey)
	, m_pObject(pObject)
{
}

inline CIntPtrMapItem::~CIntPtrMapItem()
{
}

inline uint CIntPtrMapItem::Key() const
{
	return (uint)m_iKey;
}

inline bool CIntPtrMapItem::operator==(const CMapItem& rRHS) const
{
	CIntPtrMapItem* pRHS = (CIntPtrMapItem*) &rRHS;

	return (m_iKey == pRHS->m_iKey);
}

#endif //INTPTRMAP_HPP
