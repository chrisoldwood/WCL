/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAINTHREAD.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CMainThread class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MAINTHREAD_HPP
#define MAINTHREAD_HPP

/******************************************************************************
** 
** The main application thread.
**
*******************************************************************************
*/

class CMainThread : public CMsgThread
{
public:
	//
	// Constructors/Destructor.
	//
	CMainThread();
	~CMainThread();
	
protected:
	//
	// Members.
	//

	// The main thread function.
	virtual void Run();

	// Friends.
	friend class CApp;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CMainThread::CMainThread()
{
	m_hThread = NULL;
	m_dwID    = ::GetCurrentThreadId();
}

inline CMainThread::~CMainThread()
{
}

inline void CMainThread::Run()
{
	CMsgThread::Run();
}

#endif // MAINTHREAD_HPP
