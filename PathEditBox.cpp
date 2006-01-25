/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PATHEDITBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPathEditBox class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Character filter (invalid characters in a path).
static const char* pszFilter = "*?\"<>|";

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

CPathEditBox::CPathEditBox() : CEditBox()
{
	// Setup character filter.
	SetFilterDefault(true);
	Filter(pszFilter, false);
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

CPathEditBox::~CPathEditBox()
{
}
