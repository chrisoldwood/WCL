/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		THREADJOB.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CThreadJob class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef THREADJOB_HPP
#define THREADJOB_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** A job that runs on a worker thread in a thread pool.
**
*******************************************************************************
*/

class CThreadJob
{
public:
	//
	// Constructors/Destructor.
	//
	CThreadJob();
	virtual ~CThreadJob();

	// Job status.
	enum JobStatus
	{
		PENDING,
		RUNNING,
		COMPLETED,
		CANCELLED,
	};

	//
	// Accessors.
	//
	JobStatus Status() const;
	void      Status(JobStatus eStatus);

	//
	// Methods.
	//
	virtual void Run() = 0;

protected:
	//
	// Members.
	//
	JobStatus	m_eStatus;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CThreadJob::JobStatus CThreadJob::Status() const
{
	return m_eStatus;
}

inline void CThreadJob::Status(JobStatus eStatus)
{
	m_eStatus = eStatus;
}

#endif // THREADJOB_HPP
