/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TMAP.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The TMap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TMAP_HPP
#define TMAP_HPP

/******************************************************************************
** 
** This is a template version of the CMap class.
**
*******************************************************************************
*/

template<class K, class V> class TMap : protected CMap
{
public:
	//
	// Constructors/Destructor.
	//
	TMap();
	~TMap();
	
	//
	// Methods.
	//
	int   Count() const;

	void  Add(K Key, V Value);
	void  Remove(K Key);
	void  RemoveAll();
	bool  Find(K Key, V& Value) const;

	void  Reserve(int nItems);
};

/******************************************************************************
** 
** This is the class used for items stored in the map.
**
*******************************************************************************
*/

template<class K, class V> class TMapItem : public CMapItem
{
public:
	//
	// Constructors/Destructor.
	//
	TMapItem(K Key);
	TMapItem(K Key, V Value);
	virtual ~TMapItem();

	//
	// Methods.
	//
	virtual uint Key() const;
	virtual bool operator==(const CMapItem& rRHS) const;

	//
	// Members.
	//
	K	m_Key;
	V	m_Value;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

template<class K, class V> inline TMap<K, V>::TMap()
{
}

template<class K, class V> inline TMap<K, V>::~TMap()
{
}

template<class K, class V> inline int TMap<K, V>::Count() const
{
	return CMap::Count();
}

template<class K, class V> inline void TMap<K, V>::Add(K Key, V Value)
{
	CMap::Add(*(new TMapItem<K, V>(Key, Value)));
}

template<class K, class V> inline void TMap<K, V>::Remove(K Key)
{
	CMap::Remove(TMapItem<K, V>(Key));
}

template<class K, class V> inline void TMap<K, V>::RemoveAll()
{
	CMap::RemoveAll();
}

template<class K, class V> inline bool TMap<K, V>::Find(K Key, V& Value) const
{
	TMapItem<K, V>* pItem = (TMapItem<K, V>*) CMap::Find(TMapItem<K, V>(Key));

	if (pItem != NULL)
		Value = pItem->m_Value;

	return (pItem != NULL);
}

template<class K, class V> inline void TMap<K, V>::Reserve(int nItems)
{
	CMap::Reserve(nItems);
}

template<class K, class V> inline TMapItem<K, V>::TMapItem(K Key)
	: m_Key(Key)
{
}

template<class K, class V> inline TMapItem<K, V>::TMapItem(K Key, V Value)
	: m_Key(Key)
	, m_Value(Value)
{
}

template<class K, class V> inline TMapItem<K, V>::~TMapItem()
{
}

template<class K, class V> inline uint TMapItem<K, V>::Key() const
{
	return (uint) m_Key;
}

template<class K, class V> inline bool TMapItem<K, V>::operator==(const CMapItem& rRHS) const
{
	TMapItem<K, V>* pRHS = (TMapItem<K, V>*) &rRHS;

	return (m_Key == pRHS->m_Key);
}

#endif // TMAP_HPP
