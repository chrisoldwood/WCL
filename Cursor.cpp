/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CURSOR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCursor class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

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

CCursor::CCursor()
	: m_hCursor(NULL)
	, m_bOwner(false)
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

CCursor::~CCursor()
{
	// Delete if valid and we own it.
	if ( (m_hCursor) && (m_bOwner) )
		::DeleteObject(m_hCursor);
}
