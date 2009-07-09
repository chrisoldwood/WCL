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

#if _MSC_VER > 1000
#pragma once
#endif

#include "CriticalSection.hpp"
#include "ThreadJob.hpp"
#include <vector>

// Forward declarations.
class ThreadPoolThread;

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
	CThreadPool(size_t nThreads);
	~CThreadPool();

	//
	// Control Methods.
	//
	void Start();
	void Stop();

	//
	// Job Methods.
	//
	void AddJob(ThreadJobPtr& pJob);
	void CancelJob(ThreadJobPtr& pJob);
	void CancelAllJobs();

	void ClearCompletedJobs();
	void DeleteCompletedJobs();

	//
	// Queue accessors.
	//
	size_t PendingJobCount() const;
	size_t RunningJobCount() const;
	size_t CompletedJobCount() const;

protected:
	// Template shorthands.
	typedef Core::SharedPtr<ThreadPoolThread> ThreadPoolThreadPtr;
	typedef std::vector<ThreadPoolThreadPtr> CThreads;
	typedef std::vector<ThreadJobPtr> CJobQueue;

	// Thread pool status.
	enum Status
	{
		STOPPED,
		RUNNING,
	};

	//
	// Members.
	//
	size_t				m_nThreads;
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
	void OnJobCompleted(ThreadJobPtr& pJob);

	// Friends.
	friend class ThreadPoolThread;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline size_t CThreadPool::PendingJobCount() const
{
	return m_oPendingQ.size();
}

inline size_t CThreadPool::RunningJobCount() const
{
	return m_oRunningQ.size();
}

inline size_t CThreadPool::CompletedJobCount() const
{
	return m_oCompletedQ.size();
}

#endif // THREADPOOL_HPP
