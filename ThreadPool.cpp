/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		THREADPOOL.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CThreadPool class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	nThreads	The number of threads in the pool.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CThreadPool::CThreadPool(int nThreads)
	: m_nThreads(nThreads)
{
	ASSERT(m_nThreads > 0);
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

CThreadPool::~CThreadPool()
{
	// Free thread pool.
	m_oPool.DeleteAll();
}

/******************************************************************************
** Method:		Start()
**
** Description:	Start the thread pool running.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CThreadPool::Start()
{
	ASSERT(m_oPool.Size() == 0);

	// Create the thread pool.
	for (int i = 0; i < m_nThreads; ++i)
		m_oPool.Add(new CWorkerThread);

	// Start the pool threads.
	for (i = 0; i < m_nThreads; ++i)
		m_oPool[i]->Start();

	// Wait for the threads to become idle.
}

/******************************************************************************
** Method:		Stop()
**
** Description:	Stop the thread pool running.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CThreadPool::Stop()
{
	ASSERT(m_oPool.Size() != 0);

	// Stop the pool threads.
	for (int i = 0; i < m_nThreads; ++i)
		m_oPool[i]->Stop();

	// Wait for the threads to die.
}

/******************************************************************************
** Method:		AddJob()
**
** Description:	Add a new job to be run in the pool.
**
** Parameters:	pJob	The job to add.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CThreadPool::AddJob(CThreadJob* pJob)
{
	ASSERT(pJob != NULL);

	// Add to the pending queue.
	m_oPendingQ.Add(pJob);

	// Try and run it.
	ScheduleJob();
}

/******************************************************************************
** Method:		CancelJob()
**
** Description:	Cancel the specified job.
**
** Parameters:	pJob	The job to cancel.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CThreadPool::CancelJob(CThreadJob* pJob)
{
	ASSERT(pJob != NULL);
}

/******************************************************************************
** Method:		CancelAllJobs()
**
** Description:	Cancel all jobs assigned to the pool.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CThreadPool::CancelAllJobs()
{
}

/******************************************************************************
** Method:		ScheduleJob()
**
** Description:	Try and assign the next pending job to an idle thread.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CThreadPool::ScheduleJob()
{
	// Pending queue empty?
	if (m_oPendingQ.Size() == 0)
		return;

	// Find an idle thread.
	for (int i = 0; i < m_nThreads; ++i)
	{
		CWorkerThread* pThread = m_oPool[i];

		// Found one?
		if (m_oPool[i]->Status() == CWorkerThread::IDLE)
		{
			// Get next job.
			CThreadJob* pJob = m_oPendingQ[0];

			// Assign to thread.
			pThread->RunJob(pJob);

			// Move from pending to running queue.
			m_oPendingQ.Remove(0);
			m_oRunningQ.Add(pJob);
			break;
		}
	}
}
