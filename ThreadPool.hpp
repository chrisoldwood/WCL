/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		THREADPOOL.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CThreadPool class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

/******************************************************************************
** 
** A pool of worker threads which run thread jobs.
**
*******************************************************************************
*/

class CThreadPool
{
public:
	//
	// Constructors/Destructor.
	//
	CThreadPool(int nThreads);
	~CThreadPool();

	//
	// Control Methods.
	//
	void Start();
	void Stop();

	//
	// Job Methods.
	//
	void AddJob(CThreadJob* pJob);
	void CancelJob(CThreadJob* pJob);
	void CancelAllJobs();

	void ClearCompletedJobs();
	void DeleteCompletedJobs();

	//
	// Queue accessors.
	//
	int PendingJobCount() const;
	int RunningJobCount() const;
	int CompletedJobCount() const;

protected:
	// Template shorthands.
	typedef TPtrArray<CWorkerThread> CThreads;
	typedef TPtrArray<CThreadJob> CJobQueue;

	// Thread pool status.
	enum Status
	{
		STOPPED,
		RUNNING,
	};

	//
	// Members.
	//
	int					m_nThreads;
	Status				m_eStatus;
	CThreads			m_oPool;
	CJobQueue			m_oPendingQ;
	CJobQueue			m_oRunningQ;
	CJobQueue			m_oCompletedQ;
	CCriticalSection	m_oLock;

	//
	// Internal methods.
	//
	void ScheduleJob();
	void OnJobCompleted(CThreadJob* pJob);

	// Friends.
	friend class CWorkerThread;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline int CThreadPool::PendingJobCount() const
{
	return m_oPendingQ.Size();
}

inline int CThreadPool::RunningJobCount() const
{
	return m_oRunningQ.Size();
}

inline int CThreadPool::CompletedJobCount() const
{
	return m_oCompletedQ.Size();
}

#endif // THREADPOOL_HPP
