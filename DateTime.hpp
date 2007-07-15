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
#ifndef WCL_DATETIME_HPP
#define WCL_DATETIME_HPP

// Forward declarations.
class CDateTimeSpan;

namespace WCL
{
class IInputStream;
class IOutputStream;
}

/******************************************************************************
** 
** This class is used to represent a date. It is stored and manipulated as if
** it was a UTC time_t. Consequenetly there is no notion of Daylight Saving or
** timezones, which makes date and time arithmetic easier.
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
	CDateTime(seconds_t tDateTime);
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
	void Set(seconds_t tDateTime);
	void Set(int  iDay, int  iMonth, int  iYear, int  iHours, int  iMins, int  iSecs);
	void Get(int& iDay, int& iMonth, int& iYear, int& iHours, int& iMins, int& iSecs) const;

	CDate Date() const;
	void  Date(const CDate& rDate);

	CTime Time() const;
	void  Time(const CTime& rTime);

	seconds_t GetDateTimeInSecs() const;

	static CDateTime Current();

	static CDateTime FromLocalTime(time_t tDateTime);

	//
	// Conversion methods.
	//
	CString ToString(int nDateFormat = CDate::FMT_WIN_SHORT, int nTimeFormat = CTime::FMT_WIN_LONG) const;
	bool    FromString(const char* pszDateTime);

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
	
protected:
	//
	// Members.
	//
	seconds_t	m_tDateTime;

	//
	// Friends.
	//
	friend class CDateTimeSpan;

private:
	//
	// Persistance.
	//
	friend void operator >>(WCL::IInputStream& , CDateTime& rDateTime);
	friend void operator <<(WCL::IOutputStream&, const CDateTime& rDateTime);
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
	CDateTimeSpan(seconds_t tSecs);
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
	seconds_t	m_tSpan;

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
	: m_tDateTime(0)
{
}

inline CDateTime::CDateTime(seconds_t tDateTime)
{
	Set(tDateTime);
}

inline CDateTime::CDateTime(int iDay, int iMonth, int iYear, int iHours, int iMins, int iSecs)
{
	Set(iDay, iMonth, iYear, iHours, iMins, iSecs);
}

inline CDateTime::CDateTime(const CDate& rDate, const CTime& rTime)
	: m_tDateTime(rDate.m_tDate + rTime.m_tTime)
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
	CDate oDate = CDate::Current();
	CTime oTime = CTime::Current();

	*this = CDateTime(oDate, oTime);
}

inline void CDateTime::Set(seconds_t tDateTime)
{
	m_tDateTime = tDateTime;
}

inline void CDateTime::Set(int iDay, int iMonth, int iYear, int iHours, int iMins, int iSecs)
{
	CDate oDate(iDay,   iMonth, iYear);
	CTime oTime(iHours, iMins,  iSecs);

	*this = CDateTime(oDate, oTime);
}

inline void CDateTime::Get(int& iDay, int& iMonth, int& iYear, int& iHours, int& iMins, int& iSecs) const
{
	CDate oDate = Date();
	CTime oTime = Time();

	oDate.Get(iDay,   iMonth, iYear);
	oTime.Get(iHours, iMins,  iSecs);
}

inline CDate CDateTime::Date() const
{
	return CDate(m_tDateTime - (m_tDateTime % SECS_PER_DAY));
}

inline void  CDateTime::Date(const CDate& rDate)
{
	CTime oTime = Time();

	*this = CDateTime(rDate, oTime);
}

inline CTime CDateTime::Time() const
{
	return CTime(m_tDateTime % SECS_PER_DAY);
}

inline void  CDateTime::Time(const CTime& rTime)
{
	CDate oDate = Date();

	*this = CDateTime(oDate, rTime);
}

inline CString CDateTime::ToString(int nDateFormat, int nTimeFormat) const
{
	const char* pszSep = (nDateFormat == CDate::FMT_ISO) ? "T": " ";

	return Date().ToString(nDateFormat) + pszSep + Time().ToString(nTimeFormat);
}

inline seconds_t CDateTime::GetDateTimeInSecs() const
{
	return m_tDateTime;
}

inline bool CDateTime::operator ==(const CDateTime& rRHS) const
{
	return (m_tDateTime == rRHS.m_tDateTime);
}

inline bool CDateTime::operator !=(const CDateTime& rRHS) const
{
	return (m_tDateTime != rRHS.m_tDateTime);
}

inline bool CDateTime::operator <(const CDateTime& rRHS) const
{
	return (m_tDateTime < rRHS.m_tDateTime);
}

inline bool CDateTime::operator >(const CDateTime& rRHS) const
{
	return (m_tDateTime > rRHS.m_tDateTime);
}

inline bool CDateTime::operator <=(const CDateTime& rRHS) const
{
	return (m_tDateTime <= rRHS.m_tDateTime);
}

inline bool CDateTime::operator >=(const CDateTime& rRHS) const
{
	return (m_tDateTime >= rRHS.m_tDateTime);
}

inline CDateTimeSpan CDateTime::operator -(const CDateTime& rRHS) const
{
	return CDateTimeSpan(m_tDateTime - rRHS.m_tDateTime);
}

inline void CDateTime::operator -=(const CDateTimeSpan& rRHS)
{
	m_tDateTime -= rRHS.m_tSpan;
}

/******************************************************************************
**
** Implementation of CDateTimeSpan inline functions.
**
*******************************************************************************
*/

inline CDateTimeSpan::CDateTimeSpan()
	: m_tSpan(0)
{
}

inline CDateTimeSpan::CDateTimeSpan(seconds_t tSecs)
	: m_tSpan(tSecs)
{
}

inline CDateTimeSpan::CDateTimeSpan(const CDateTime& rDateTime)
{
	m_tSpan = rDateTime.m_tDateTime;
}

inline int CDateTimeSpan::Secs() const
{
	return m_tSpan;
}

inline int CDateTimeSpan::Mins() const
{
	return (m_tSpan / SECS_PER_MIN);
}

inline int CDateTimeSpan::Hours() const
{
	return (m_tSpan / SECS_PER_HOUR);
}

inline int CDateTimeSpan::Days() const
{
	return (m_tSpan / SECS_PER_DAY);
}

#endif // WCL_DATETIME_HPP
