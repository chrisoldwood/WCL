/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BRUSH.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CBrush class definition.
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

CBrush::CBrush()
	: m_hBrush(NULL)
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

CBrush::~CBrush()
{
	// Delete if valid and we own it.
	if ( (m_hBrush) && (m_bOwner) )
		::DeleteObject(m_hBrush);
}
