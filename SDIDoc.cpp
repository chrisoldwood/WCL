/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDIDOC.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CSDIDoc class definition.
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
