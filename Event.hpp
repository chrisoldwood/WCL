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

/******************************************************************************
** 
** An Event thread lock.
**
*******************************************************************************
*/

class CEvent
{
public:
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

	bool Wait(DWORD dwWaitTime = INFINITE);

protected:
	//
	// Members.
	//
	HANDLE	m_hEvent;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CEvent::CEvent(bool bManual, bool bSignaled)
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

inline bool CEvent::Wait(DWORD dwWaitTime)
{
	ASSERT(m_hEvent != NULL);

	DWORD dwResult = ::WaitForSingleObject(m_hEvent, dwWaitTime);

	ASSERT((dwResult == WAIT_OBJECT_0) || (dwResult == WAIT_TIMEOUT) );

	return (dwResult == WAIT_OBJECT_0);
}

#endif // EVENT_HPP
