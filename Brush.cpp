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
