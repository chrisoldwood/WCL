/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CRITICALSECTION.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CCriticalSection class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "CriticalSection.hpp"

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
	: m_oLock()
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
** Method:		Acquire()
**
** Description:	Attempt to acquire the critical section.
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
