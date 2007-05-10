/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MSGTHREAD.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMsgThread class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MSGTHREAD_HPP
#define MSGTHREAD_HPP

/******************************************************************************
** 
** A thread derived class which is message driven.
**
*******************************************************************************
*/

class CMsgThread : public CThread
{
public:
	//
	// Constructors/Destructor.
	//
	CMsgThread();
	virtual	~CMsgThread();

	//
	// Message filtering.
	//
	void AddMsgFilter(IMsgFilter* pFilter);
	void RemoveMsgFilter(IMsgFilter* pFilter);

	//
	// Message processing.
	//
	bool ProcessMsgQueue();

	const MSG& CurrentMsg() const;

protected:
	// Template shorthands.
	typedef std::list<IMsgFilter*> CMsgFilters;

	//
	// Members.
	//
	MSG			m_oMsg;
	CMsgFilters	m_oMsgFilters;

	// The main thread function.
	virtual void Run();

	//
	// Message handlers.
	//
	virtual void OnThreadMsg(UINT nMsg, WPARAM wParam, LPARAM lParam);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline const MSG& CMsgThread::CurrentMsg() const
{
	return m_oMsg;
}

#endif //MSGTHREAD_HPP
