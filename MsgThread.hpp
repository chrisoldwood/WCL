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

class CMsgThread
{
public:
	//
	// Constructors/Destructor.
	//
	CMsgThread();
	~CMsgThread();

	// The main thread function.
	virtual void Run();

	//
	// Message filtering.
	//
	void AddMsgFilter(CMsgFilter& rFilter);
	void RemoveMsgFilter(CMsgFilter& rFilter);

	//
	// Message processing.
	//
	bool ProcessMsgQueue();

	const MSG& CurrentMsg() const;

protected:
	//
	// Members.
	//
	MSG			m_oMsg;
	CMsgFilters	m_MsgFilters;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CMsgThread::AddMsgFilter(CMsgFilter& rFilter)
{
	m_MsgFilters.Add(rFilter);
}

inline void CMsgThread::RemoveMsgFilter(CMsgFilter& rFilter)
{
	m_MsgFilters.Remove(rFilter);
}

inline const MSG& CMsgThread::CurrentMsg() const
{
	return m_oMsg;
}

#endif //MSGTHREAD_HPP
