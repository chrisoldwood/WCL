/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PEN.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPen class definition.
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

CPen::CPen()
	: m_hPen(NULL)
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

CPen::~CPen()
{
	// Delete if valid and we own it.
	if ( (m_hPen) && (m_bOwner) )
		::DeleteObject(m_hPen);
}
