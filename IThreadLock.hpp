/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ITHREADLOCK.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The IThreadLock interface declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ITHREADLOCK_HPP
#define ITHREADLOCK_HPP

/******************************************************************************
** 
** Interface for controlling a thread lock.
**
*******************************************************************************
*/

class IThreadLock
{
public:
	//
	// Methods.
	//
	virtual void Aquire() = 0;
	virtual void Release() = 0;
	
protected:
	// Make interface.
	virtual ~IThreadLock() = 0 {}; 
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // ITHREADLOCK_HPP
