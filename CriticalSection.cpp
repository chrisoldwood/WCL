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

/******************************************************************************
** Method:		Aquire()
**
** Description:	Attempt to aquire the critical section.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCriticalSection::Aquire()
{
	::EnterCriticalSection(&m_oLock);
}

/******************************************************************************
** Method:		Release()
**
** Description:	Release the critical section.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCriticalSection::Release()
{
	::LeaveCriticalSection(&m_oLock);
}
