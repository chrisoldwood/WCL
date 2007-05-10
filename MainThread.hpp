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
	virtual	~CMainThread();
	
protected:
	//
	// Members.
	//

	// The main thread function.
	virtual void Run();

	//
	// Message handlers.
	//
	virtual void OnThreadMsg(UINT nMsg, WPARAM wParam, LPARAM lParam);

	// Friends.
	friend class CApp;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // MAINTHREAD_HPP
