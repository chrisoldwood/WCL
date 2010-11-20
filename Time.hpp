/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TIME.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CTime class declarations.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_TIME_HPP
#define WCL_TIME_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "TimeSpan.hpp"

// Forward declarations.
class CDateTime;

namespace WCL
{
class IInputStream;
class IOutputStream;
}

/******************************************************************************
**
** This class is used to represent a time. It is stored and manipulated as if
** it was a UTC time_t, with the date part set 01/01/1970.
**
*******************************************************************************
*/

class CTime
{
public:
	//
	// Constructors/Destructor.
	//
	CTime();
	CTime(WCL::Seconds tTime);
	CTime(int  iHours, int  iMins, int  iSecs);

	//
	// Class limits.
	//
	static CTime Min();
	static CTime Max();

	//
	// Core accessors & mutators.
	//
	void Set();
	void Set(WCL::Seconds tTime);
	void Set(int  iHours, int  iMins, int  iSecs);
	void Get(int& iHours, int& iMins, int& iSecs) const;

	void Hours(int iHours);
	int  Hours() const;
	void Mins(int iMins);
	int  Mins() const;
	void Secs(int iSecs);
	int  Secs() const;

	WCL::Seconds GetTimeInSecs() const;

	static CTime Current();

	//
	// Time string formats.
	//
	enum Format
	{
		FMT_ISO			= 0x0001,		// ISO standard format (HH:MM:SS).
		FMT_WIN_SHORT	= 0x0002,		// Windows locale short format (e.g. HH:MM).
		FMT_WIN_LONG	= 0x0003,		// Windows locale long format (e.g. HH:MM:SS).
	};

	//
	// Locale information.
	//
	static CString FieldSeparator();

	//
	// Conversion methods.
	//
	CString ToString(int nFormat = FMT_WIN_LONG) const;
	bool    FromString(const tchar* pszTime);

	//
	// Comparison operators.
	//
	bool operator ==(const CTime& rRHS) const;
	bool operator !=(const CTime& rRHS) const;
	bool operator  <(const CTime& rRHS) const;
	bool operator  >(const CTime& rRHS) const;
	bool operator <=(const CTime& rRHS) const;
	bool operator >=(const CTime& rRHS) const;

	//
	// Arithmetic operators.
	//
	CTimeSpan operator -(const CTime& rRHS) const;

	void operator +=(const CTimeSpan& rRHS);
	void operator -=(const CTimeSpan& rRHS);

protected:
	//
	// Members.
	//
	WCL::Seconds	m_tTime;

	//
	// Friends.
	//
	friend class CTimeSpan;
	friend class CDateTime;

	//
	// Persistance.
	//
	friend void operator >>(WCL::IInputStream&  rStream, CTime& rTime);
	friend void operator <<(WCL::IOutputStream& rStream, const CTime& rTime);
};

/******************************************************************************
**
** Implementation of CTime inline functions.
**
*******************************************************************************
*/

inline CTime CTime::Min()
{
	return CTime(0, 0, 0);
}

inline CTime CTime::Max()
{
	return CTime(23, 59, 59);
}

inline void CTime::Set(WCL::Seconds tTime)
{
	m_tTime = (tTime % WCL::SECS_PER_DAY);
}

inline void CTime::Hours(int iHours)
{
	int iOldHours, iMins, iSecs;

	Get(iOldHours, iMins, iSecs);
	Set(iHours, iMins, iSecs);
}

inline int CTime::Hours() const
{
	int iHours, iMins, iSecs;

	Get(iHours, iMins, iSecs);

	return iHours;
}

inline void CTime::Mins(int iMins)
{
	int iHours, iOldMins, iSecs;

	Get(iHours, iOldMins, iSecs);
	Set(iHours, iMins, iSecs);
}

inline int CTime::Mins() const
{
	int iHours, iMins, iSecs;

	Get(iHours, iMins, iSecs);

	return iMins;
}

inline void CTime::Secs(int iSecs)
{
	int iHours, iMins, iOldSecs;

	Get(iHours, iMins, iOldSecs);
	Set(iHours, iMins, iSecs);
}

inline int CTime::Secs() const
{
	int iHours, iMins, iSecs;

	Get(iHours, iMins, iSecs);

	return iSecs;
}

inline WCL::Seconds CTime::GetTimeInSecs() const
{
	return m_tTime;
}

inline bool CTime::operator ==(const CTime& rRHS) const
{
	return (m_tTime == rRHS.m_tTime);
}

inline bool CTime::operator !=(const CTime& rRHS) const
{
	return (m_tTime != rRHS.m_tTime);
}

inline bool CTime::operator <(const CTime& rRHS) const
{
	return (m_tTime < rRHS.m_tTime);
}

inline bool CTime::operator >(const CTime& rRHS) const
{
	return (m_tTime > rRHS.m_tTime);
}

inline bool CTime::operator <=(const CTime& rRHS) const
{
	return ((*this < rRHS) || (*this == rRHS));
}

inline bool CTime::operator >=(const CTime& rRHS) const
{
	return ((*this > rRHS) || (*this == rRHS));
}

inline CTimeSpan CTime::operator -(const CTime& rRHS) const
{
	return CTimeSpan(m_tTime - rRHS.m_tTime);
}

inline void CTime::operator +=(const CTimeSpan& rRHS)
{
	m_tTime += rRHS.m_tSpan;
}

inline void CTime::operator -=(const CTimeSpan& rRHS)
{
	m_tTime -= rRHS.m_tSpan;
}

#endif // WCL_TIME_HPP
