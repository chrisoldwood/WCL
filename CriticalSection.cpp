/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CRITICALSECTION.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CCriticalSection class definition.
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

CCriticalSection::CCriticalSection()
{
	::InitializeCriticalSection(&m_oLock);
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

CCriticalSection::~CCriticalSection()
{
	::DeleteCriticalSection(&m_oLock);
}
