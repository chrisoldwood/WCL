/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATETIME.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDateTime & CDateTimeSpan class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef DATETIME_HPP
#define DATETIME_HPP

// Forward declarations.
class CStream;
class CDateTimeSpan;

/******************************************************************************
** 
** This class is used to represent a date and time. See the CDate and CTime
** class declarations for the limits.
**
*******************************************************************************
*/

class CDateTime
{
public:
	//
	// Constructors/Destructor.
	//
	CDateTime();
	CDateTime(int iDay, int iMonth, int iYear, int iHours, int iMins, int iSecs);
	CDateTime(const CDate& rDate, const CTime& rTime);

	//
	// Class limits.
	//
	static CDateTime Min();
	static CDateTime Max();
	
	//
	// Core accessors & mutators.
	//
	void Set();
	void Set(int  iDay, int  iMonth, int  iYear, int  iHours, int  iMins, int  iSecs);
	void Get(int& iDay, int& iMonth, int& iYear, int& iHours, int& iMins, int& iSecs) const;

	CDate Date() const;
	void  Date(const CDate& rDate);

	CTime Time() const;
	void  Time(const CTime& rTime);

	static CDateTime Current();

	//
	// Comparison operators.
	//
	bool operator ==(const CDateTime& rRHS) const;
	bool operator !=(const CDateTime& rRHS) const;
	bool operator  <(const CDateTime& rRHS) const;
	bool operator  >(const CDateTime& rRHS) const;
	bool operator <=(const CDateTime& rRHS) const;
	bool operator >=(const CDateTime& rRHS) const;

	//
	// Arithmetic operators.
	//
	CDateTimeSpan operator  -(const CDateTime& rRHS) const;
	void          operator -=(const CDateTimeSpan& rRHS);
	

	//
	// Persistance.
	//
	void operator <<(CStream& rStream);
	void operator >>(CStream& rStream) const;
	
protected:
	//
	// Members.
	//
	CDate	m_Date;		// The date part.
	CTime	m_Time;		// The time part.

	//
	// Friends.
	//
	friend class CDateTimeSpan;
};

/******************************************************************************
** 
** This class is used to represent a period between two date-times.
**
*******************************************************************************
*/

class CDateTimeSpan
{
public:
	//
	// Constructors/Destructor.
	//
	CDateTimeSpan();
	CDateTimeSpan(int64 lSecs);
	CDateTimeSpan(const CDateTime& rDateTime);
	
	//
	// Accessors.
	//
	int Secs() const;
	int Mins() const;
	int Hours() const;
	int Days() const;

protected:
	//
	// Members.
	//
	int64	m_lSpan;	// The span in seconds.

	//
	// Friends.
	//
	friend class CDateTime;
};

/******************************************************************************
**
** Implementation of CDateTime inline functions.
**
*******************************************************************************
*/

inline CDateTime::CDateTime()
{
}

inline CDateTime::CDateTime(int iDay, int iMonth, int iYear, int iHours, int iMins, int iSecs)
{
	Set(iDay, iMonth, iYear, iHours, iMins, iSecs);
}

inline CDateTime::CDateTime(const CDate& rDate, const CTime& rTime)
	: m_Date(rDate)
	, m_Time(rTime)
{
}

inline CDateTime CDateTime::Min()
{
	return CDateTime(CDate::Min(), CTime::Min());
}

inline CDateTime CDateTime::Max()
{
	return CDateTime(CDate::Max(), CTime::Max());
}

inline void CDateTime::Set()
{
	m_Date.Set();
	m_Time.Set();
}

inline void CDateTime::Set(int iDay, int iMonth, int iYear, int iHours, int iMins, int iSecs)
{
	m_Date.Set(iDay, iMonth, iYear);
	m_Time.Set(iHours, iMins, iSecs);
}

inline void CDateTime::Get(int& iDay, int& iMonth, int& iYear, int& iHours, int& iMins, int& iSecs) const
{
	m_Date.Get(iDay,   iMonth, iYear);
	m_Time.Get(iHours, iMins,  iSecs);
}

inline CDate CDateTime::Date() const
{
	return m_Date;
}

inline void  CDateTime::Date(const CDate& rDate)
{
	m_Date = rDate;
}

inline CTime CDateTime::Time() const
{
	return m_Time;
}

inline void  CDateTime::Time(const CTime& rTime)
{
	m_Time = rTime;
}

inline bool CDateTime::operator ==(const CDateTime& rRHS) const
{
	return ((m_Date == rRHS.m_Date) && (m_Time == rRHS.m_Time));
}

inline bool CDateTime::operator !=(const CDateTime& rRHS) const
{
	return ((m_Date != rRHS.m_Date) || (m_Time != rRHS.m_Time));
}

inline bool CDateTime::operator <(const CDateTime& rRHS) const
{
	return ( (m_Date  < rRHS.m_Date)
		 || ((m_Date == rRHS.m_Date) && (m_Time < rRHS.m_Time)) );
}

inline bool CDateTime::operator >(const CDateTime& rRHS) const
{
	return ( (m_Date  > rRHS.m_Date)
		 || ((m_Date == rRHS.m_Date) && (m_Time > rRHS.m_Time)) );
}

inline bool CDateTime::operator <=(const CDateTime& rRHS) const
{
	return ((*this < rRHS) || (*this == rRHS));
}

inline bool CDateTime::operator >=(const CDateTime& rRHS) const
{
	return ((*this > rRHS) || (*this == rRHS));
}

inline CDateTimeSpan CDateTime::operator -(const CDateTime& rRHS) const
{
	CDateTimeSpan dtsThis(*this);
	CDateTimeSpan dtsRHS(rRHS);
	
	return CDateTimeSpan(dtsThis.m_lSpan - dtsRHS.m_lSpan);
}

inline void CDateTime::operator -=(const CDateTimeSpan& rRHS)
{
	// TODO: Implement properly.
	m_Time -= CTimeSpan(rRHS.Secs());
}

/******************************************************************************
**
** Implementation of CDateTimeSpan inline functions.
**
*******************************************************************************
*/

inline CDateTimeSpan::CDateTimeSpan()
	: m_lSpan(0)
{
}

inline CDateTimeSpan::CDateTimeSpan(int64 lSecs)
	: m_lSpan(lSecs)
{
}

inline CDateTimeSpan::CDateTimeSpan(const CDateTime& rDateTime)
{
	// Convert date and time to spans.
	int64 lDays = CDateSpan(rDateTime.Date()).Days();
	int64 lSecs = CTimeSpan(rDateTime.Time()).Secs();

	// Calculate span.
	m_lSpan = (lDays * SECS_PER_DAY) + lSecs;
}

inline int CDateTimeSpan::Secs() const
{
	return (int) m_lSpan;
}

inline int CDateTimeSpan::Mins() const
{
	return (int) (m_lSpan / SECS_PER_MIN);
}

inline int CDateTimeSpan::Hours() const
{
	return (int) (m_lSpan / SECS_PER_HOUR);
}

inline int CDateTimeSpan::Days() const
{
	return (int) (m_lSpan / SECS_PER_DAY);
}

#endif //DATETIME_HPP
