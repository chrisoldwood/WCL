/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAINTHREAD.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CMainThread class definition.
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

CMainThread::CMainThread()
{
	m_hHandle = NULL;
	m_dwID    = ::GetCurrentThreadId();
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

CMainThread::~CMainThread()
{
}
