/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MAP_HPP
#define MAP_HPP

/******************************************************************************
** 
** This is the base class used for items stored in a map collection.
**
*******************************************************************************
*/

class CMapItem
{
public:
	//
	// Constructors/Destructor.
	//
	CMapItem();
	virtual ~CMapItem();

	//
	// Methods.
	//
	virtual uint Key() const = 0;
	virtual bool operator==(const CMapItem& rRHS) const = 0;
	virtual bool operator!=(const CMapItem& rRHS) const;

	//
	// Members.
	//
	CMapItem*	m_pNext;	// The next item in the collision chain.
};

/******************************************************************************
** 
** The is the base class for all map collections.
**
*******************************************************************************
*/

class CMap
{
public:
	//
	// Methods.
	//
	void RemoveAll();

protected:
	//
	// Constructors/Destructor.
	//
	CMap(int iSize);
	~CMap();
	
	//
	// External methods.
	//
	void      Add(CMapItem& rItem);
	void      Remove(const CMapItem& rItem);
	CMapItem* Find(const CMapItem& rItem) const;

	//
	// Internal methods.
	//
	virtual int Hash(const CMapItem& rItem) const;

	//
	// Members.
	//
	int			m_iSize;	// The size of the map.
	CMapItem**	m_pMap;		// The array of map buckets.
	int			m_iCount;	// The number of items in the map.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline bool CMapItem::operator!=(const CMapItem& rRHS) const
{
	return !(*this == rRHS);
}

#endif //MAP_HPP
