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

	//
	// Queue accessors.
	//
	int NumPendingJobs() const;
	int NumRunningJobs() const;
	int NumCompletedJobs() const;

protected:
	// Template shorthands.
	typedef TPtrArray<CWorkerThread> CThreads;
	typedef TPtrArray<CThreadJob> CJobQueue;

	//
	// Members.
	//
	int			m_nThreads;
	CThreads	m_oPool;
	CJobQueue	m_oPendingQ;
	CJobQueue	m_oRunningQ;
	CJobQueue	m_oCompletedQ;

	//
	// Internal methods.
	//
	void ScheduleJob();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline int CThreadPool::NumPendingJobs() const
{
	return m_oPendingQ.Size();
}

inline int CThreadPool::NumRunningJobs() const
{
	return m_oRunningQ.Size();
}

inline int CThreadPool::NumCompletedJobs() const
{
	return m_oCompletedQ.Size();
}

#endif // THREADPOOL_HPP
