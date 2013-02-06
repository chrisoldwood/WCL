////////////////////////////////////////////////////////////////////////////////
//! \file   IMsgThread.hpp
//! \brief  The IMsgThread interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_IMSGTHREAD_HPP
#define WCL_IMSGTHREAD_HPP

#if _MSC_VER > 1000
#pragma once
#endif

// Forward declarations.
class IMsgFilter;

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A thread that contains a message queue. This type of thread is used for
//! UI based code.

class IMsgThread
{
public:
	//! Attach a message queue filter.
	virtual void AddMsgFilter(IMsgFilter* pFilter) = 0;

	//! Detach a message queue filter.
	virtual void RemoveMsgFilter(IMsgFilter* pFilter) = 0;

protected:
	// Make abstract.
	virtual ~IMsgThread() {};
};

//namespace WCL
}

#endif // WCL_IMSGTHREAD_HPP
