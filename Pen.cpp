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
	if (m_hPen)
		::DeleteObject(m_hPen);
}
