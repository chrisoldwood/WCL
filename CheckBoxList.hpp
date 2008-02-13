/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CHECKBOXLIST.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CCheckBoxList class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CHECKBOXLIST_HPP
#define CHECKBOXLIST_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "ListView.hpp"

/******************************************************************************
** 
** This is a ListView derived class used to display a list of check boxes.
**
*******************************************************************************
*/

class CCheckBoxList : public CListView
{
public:
	//
	// Constructors/Destructor.
	//
	CCheckBoxList();
	~CCheckBoxList();
	
	//
	// Methods.
	//
	void ItemCheck(size_t nItem, bool bChecked);
	bool IsItemChecked(size_t nItem);

protected:
	//
	// Members.
	//

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CCheckBoxList::ItemCheck(size_t nItem, bool bChecked)
{
	uint nState = INDEXTOSTATEIMAGEMASK((bChecked ? 2 : 1));

	ListView_SetItemState(m_hWnd, nItem, nState, LVIS_STATEIMAGEMASK);
}

inline bool CCheckBoxList::IsItemChecked(size_t nItem)
{
	return ListView_GetCheckState(m_hWnd, nItem);
}

#endif //CHECKBOXLIST_HPP
