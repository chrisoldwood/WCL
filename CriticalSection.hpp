/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CRITICALSECTION.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CCriticalSection class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CRITICALSECTION_HPP
#define CRITICALSECTION_HPP

/******************************************************************************
** 
** A Critical Section thread lock.
**
*******************************************************************************
*/

class CCriticalSection : public IThreadLock
{
public:
	//
	// Constructors/Destructor.
	//
	CCriticalSection();
	~CCriticalSection();

	//
	// Methods.
	//
	virtual void Lock();
	virtual void Unlock();
	
protected:
	//
	// Members.
	//
	CRITICAL_SECTION	m_oLock;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CCriticalSection::Lock()
{
	::EnterCriticalSection(&m_oLock);
}

inline void CCriticalSection::Unlock()
{
	::LeaveCriticalSection(&m_oLock);
}

#endif // CRITICALSECTION_HPP
