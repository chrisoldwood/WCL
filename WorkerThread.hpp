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

// Forward declarations.
class CThreadPool;

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
	CWorkerThread(CThreadPool& oPool);
	~CWorkerThread();

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
	CThreadPool&	m_oPool;
	ThreadStatus	m_eStatus;
	CEvent			m_oSyncEvent;
	CThreadJob*		m_pJob;

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
