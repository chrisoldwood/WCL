/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WORKERTHREAD.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CWorkerThread class definition.
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
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CWorkerThread::CWorkerThread(CThreadPool& oPool)
	: m_oPool(oPool)
	, m_eStatus(STOPPED)
	, m_oSyncEvent(true, false)
	, m_pJob(NULL)
{
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

CWorkerThread::~CWorkerThread()
{
	ASSERT(m_eStatus == STOPPED);

	::CloseHandle(m_hThread);
}

/******************************************************************************
** Method:		ThreadFunction()
**
** Description:	The inital function for the thread.
**
** Parameters:	lpParam		The CWorkerThread object.
**
** Returns:		0.
**
*******************************************************************************
*/

DWORD WINAPI CWorkerThread::ThreadFunction(LPVOID lpParam)
{
	CWorkerThread* pThread = reinterpret_cast<CWorkerThread*>(lpParam);

	// Force creation of a message queue.
	::PeekMessage(&pThread->m_oMsg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	// Signal calling thread that we're started.
	pThread->m_eStatus = IDLE;
	pThread->m_oSyncEvent.Signal();

	// Call the threads main function.
	pThread->Run();

	// Signal calling thread that we've stopped.
	pThread->m_eStatus = STOPPED;
	pThread->m_oSyncEvent.Signal();

	return 0;
}

/******************************************************************************
** Method:		Start()
**
** Description:	Start the underlying thread.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::Start()
{
	ASSERT(m_eStatus == STOPPED);

	// Create the thread.
	m_hThread = ::CreateThread(NULL, 0, ThreadFunction, this, 0, &m_dwID);

	ASSERT(m_hThread != NULL);

	// Wait until thread is actually running.
	m_oSyncEvent.Wait();
	m_oSyncEvent.Reset();

	// Signal to ready itself for jobs.
	PostMessage(START_THREAD);
}

/******************************************************************************
** Method:		Stop()
**
** Description:	Stop the underlying thread.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::Stop()
{
	ASSERT(m_eStatus == IDLE);

	// Signal to terminate itself.
	PostMessage(STOP_THREAD);

	// Wait until thread has stopped.
	m_oSyncEvent.Wait();
	m_oSyncEvent.Reset();
}

/******************************************************************************
** Method:		RunJob()
**
** Description:	Run the given job on the thread.
**
** Parameters:	pJob	The job to run.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::RunJob(CThreadJob* pJob)
{
	ASSERT(pJob != NULL);
	ASSERT(pJob->Status() == CThreadJob::PENDING);
	ASSERT(m_eStatus == IDLE);
	ASSERT(m_pJob == NULL);

	// Update job state.
	pJob->Status(CThreadJob::RUNNING);

	// Update thread state.
	m_eStatus = RUNNING;
	m_pJob    = pJob;

	// Signal to run job.
	PostMessage(RUN_JOB);
}

/******************************************************************************
** Method:		OnThreadMsg()
**
** Description:	Message handler for general thread messages.
**
** Parameters:	Standard thread message parameters.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::OnThreadMsg(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	switch(nMsg)
	{
		case START_THREAD:	OnStartThread();	break;
		case RUN_JOB:		OnRunJob();			break;
		case STOP_THREAD:	OnStopThread();		break;
		default:			ASSERT(false);		break;
	}
}

/******************************************************************************
** Method:		OnStartThread()
**
** Description:	Ready the thread for jobs.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::OnStartThread()
{
}

/******************************************************************************
** Method:		OnRunJob()
**
** Description:	Run the current job.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::OnRunJob()
{
	ASSERT(m_pJob != NULL);
	ASSERT(m_pJob->Status() == CThreadJob::RUNNING);

	// Get the job to run.
	CThreadJob* pJob = m_pJob;

	// Run it.
	pJob->Run();

	// Update job state.
	pJob->Status(CThreadJob::COMPLETED);

	// Update thread state.
	m_eStatus = IDLE;
	m_pJob    = NULL;

	// Notify thread pool.
	m_oPool.OnJobCompleted(pJob);
}

/******************************************************************************
** Method:		OnStopThread()
**
** Description:	Close down the thread.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWorkerThread::OnStopThread()
{
	::PostQuitMessage(0);
}
