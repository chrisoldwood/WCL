/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		THREAD.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CThread class definition.
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

CThread::CThread()
	: m_hHandle(NULL)
	, m_dwID(NULL)
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

CThread::~CThread()
{
}
