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
	virtual ~CThread();
	
	// The main thread function.
	virtual void Run() = 0;

	//
	// Accessors.
	//
	HANDLE Handle() const;
	DWORD  ID() const;

protected:
	//
	// Members.
	//
	HANDLE	m_hHandle;
	DWORD	m_dwID;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HANDLE CThread::Handle() const
{
	return m_hHandle;
}

inline DWORD CThread::ID() const
{
	return m_dwID;
}

#endif //THREAD_HPP
