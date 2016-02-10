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

#if _MSC_VER > 1000
#pragma once
#endif

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
	virtual void Acquire() = 0;
	virtual void Release() = 0;

protected:
	// Make interface.
	virtual ~IThreadLock() {};
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // ITHREADLOCK_HPP
