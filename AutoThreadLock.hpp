/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		AUTOTHREADLOCK.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CAutoThreadLock class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef AUTOTHREADLOCK_HPP
#define AUTOTHREADLOCK_HPP

/******************************************************************************
** 
** Helper class to automatically aquire and release a thread lock.
**
*******************************************************************************
*/

class CAutoThreadLock
{
public:
	//
	// Constructors/Destructor.
	//
	CAutoThreadLock(IThreadLock& oLock);
	~CAutoThreadLock();
	
protected:
	//
	// Members.
	//
	IThreadLock&	m_oLock;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CAutoThreadLock::CAutoThreadLock(IThreadLock& oLock)
	: m_oLock(oLock)
{
	m_oLock.Aquire();
}

inline CAutoThreadLock::~CAutoThreadLock()
{
	m_oLock.Release();
}

#endif // AUTOTHREADLOCK_HPP
