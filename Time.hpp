/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TIME.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CTime & CTimeSpan class declarations.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TIME_HPP
#define TIME_HPP

// Forward declarations.
class CStream;
class CTimeSpan;

/******************************************************************************
** 
** Constants.
**
*******************************************************************************
*/

const int SECS_PER_MIN  = 60;
const int SECS_PER_HOUR = 60*60;
const int SECS_PER_DAY  = 60*60*24;

/******************************************************************************
** 
** This class is used to represent a time between 00:00:00 and 23:59:59.
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
	void Set(int  iHours, int  iMins, int  iSecs);
	void Get(int& iHours, int& iMins, int& iSecs) const;

	void Hours(int iHours);
	int  Hours() const;
	void Mins(int iMins);
	int  Mins() const;
	void Secs(int iSecs);
	int  Secs() const;

	static CTime Current();

	//
	// String conversion fields.
	// and common formats.
	//
	enum Field
	{
		HH = 0x01,	// 2 digit hours
		MM = 0x02,	// 2 digit minutes
		SS = 0x04	// 2 digit seconds
	};

	enum Format
	{
		HH_MM    = HH | MM,
		HH_MM_SS = HH | MM | SS
	};

	//
	// Conversion methods.
	//
	CString ToString(int nFields = HH_MM_SS) const;
	bool    FromString(const char* pszTime);

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

	//
	// Persistance.
	//
	void operator <<(CStream& rStream);
	void operator >>(CStream& rStream) const;
	
protected:
	//
	// Members.
	//
	int32	m_lTime;	// The time in seconds from 00:00:00.

	//
	// Friends.
	//
	friend class CTimeSpan;
};

/******************************************************************************
** 
** This class is used to represent a period between two times.
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
	CTimeSpan(int iSecs);
	CTimeSpan(const CTime& rTime);
	
	// Accessors.
	int Secs() const;
	int Mins() const;
	int Hours() const;
	int Days() const;

protected:
	//
	// Members.
	//
	int32	m_lSpan;	// The time span in seconds.

	//
	// Friends.
	//
	friend class CTime;
};

/******************************************************************************
**
** Implementation of CTime inline functions.
**
*******************************************************************************
*/

inline CTime::CTime()
	: m_lTime(0)
{
}

inline CTime::CTime(int iHours, int iMins, int iSecs)
{
	Set(iHours, iMins, iSecs);
}

inline CTime CTime::Min()
{
	return CTime(0, 0, 0);
}

inline CTime CTime::Max()
{
	return CTime(23, 59, 59);
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

inline bool CTime::operator ==(const CTime& rRHS) const
{
	return (m_lTime == rRHS.m_lTime);
}

inline bool CTime::operator !=(const CTime& rRHS) const
{
	return (m_lTime != rRHS.m_lTime);
}

inline bool CTime::operator <(const CTime& rRHS) const
{
	return (m_lTime < rRHS.m_lTime);
}

inline bool CTime::operator >(const CTime& rRHS) const
{
	return (m_lTime > rRHS.m_lTime);
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
	return CTimeSpan(m_lTime - rRHS.m_lTime);
}

inline void CTime::operator +=(const CTimeSpan& rRHS)
{
	m_lTime += rRHS.m_lSpan;
}

inline void CTime::operator -=(const CTimeSpan& rRHS)
{
	m_lTime -= rRHS.m_lSpan;
}

/******************************************************************************
**
** Implementation of CTimeSpan inline functions.
**
*******************************************************************************
*/

inline CTimeSpan::CTimeSpan()
	: m_lSpan(0)
{
}

inline CTimeSpan::CTimeSpan(int iSecs)
	: m_lSpan(iSecs)
{
}

inline CTimeSpan::CTimeSpan(const CTime& rTime)
	: m_lSpan(rTime.m_lTime)
{
}

inline int CTimeSpan::Secs() const
{
	return m_lSpan;
}

inline int CTimeSpan::Mins() const
{
	return m_lSpan / SECS_PER_MIN;
}

inline int CTimeSpan::Hours() const
{
	return m_lSpan / SECS_PER_HOUR;
}

inline int CTimeSpan::Days() const
{
	return m_lSpan / SECS_PER_DAY;
}

#endif //TIME_HPP
