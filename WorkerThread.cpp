/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WORKERTHREAD.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CWorkerThread class definition.
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

CWorkerThread::CWorkerThread()
	: m_eStatus(SUSPENDED)
	, m_pCurrentJob(NULL)
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

CWorkerThread::~CWorkerThread()
{
}

/******************************************************************************
** Method:		Start()
**
** Description:	Start the underlying thread.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::Start()
{
}

/******************************************************************************
** Method:		Stop()
**
** Description:	Stop the underlying thread.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::Stop()
{
}

/******************************************************************************
** Method:		RunJob()
**
** Description:	Run the given job on the thread.
**
** Parameters:	pJob	The job to run.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::RunJob(CThreadJob* pJob)
{
	ASSERT(pJob != NULL);

	// Update state.
	m_eStatus     = RUNNING;
	m_pCurrentJob = pJob;

	// Signal to run job.
}
