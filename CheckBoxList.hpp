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
	void ItemCheck(int nItem, bool bChecked);
	bool IsItemChecked(int nItem);

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

inline void CCheckBoxList::ItemCheck(int nItem, bool bChecked)
{
	int nState = INDEXTOSTATEIMAGEMASK((bChecked ? 2 : 1));

	ListView_SetItemState(m_hWnd, nItem, nState, LVIS_STATEIMAGEMASK);
}

inline bool CCheckBoxList::IsItemChecked(int nItem)
{
	return ListView_GetCheckState(m_hWnd, nItem);
}

#endif //CHECKBOXLIST_HPP
