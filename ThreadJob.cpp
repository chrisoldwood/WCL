/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		THREADJOB.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CThreadJob class definition.
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
