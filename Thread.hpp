/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		THREAD.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CThread class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef THREAD_HPP
#define THREAD_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
**
** The base class from which threads are derived.
**
*******************************************************************************
*/

class CThread /*: private NotCopyable*/
{
public:
	//
	// Constructors/Destructor.
	//
	CThread();
	virtual ~CThread();

	//
	// Accessors.
	//
	HANDLE Handle() const;
	DWORD  ID() const;

	//
	// Methods.
	//
	bool PostMessage(UINT nMsg, WPARAM wParam = 0, LPARAM lParam = 0L);

protected:
	//
	// Members.
	//
	HANDLE	m_hThread;
	DWORD	m_dwID;

	// The main thread function.
	virtual void Run() = 0;

private:
	// NotCopyable.
	CThread(const CThread&);
	CThread& operator=(const CThread&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CThread::CThread()
	: m_hThread(NULL)
	, m_dwID(0)
{
}

inline CThread::~CThread()
{
}

inline HANDLE CThread::Handle() const
{
	return m_hThread;
}

inline DWORD CThread::ID() const
{
	return m_dwID;
}

inline bool CThread::PostMessage(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_dwID != 0);

	return (::PostThreadMessage(m_dwID, nMsg, wParam, lParam) != 0);
}

#endif //THREAD_HPP
