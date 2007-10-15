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

#if _MSC_VER > 1000
#pragma once
#endif

#include "IThreadLock.hpp"

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
	virtual void Aquire();
	virtual void Release();
	
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

#endif // CRITICALSECTION_HPP
