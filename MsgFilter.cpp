/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MSGFILTER.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMsgFilter & CMsgFilters class definitions.
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

CMsgFilter::CMsgFilter()
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

CMsgFilter::~CMsgFilter()
{
}

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

CMsgFilters::CMsgFilters()
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

CMsgFilters::~CMsgFilters()
{
}

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

CMsgFilters::CIter::CIter(const CMsgFilters& rList)
	: CPtrListIter(rList)
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

CMsgFilters::CIter::~CIter()
{
}
