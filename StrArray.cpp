/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRARRAY.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CStrArray class definition.
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

CStrArray::CStrArray()
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

CStrArray::~CStrArray()
{
	// Delete the collection.
	for (int i = 0; i < Size(); i++)
		delete &Item(i);
}

/******************************************************************************
** Method:		Find()
**
** Description:	Attempts to find a string in the array.
**
** Parameters:	pszString		The string to find.
**				bIgnoreCase		Case insensitive flag.
**
** Returns:		The index of the string or -1 if not found.
**
*******************************************************************************
*/

int CStrArray::Find(const char* pszString, bool bIgnoreCase) const
{
	ASSERT(pszString != NULL);

	for (int i = 0; i < Size(); i++)
	{
		if (Item(i).Compare(pszString, bIgnoreCase) == 0)
			return i;
	}

	return -1;
}
