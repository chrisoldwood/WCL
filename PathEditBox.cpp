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

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Character filter.
static const char* pszFilter = " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_~.\\:";

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
	Filter(pszFilter);
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
