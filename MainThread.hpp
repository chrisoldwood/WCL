/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAINTHREAD.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CMainThread class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MAINTHREAD_HPP
#define MAINTHREAD_HPP

/******************************************************************************
** 
** The main application thread.
**
*******************************************************************************
*/

class CMainThread : public CMsgThread
{
public:
	//
	// Constructors/Destructor.
	//
	CMainThread();
	~CMainThread();
	
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

#endif // MAINTHREAD_HPP
