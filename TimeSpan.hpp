/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TIMESPAN.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CTimeSpan class declarations.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_TIMESPAN_HPP
#define WCL_TIMESPAN_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This class is used to represent a period between two times in seconds.
**
*******************************************************************************
*/

class CTimeSpan
{
public:
	//
	// Constructors/Destructor.
	//
	CTimeSpan();
	CTimeSpan(WCL::Seconds tSecs);
	
	// Accessors.
	int Secs() const;
	int Mins() const;
	int Hours() const;
	int Days() const;

protected:
	//
	// Members.
	//
	WCL::Seconds	m_tSpan;

	//
	// Friends.
	//
	friend class CTime;
};

/******************************************************************************
**
** Implementation of CTimeSpan inline functions.
**
*******************************************************************************
*/

inline CTimeSpan::CTimeSpan()
	: m_tSpan(0)
{
}

inline CTimeSpan::CTimeSpan(WCL::Seconds tSecs)
	: m_tSpan(tSecs)
{
}

inline int CTimeSpan::Secs() const
{
	return static_cast<int>(m_tSpan);
}

inline int CTimeSpan::Mins() const
{
	return static_cast<int>(m_tSpan / WCL::SECS_PER_MIN);
}

inline int CTimeSpan::Hours() const
{
	return static_cast<int>(m_tSpan / WCL::SECS_PER_HOUR);
}

inline int CTimeSpan::Days() const
{
	return static_cast<int>(m_tSpan / WCL::SECS_PER_DAY);
}

#endif // WCL_TIMESPAN_HPP
