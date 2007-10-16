/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		THREADJOB.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CThreadJob class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ThreadJob.hpp"

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

CThreadJob::CThreadJob()
	: m_eStatus(PENDING)
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

CThreadJob::~CThreadJob()
{
}
