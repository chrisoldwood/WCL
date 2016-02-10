/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MSGTHREAD.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMsgThread class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MSGTHREAD_HPP
#define MSGTHREAD_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "IMsgThread.hpp"
#include "Thread.hpp"
#include <list>

/******************************************************************************
**
** A thread derived class which is message driven.
**
*******************************************************************************
*/

class CMsgThread : public WCL::IMsgThread, public CThread
{
public:
	//
	// Constructors/Destructor.
	//
	CMsgThread();
	virtual	~CMsgThread();

	//
	// Properties.
	//

	//! Get the result from the WM_QUIT message.
	int Result() const;

	//
	// Message filtering.
	//
	virtual void AddMsgFilter(IMsgFilter* pFilter);
	virtual void RemoveMsgFilter(IMsgFilter* pFilter);

	//
	// Message processing.
	//
	bool ProcessMsgQueue(bool bRepostQuitMsg = true);

	const MSG& CurrentMsg() const;

	//! Wait for message or handle to be signalled.
	bool WaitForMessageOrSignal(HANDLE handle) const;

	//
	// Constants.
	//

	//! The thread result code for success.
	static const int THREAD_EXIT_SUCCESS = EXIT_SUCCESS;

	//! The thread result code for failure.
	static const int THREAD_EXIT_FAILURE = EXIT_FAILURE;

protected:
	// Template short-hands.
	typedef std::list<IMsgFilter*> CMsgFilters;

	//
	// Members.
	//
	MSG			m_oMsg;
	CMsgFilters	m_oMsgFilters;
	int			m_nResult;			//!< The WM_QUIT result.

	// The main thread function.
	virtual void Run();

	//
	// Message handlers.
	//
	virtual void OnThreadMsg(UINT nMsg, WPARAM wParam, LPARAM lParam);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

////////////////////////////////////////////////////////////////////////////////
//! Get the result from the WM_QUIT message.

inline int CMsgThread::Result() const
{
	return m_nResult;
}

inline const MSG& CMsgThread::CurrentMsg() const
{
	return m_oMsg;
}

#endif //MSGTHREAD_HPP
