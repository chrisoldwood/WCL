/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TMAPITER.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The TMapIter class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TMAPITER_HPP
#define TMAPITER_HPP

/******************************************************************************
** 
** The template version of the map iterator.
**
*******************************************************************************
*/

template<class K, class V> class TMapIter : public CMapIter
{
public:
	//
	// Constructors/Destructor.
	//
	TMapIter(const TMap<K, V>& oMap);
	~TMapIter();
	
	//
	// Methods.
	//
	bool Next(K& Key, V& Value);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

template<class K, class V> inline TMapIter<K, V>::TMapIter(const TMap<K, V>& oMap)
	: CMapIter(oMap)
{
}

template<class K, class V> inline TMapIter<K, V>::~TMapIter()
{
}

template<class K, class V> inline bool TMapIter<K, V>::Next(K& Key, V& Value)
{
	TMapItem<K, V>* pItem = static_cast<TMapItem<K, V>*>(CMapIter::Next());

	if (pItem == NULL)
		return false;

	Key   = pItem->m_Key;
	Value = pItem->m_Value;

	return true;
}

#endif // TMAPITER_HPP
