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
	CWorkerThread();
	~CWorkerThread();

	// Thread status.
	enum ThreadStatus
	{
		SUSPENDED,
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
	ThreadStatus	m_eStatus;
	CThreadJob*		m_pCurrentJob;
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
