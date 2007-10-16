/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDIDOC.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CSDIDoc class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "SDIDoc.hpp"

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

CSDIDoc::CSDIDoc()
	: m_pView(NULL)
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

CSDIDoc::~CSDIDoc()
{
	ASSERT(m_pView == NULL);
}
