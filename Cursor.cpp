/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CURSOR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCursor class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Cursor.hpp"
#include "Module.hpp"

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
		::DestroyCursor(m_hCursor);
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads the cursor from the resource file.
**
** Parameters:	iRscID		The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCursor::LoadRsc(uint nRscID)
{
	ASSERT(m_hCursor == NULL);

	m_hCursor = ::LoadCursor(CModule::This().Handle(), MAKEINTRESOURCE(nRscID));
	m_bOwner  = false;

	ASSERT(m_hCursor != NULL);
}
