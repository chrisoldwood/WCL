/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PATHEDITBOX.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPathEditBox class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "PathEditBox.hpp"

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
