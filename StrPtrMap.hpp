/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRPTRMAP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CStrPtrMap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STRPTRMAP_HPP
#define STRPTRMAP_HPP

/******************************************************************************
** 
** This is the base class used for items stored in a str->ptr map collection.
**
*******************************************************************************
*/

class CStrPtrMapItem : public CMapItem
{
public:
	//
	// Constructors/Destructor.
	//
	CStrPtrMapItem(const CString& strKey, void* pObject);
	virtual ~CStrPtrMapItem();

	//
	// Methods.
	//
	virtual uint Key() const;
	virtual bool operator==(const CMapItem& rRHS) const;

	//
	// Members.
	//
	CString	m_strKey;
	void*	m_pObject;
};

/******************************************************************************
** 
** This is the map used to link strings to objects.
**
*******************************************************************************
*/

class CStrPtrMap : public CMap
{
public:
	//
	// Constructors/Destructor.
	//
	CStrPtrMap(int iSize);
	~CStrPtrMap();

	//
	// Methods.
	//
	void  Add(const CString& strKey, void* pObject);
	void  Remove(const CString& strKey);
	void* Find(const CString& strKey) const;

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

inline CStrPtrMap::CStrPtrMap(int iSize)
	: CMap(iSize)
{
}

inline CStrPtrMap::~CStrPtrMap()
{
}

inline void CStrPtrMap::Add(const CString& strKey, void* pObject)
{
	ASSERT(strKey != NULL);

	CMap::Add(*(new CStrPtrMapItem(strKey, pObject)));
}

inline void CStrPtrMap::Remove(const CString& strKey)
{
	ASSERT(strKey != NULL);

	CMap::Remove(CStrPtrMapItem(strKey, NULL));
}

inline void* CStrPtrMap::Find(const CString& strKey) const
{
	ASSERT(strKey);

	CStrPtrMapItem* pItem = (CStrPtrMapItem*) CMap::Find(CStrPtrMapItem(strKey, NULL));

	return (pItem != NULL) ? pItem->m_pObject : NULL;
}

inline CStrPtrMapItem::CStrPtrMapItem(const CString& strKey, void* pObject)
	: m_strKey(strKey)
	, m_pObject(pObject)
{
}

inline CStrPtrMapItem::~CStrPtrMapItem()
{
}

inline uint CStrPtrMapItem::Key() const
{
	ASSERT(false);

	uint nKey = 0;

	for (const char* psz = m_strKey; *psz != '\0'; psz++)
		nKey = (nKey << 1) ^ *psz;

	return nKey;
}

inline bool CStrPtrMapItem::operator==(const CMapItem& rRHS) const
{
	CStrPtrMapItem* pRHS = (CStrPtrMapItem*) &rRHS;

	return (m_strKey == pRHS->m_strKey);
}

#endif //STRPTRMAP_HPP
