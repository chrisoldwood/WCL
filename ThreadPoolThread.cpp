/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		THREADPOOLTHREAD.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	ThreadPoolThread class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ThreadPoolThread.hpp"
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

ThreadPoolThread::ThreadPoolThread(CThreadPool& oPool, size_t nPoolID)
	: m_oPool(oPool)
	, m_nPoolID(nPoolID)
	, m_eStatus(STOPPED)
	, m_oSyncEvent(true, false)
	, m_pJob()
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

ThreadPoolThread::~ThreadPoolThread()
{
	ASSERT(m_eStatus == STOPPED);

	::CloseHandle(m_hThread);
}

#if (__GNUC__ >= 8) // GCC 8+
// error: format '%hs' expects argument of type 'short int*', but argument 3 has type 'const char*' [-Werror=format=]
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif

/******************************************************************************
** Method:		ThreadFunction()
**
** Description:	The inital function for the thread.
**
** Parameters:	lpParam		The ThreadPoolThread object.
**
** Returns:		0.
**
*******************************************************************************
*/

DWORD WINAPI ThreadPoolThread::ThreadFunction(LPVOID lpParam)
{
	// Translate structured exceptions.
	WCL::SeTranslator::Install();

	ThreadPoolThread* pThread = reinterpret_cast<ThreadPoolThread*>(lpParam);

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
	catch (const Core::Exception& e)
	{
		WCL::ReportUnhandledException(TXT("Unexpected exception caught in ThreadPoolThread::Run()\n\n%s"), e.twhat());
	}
	catch (const std::exception& e)
	{
		WCL::ReportUnhandledException(TXT("Unexpected exception caught in ThreadPoolThread::Run()\n\n%hs"), e.what());
	}
	catch (...)
	{
		WCL::ReportUnhandledException(TXT("Unexpected unknown exception caught in ThreadPoolThread::Run()"));
	}

	// Signal calling thread that we've stopped.
	pThread->m_eStatus = STOPPED;
	pThread->m_oSyncEvent.Signal();

	return 0;
}

#if (__GNUC__ >= 8) // GCC 8+
#pragma GCC diagnostic pop
#endif

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

void ThreadPoolThread::Start()
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

void ThreadPoolThread::Stop()
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

void ThreadPoolThread::RunJob(ThreadJobPtr& pJob)
{
	ASSERT(pJob.get() != nullptr);
	ASSERT(pJob->Status() == CThreadJob::PENDING);
	ASSERT(m_eStatus == IDLE);
	ASSERT(m_pJob.get() == nullptr);

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

void ThreadPoolThread::OnThreadMsg(UINT nMsg, WPARAM /*wParam*/, LPARAM /*lParam*/)
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

void ThreadPoolThread::OnStartThread()
{
}

#if (__GNUC__ >= 8) // GCC 8+
// error: format '%hs' expects argument of type 'short int*', but argument 3 has type 'const char*' [-Werror=format=]
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif

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

void ThreadPoolThread::OnRunJob()
{
	ASSERT(m_pJob.get() != nullptr);
	ASSERT(m_pJob->Status() == CThreadJob::RUNNING);

	// Get the job to run.
	ThreadJobPtr pJob = m_pJob;

	try
	{
		// Run it.
		pJob->Run();
	}
	catch (const Core::Exception& e)
	{
		WCL::ReportUnhandledException(TXT("Unexpected exception caught in ThreadPoolThread::OnRunJob()\n\n%s"), e.twhat());
	}
	catch (const std::exception& e)
	{
		WCL::ReportUnhandledException(TXT("Unexpected exception caught in ThreadPoolThread::OnRunJob()\n\n%hs"), e.what());
	}
	catch (...)
	{
		WCL::ReportUnhandledException(TXT("Unexpected unknown exception caught in ThreadPoolThread::OnRunJob()"));
	}

	// Update job state.
	pJob->Status(CThreadJob::COMPLETED);

	// Update thread state.
	m_eStatus = IDLE;
	m_pJob.reset();

	// Notify thread pool.
	m_oPool.OnJobCompleted(pJob);
}

#if (__GNUC__ >= 8) // GCC 8+
#pragma GCC diagnostic pop
#endif

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

void ThreadPoolThread::OnStopThread()
{
	::PostQuitMessage(CMsgThread::THREAD_EXIT_SUCCESS);
}
