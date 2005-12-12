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

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

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
	ASSERT(m_oPendingQ.empty());
	ASSERT(m_oRunningQ.empty());
	ASSERT(m_oCompletedQ.empty());

	// Template shorthands.
	typedef CThreads::const_iterator CIter;

	// Free thread pool.
	for (CIter oIter = m_oPool.begin(); oIter != m_oPool.end(); ++oIter)
		delete *oIter;

	m_oPool.clear();
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
	ASSERT(m_oPool.empty());
	ASSERT(m_eStatus == STOPPED);

	// Create the thread pool.
	for (int i = 0; i < m_nThreads; ++i)
		m_oPool.push_back(new CWorkerThread(*this, i));

	// Start the pool threads.
	for (int i = 0; i < m_nThreads; ++i)
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
	ASSERT(!m_oPool.empty());
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
	m_oPendingQ.push_back(pJob);

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

	// Template shorthands.
	typedef CJobQueue::iterator CIter;

	// Lock queues.
	CAutoThreadLock oAutoLock(m_oLock);

	// If pending, move to completed queue.
	// NB: If running, leave it to complete.
	CIter oIter = std::find(m_oPendingQ.begin(), m_oPendingQ.end(), pJob);

	if (oIter != m_oPendingQ.end())
	{
		ASSERT(pJob->Status() == CThreadJob::PENDING);

		pJob->Status(CThreadJob::CANCELLED);

		m_oCompletedQ.push_back(pJob);
		m_oPendingQ.erase(oIter);
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

	// Template shorthands.
	typedef CJobQueue::const_iterator CIter;

	// Lock queues.
	CAutoThreadLock oAutoLock(m_oLock);

	// Move all pending jobs to completed queue.
	// NB: Leave all running jobs to complete.
	for (CIter oIter = m_oPendingQ.begin(); oIter != m_oPendingQ.end(); ++oIter)
	{
		CThreadJob* pJob = *oIter;

		pJob->Status(CThreadJob::CANCELLED);

		m_oCompletedQ.push_back(pJob);
	}

	m_oPendingQ.clear();
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
	m_oCompletedQ.clear();
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
	// Template shorthands.
	typedef CJobQueue::const_iterator CIter;

	for (CIter oIter = m_oCompletedQ.begin(); oIter != m_oCompletedQ.end(); ++oIter)
		delete *oIter;

	m_oCompletedQ.clear();
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

	// Template shorthands.
	typedef CJobQueue::iterator CIter;

	// Lock queues.
	CAutoThreadLock oAutoLock(m_oLock);

	// Nothing to schedule?
	if (m_oPendingQ.empty())
		return;

	// Find an idle thread.
	for (int i = 0; i < m_nThreads; ++i)
	{
		CWorkerThread* pThread = m_oPool[i];

		// Found one?
		if (pThread->Status() == CWorkerThread::IDLE)
		{
			// Get next job.
			CIter       oIter = m_oPendingQ.begin();
			CThreadJob* pJob  = *oIter;

			// Assign to thread.
			pThread->RunJob(pJob);

			// Move from pending to running queue.
			m_oPendingQ.erase(oIter);
			m_oRunningQ.push_back(pJob);
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

	// Template shorthands.
	typedef CJobQueue::iterator CIter;

	// Lock queues.
	CAutoThreadLock oAutoLock(m_oLock);

	// Move from running to completed queue.
	CIter oIter = std::find(m_oRunningQ.begin(), m_oRunningQ.end(), pJob);
	
	ASSERT(oIter != m_oRunningQ.end());

	m_oCompletedQ.push_back(pJob);
	m_oRunningQ.erase(oIter);

	// Try and run another.
	ScheduleJob();
}
