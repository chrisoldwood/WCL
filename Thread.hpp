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

/******************************************************************************
** 
** The base class from which threads are derived.
**
*******************************************************************************
*/

class CThread
{
public:
	//
	// Constructors/Destructor.
	//
	CThread();
	~CThread();
	
	// The main thread function.
	virtual void Run() = 0;

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //THREAD_HPP
