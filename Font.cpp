/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FONT.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CFont class definition.
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

CFont::CFont()
	: m_hFont(NULL)
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

CFont::~CFont()
{
	// Delete if valid and we own it.
	if ( (m_hFont) && (m_bOwner) )
		::DeleteObject(m_hFont);
}
