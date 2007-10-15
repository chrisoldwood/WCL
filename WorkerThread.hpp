/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WORKERTHREAD.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CWorkerThread class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WORKERTHREAD_HPP
#define WORKERTHREAD_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "MsgThread.hpp"
#include "Event.hpp"

// Forward declarations.
class CThreadPool;
class CThreadJob;

/******************************************************************************
** 
** A worker thread in a thread pool.
**
*******************************************************************************
*/

class CWorkerThread : public CMsgThread
{
public:
	//
	// Constructors/Destructor.
	//
	CWorkerThread(CThreadPool& oPool, uint nPoolID);
	virtual	~CWorkerThread();

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
	void RunJob(CThreadJob* pJob);
	void Stop();

protected:
	//
	// Members.
	//
	CThreadPool&	m_oPool;		// The owning thread pool.
	uint			m_nPoolID;		// The ID within the pool.
	ThreadStatus	m_eStatus;		// Current status.
	CEvent			m_oSyncEvent;	// Start/Stop event object.
	CThreadJob*		m_pJob;			// Current job, if one.

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

	// Inital thread function.
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CWorkerThread::ThreadStatus CWorkerThread::Status() const
{
	return m_eStatus;
}

#endif // WORKERTHREAD_HPP
