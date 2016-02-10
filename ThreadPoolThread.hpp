/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		THREADPOOLTHREAD.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The ThreadPoolThread class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef THREADPOOLTHREAD_HPP
#define THREADPOOLTHREAD_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "MsgThread.hpp"
#include "Event.hpp"
#include "ThreadJob.hpp"

// Forward declarations.
class CThreadPool;

/******************************************************************************
**
** A worker thread in a thread pool.
**
*******************************************************************************
*/

class ThreadPoolThread : public CMsgThread
{
public:
	//
	// Constructors/Destructor.
	//
	ThreadPoolThread(CThreadPool& oPool, size_t nPoolID);
	virtual	~ThreadPoolThread();

	// Thread status.
	enum ThreadStatus
	{
		STOPPED,
		IDLE,
		RUNNING,
	};

	//
	// Accessors.
	//
	ThreadStatus Status() const;

	//
	// Methods.
	//
	void Start();
	void RunJob(ThreadJobPtr& pJob);
	void Stop();

protected:
	//
	// Members.
	//
	CThreadPool&	m_oPool;		// The owning thread pool.
	size_t			m_nPoolID;		// The ID within the pool.
	ThreadStatus	m_eStatus;		// Current status.
	CEvent			m_oSyncEvent;	// Start/Stop event object.
	ThreadJobPtr	m_pJob;			// Current job, if one.

	// Thread messages.
	enum ThreadMsg
	{
		START_THREAD	= WM_USER+1,
		RUN_JOB			= WM_USER+2,
		STOP_THREAD		= WM_USER+3,
	};

	//
	// Message handlers.
	//
	virtual void OnThreadMsg(UINT nMsg, WPARAM wParam, LPARAM lParam);

	void OnStartThread();
	void OnRunJob();
	void OnStopThread();

	// Initial thread function.
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline ThreadPoolThread::ThreadStatus ThreadPoolThread::Status() const
{
	return m_eStatus;
}

#endif // THREADPOOLTHREAD_HPP
