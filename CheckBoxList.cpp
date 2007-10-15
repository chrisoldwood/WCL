/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CHECKBOXLIST.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCheckBoxList class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "CheckBoxList.hpp"

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
