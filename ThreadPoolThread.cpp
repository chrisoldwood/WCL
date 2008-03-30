/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WORKERTHREAD.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CWorkerThread class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "WorkerThread.hpp"
#include "ThreadPool.hpp"
#include "ThreadJob.hpp"
#include "SeTranslator.hpp"
#include "Exception.hpp"

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

CWorkerThread::CWorkerThread(CThreadPool& oPool, uint nPoolID)
	: m_oPool(oPool)
	, m_nPoolID(nPoolID)
	, m_eStatus(STOPPED)
	, m_oSyncEvent(true, false)
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
	// Translate structured exceptions.
	WCL::SeTranslator::Install();

	CWorkerThread* pThread = reinterpret_cast<CWorkerThread*>(lpParam);

	// Force creation of a message queue.
	::PeekMessage(&pThread->m_oMsg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	// Signal calling thread that we're started.
	pThread->m_eStatus = IDLE;
	pThread->m_oSyncEvent.Signal();

	try
	{
		// Call the threads main function.
		pThread->Run();
	}
	catch (const std::exception& e)
	{
		WCL::ReportUnhandledException(TXT("Unexpected exception caught in CWorkerThread::Run()\n\n%hs"), e.what());
	}
	catch (...)
	{
		WCL::ReportUnhandledException(TXT("Unexpected unknown exception caught in CWorkerThread::Run()"));
	}

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

void CWorkerThread::RunJob(ThreadJobPtr& pJob)
{
	ASSERT(pJob.Get() != nullptr);
	ASSERT(pJob->Status() == CThreadJob::PENDING);
	ASSERT(m_eStatus == IDLE);
	ASSERT(m_pJob.Get() == nullptr);

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

void CWorkerThread::OnThreadMsg(UINT nMsg, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	switch(nMsg)
	{
		case START_THREAD:	OnStartThread();	break;
		case RUN_JOB:		OnRunJob();			break;
		case STOP_THREAD:	OnStopThread();		break;
		default:			ASSERT_FALSE();		break;
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
	try
	{
		ASSERT(m_pJob.Get() != nullptr);
		ASSERT(m_pJob->Status() == CThreadJob::RUNNING);

		// Get the job to run.
		ThreadJobPtr pJob = m_pJob;

		// Run it.
		pJob->Run();

		// Update job state.
		pJob->Status(CThreadJob::COMPLETED);

		// Update thread state.
		m_eStatus = IDLE;
		m_pJob.Reset();

		// Notify thread pool.
		m_oPool.OnJobCompleted(pJob);
	}
	catch (const std::exception& e)
	{
		WCL::ReportUnhandledException(TXT("Unexpected exception caught in CWorkerThread::OnRunJob()\n\n%hs"), e.what());
	}
	catch (...)
	{
		WCL::ReportUnhandledException(TXT("Unexpected unknown exception caught in CWorkerThread::OnRunJob()"));
	}
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
	::PostQuitMessage(CMsgThread::THREAD_EXIT_SUCCESS);
}
