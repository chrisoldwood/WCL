/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BUSYCURSOR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CBusyCursor class definition.
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

CBusyCursor::CBusyCursor()
{
	// Save old cursor.
	m_hOldCursor = ::GetCursor();

	// Show hourglass.
	Restore();
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

CBusyCursor::~CBusyCursor()
{
	// Restore old cursor.
	::SetCursor(m_hOldCursor);
}

/******************************************************************************
** Method:		Restore()
**
** Description:	Restores the hourglass cursor.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBusyCursor::Restore()
{
	// Restore old cursor.
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
}
