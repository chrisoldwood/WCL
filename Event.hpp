/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EVENT.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CEvent class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EVENT_HPP
#define EVENT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
**
** An Event thread lock.
**
*******************************************************************************
*/

class CEvent /*: private NotCopyable*/
{
public:
	//! Create manual event.
	const static bool MANUAL = true;
	//! Create auto-reset event.
	const static bool AUTO_RESET = false;
	
	//! Create in signalled state.
	const static bool SIGNALLED = true;
	//! Create in non-signalled state.
	const static bool NOT_SIGNALLED = false;

	//
	// Constructors/Destructor.
	//
	CEvent(bool bManual, bool bSignaled);
	~CEvent();

	//
	// Accessors.
	//
	HANDLE Handle() const;

	//
	// Methods.
	//
	void Signal();
	void Reset();
	void Pulse();

	//! Wait for the event to become signalled.
	bool Wait(DWORD dwWaitTime = INFINITE) const;

	//! Query if the event is already signalled.
	bool IsSignalled() const;

protected:
	//
	// Members.
	//
	HANDLE	m_hEvent;

private:
	// NotCopyable.
	CEvent(const CEvent&);
	CEvent& operator=(const CEvent&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CEvent::CEvent(bool bManual, bool bSignaled)
	: m_hEvent()
{
	m_hEvent = ::CreateEvent(NULL, bManual, bSignaled, NULL);

	ASSERT(m_hEvent != NULL);
}

inline CEvent::~CEvent()
{
	::CloseHandle(m_hEvent);
}

inline HANDLE CEvent::Handle() const
{
	return m_hEvent;
}

inline void CEvent::Signal()
{
	ASSERT(m_hEvent != NULL);

	::SetEvent(m_hEvent);
}

inline void CEvent::Reset()
{
	ASSERT(m_hEvent != NULL);

	::ResetEvent(m_hEvent);
}

inline void CEvent::Pulse()
{
	ASSERT(m_hEvent != NULL);

	::PulseEvent(m_hEvent);
}

////////////////////////////////////////////////////////////////////////////////
//! Wait for the event to become signalled.

inline bool CEvent::Wait(DWORD dwWaitTime) const
{
	ASSERT(m_hEvent != NULL);

	DWORD dwResult = ::WaitForSingleObject(m_hEvent, dwWaitTime);

	ASSERT((dwResult == WAIT_OBJECT_0) || (dwResult == WAIT_TIMEOUT) );

	return (dwResult == WAIT_OBJECT_0);
}

////////////////////////////////////////////////////////////////////////////////
//! Query if the event is already signalled.

inline bool CEvent::IsSignalled() const
{
	return Wait(0);
}

#endif // EVENT_HPP
