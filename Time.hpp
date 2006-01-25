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
class CDateTime;

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
** This class is used to wrap a time_t that represents a time in GMT.
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
	CTime(time_t tTime);
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
	void Set(time_t tTime);
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
	bool    FromString(const char* pszTime);

	//
	// Conversion operators.
	//
	void operator =(time_t tTime);
	operator time_t() const;

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
	time_t	m_tTime;

	//
	// Friends.
	//
	friend class CTimeSpan;
	friend class CDateTime;
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
	CTimeSpan(int nSecs);
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
	int	m_nSpan;

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
	: m_tTime(0)
{
}

inline CTime::CTime(time_t tTime)
{
	Set(tTime);
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

inline void CTime::Set(time_t tTime)
{
	m_tTime = (tTime % SECS_PER_DAY);
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

inline void CTime::operator =(time_t tTime)
{
	Set(tTime);
}

inline CTime::operator time_t() const
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
	m_tTime += rRHS.m_nSpan;
}

inline void CTime::operator -=(const CTimeSpan& rRHS)
{
	m_tTime -= rRHS.m_nSpan;
}

/******************************************************************************
**
** Implementation of CTimeSpan inline functions.
**
*******************************************************************************
*/

inline CTimeSpan::CTimeSpan()
	: m_nSpan(0)
{
}

inline CTimeSpan::CTimeSpan(int nSecs)
	: m_nSpan(nSecs)
{
}

inline CTimeSpan::CTimeSpan(const CTime& rTime)
	: m_nSpan(rTime.m_tTime)
{
}

inline int CTimeSpan::Secs() const
{
	return m_nSpan;
}

inline int CTimeSpan::Mins() const
{
	return m_nSpan / SECS_PER_MIN;
}

inline int CTimeSpan::Hours() const
{
	return m_nSpan / SECS_PER_HOUR;
}

inline int CTimeSpan::Days() const
{
	return m_nSpan / SECS_PER_DAY;
}

#endif //TIME_HPP
