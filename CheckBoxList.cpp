/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CHECKBOXLIST.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCheckBoxList class definition.
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

CCheckBoxList::CCheckBoxList()
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

CCheckBoxList::~CCheckBoxList()
{
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Sets the check box mode of the listview.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCheckBoxList::OnCreate(const CRect& rcClient)
{
	CheckBoxes(true);

	CListView::OnCreate(rcClient);
}
