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
	, m_eStatus(STOPPED)
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
	ASSERT(m_eStatus == STOPPED);
	ASSERT(m_oPendingQ.Size()   == 0);
	ASSERT(m_oRunningQ.Size()   == 0);
	ASSERT(m_oCompletedQ.Size() == 0);

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
	ASSERT(m_eStatus == STOPPED);

	// Create the thread pool.
	for (int i = 0; i < m_nThreads; ++i)
		m_oPool.Add(new CWorkerThread(*this));

	// Start the pool threads.
	for (i = 0; i < m_nThreads; ++i)
		m_oPool[i]->Start();

	m_eStatus = RUNNING;
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
	ASSERT(m_eStatus == RUNNING);

	// Stop the pool threads.
	for (int i = 0; i < m_nThreads; ++i)
		m_oPool[i]->Stop();

	m_eStatus = STOPPED;
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
	ASSERT(m_eStatus == RUNNING);

	// Lock queues.
	CAutoThreadLock oAutoLock(m_oLock);

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
	ASSERT(m_eStatus == RUNNING);

	// Lock queues.
	CAutoThreadLock oAutoLock(m_oLock);

	int i = m_oPendingQ.Find(pJob);

	// If pending, move to completed queue.
	// NB: If running, leave it to complete.
	if (i != -1)
	{
		ASSERT(pJob->Status() == CThreadJob::PENDING);

		pJob->Status(CThreadJob::CANCELLED);

		m_oPendingQ.Remove(i);
		m_oCompletedQ.Add(pJob);
	}
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
	ASSERT(m_eStatus == RUNNING);

	// Lock queues.
	CAutoThreadLock oAutoLock(m_oLock);

	// Move all pending jobs to completed queue.
	// NB: Leave all running jobs to complete.
	for (int i = 0; i < m_oPendingQ.Size(); ++i)
	{
		CThreadJob* pJob = m_oPendingQ[i];

		pJob->Status(CThreadJob::CANCELLED);

		m_oCompletedQ.Add(pJob);
	}

	m_oPendingQ.RemoveAll();
}

/******************************************************************************
** Method:		ClearCompletedJobs()
**
** Description:	Remove all jobs from the completed job queue.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CThreadPool::ClearCompletedJobs()
{
	m_oCompletedQ.RemoveAll();
}

/******************************************************************************
** Method:		ClearCompletedJobs()
**
** Description:	Delete all jobs in the completed job queue.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CThreadPool::DeleteCompletedJobs()
{
	m_oCompletedQ.DeleteAll();
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
	ASSERT(m_eStatus == RUNNING);

	// Lock queues.
	CAutoThreadLock oAutoLock(m_oLock);

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

/******************************************************************************
** Method:		OnJobCompleted()
**
** Description:	Notification method that a worker thread has finished its job.
**
** Parameters:	pJob	The job completed.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CThreadPool::OnJobCompleted(CThreadJob* pJob)
{
	ASSERT(pJob != NULL);
	ASSERT(pJob->Status() == CThreadJob::COMPLETED);
	ASSERT(m_eStatus == RUNNING);

	// Lock queues.
	CAutoThreadLock oAutoLock(m_oLock);

	// Move from running to completed queue.
	int i = m_oRunningQ.Find(pJob);

	m_oRunningQ.Remove(i);
	m_oCompletedQ.Add(pJob);

	// Try and run another.
	ScheduleJob();
}
