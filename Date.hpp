/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDate & CDateSpan class declarations.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef DATE_HPP
#define DATE_HPP

// Forward declarations.
class CStream;
class CDateSpan;

/******************************************************************************
** 
** This class is used to represent a date between 01/01/1901 and 31/12/2099.
**
*******************************************************************************
*/

class CDate
{
public:
	//
	// Constructors/Destructor.
	//
	CDate();
	CDate(int iDay, int iMonth, int iYear);

	//
	// Class limits.
	//
	static CDate Min();
	static CDate Max();
	
	//	
	// Core accessors & mutators.
	//
	void Set();
	void Set(int  iDay, int  iMonth, int  iYear);
	void Get(int& iDay, int& iMonth, int& iYear) const;

	void Day(int iDay);
	int  Day() const;
	void Month(int iMonth);
	int  Month() const;
	void Year(int iYear);
	int  Year() const;

	int DayOfWeek() const;
	int DaysInMonth() const;

	static CDate Current();

	//
	// String conversion fields.
	// and common formats.
	//
	enum Field
	{
		SD = 0x01,	// Short day name.
		LD = 0x02,	// Long day name.
		DD = 0x04,	// 2 digit day.
		SM = 0x08,	// Short month name.
		LM = 0x10,	// Long month name.
		MM = 0x20,	// 2 digit month.
		YY = 0x40,	// 2 digit year.
		Y4 = 0x80	// 4 digit year.
	};

	enum Format
	{
		DD_MM_YY    = DD | MM | YY,
		DD_MM_YYYY  = DD | MM | Y4,
		SD_DD_MM_YY = SD | DD | MM | YY
	};

	//
	// Conversion methods.
	//
	CString ToString(int nFields = DD_MM_YY) const;
	bool    FromString(const char* pszDate);

	//
	// Comparison operators.
	//
	bool operator ==(const CDate& rRHS) const;
	bool operator !=(const CDate& rRHS) const;
	bool operator  <(const CDate& rRHS) const;
	bool operator  >(const CDate& rRHS) const;
	bool operator <=(const CDate& rRHS) const;
	bool operator >=(const CDate& rRHS) const;

	//
	// Arithmetic operators.
	//
	CDateSpan operator -(const CDate& rRHS) const;

	void operator +=(const CDateSpan& rRHS);
	void operator -=(const CDateSpan& rRHS);

	//
	// Persistance.
	//
	void operator <<(CStream& rStream);
	void operator >>(CStream& rStream) const;
	
protected:
	//
	// Members.
	//
	int32	m_lDate;	// The date in days since 01/01/1901.

	//
	// Internal methods.
	//
	int DaysInMonth(int iMonth, int iYear) const;

	//
	// Friends.
	//
	friend class CDateSpan;
};

/******************************************************************************
** 
** This class is used to represent a period between two dates.
**
*******************************************************************************
*/

class CDateSpan
{
public:
	//
	// Constructors/Destructor.
	//
	CDateSpan();
	CDateSpan(int iDays);
	CDateSpan(const CDate& rDate);
	
	// Accessors.
	int Days() const;

protected:
	//
	// Members.
	//
	int32	m_lSpan;	// The span in days.

	//
	// Friends.
	//
	friend class CDate;
};

/******************************************************************************
**
** Implementation of CDate inline functions.
**
*******************************************************************************
*/

inline CDate::CDate()
	: m_lDate(0)
{
}

inline CDate::CDate(int iDay, int iMonth, int iYear)
{
	Set(iDay, iMonth, iYear);
}

inline CDate CDate::Min()
{
	return CDate(1, 1, 1901);
}

inline CDate CDate::Max()
{
	return CDate(31, 12, 2099);
}

inline void CDate::Day(int iDay)
{
	int iOldDay, iMonth, iYear;

	Get(iOldDay, iMonth, iYear);
	Set(iDay, iMonth, iYear);
}

inline int CDate::Day() const
{
	int iDay, iMonth, iYear;

	Get(iDay, iMonth, iYear);

	return iDay;
}

inline void CDate::Month(int iMonth)
{
	int iDay, iOldMonth, iYear;

	Get(iDay, iOldMonth, iYear);
	Set(iDay, iMonth, iYear);
}

inline int CDate::Month() const
{
	int iDay, iMonth, iYear;

	Get(iDay, iMonth, iYear);

	return iMonth;
}

inline void CDate::Year(int iYear)
{
	int iDay, iMonth, iOldYear;

	Get(iDay, iMonth, iOldYear);
	Set(iDay, iMonth, iYear);
}

inline int CDate::Year() const
{
	int iDay, iMonth, iYear;

	Get(iDay, iMonth, iYear);

	return iYear;
}

inline int CDate::DayOfWeek() const
{
	return ((m_lDate + 1) % 7);
}

inline int CDate::DaysInMonth() const
{
	int iDay, iMonth, iYear;

	Get(iDay, iMonth, iYear);

	return DaysInMonth(iMonth, iYear);
}

inline bool CDate::operator ==(const CDate& rRHS) const
{
	return (m_lDate == rRHS.m_lDate);
}

inline bool CDate::operator !=(const CDate& rRHS) const
{
	return (m_lDate != rRHS.m_lDate);
}

inline bool CDate::operator <(const CDate& rRHS) const
{
	return (m_lDate < rRHS.m_lDate);
}

inline bool CDate::operator >(const CDate& rRHS) const
{
	return (m_lDate > rRHS.m_lDate);
}

inline bool CDate::operator <=(const CDate& rRHS) const
{
	return ((*this < rRHS) || (*this == rRHS));
}

inline bool CDate::operator >=(const CDate& rRHS) const
{
	return ((*this > rRHS) || (*this == rRHS));
}

inline CDateSpan CDate::operator -(const CDate& rRHS) const
{
	return CDateSpan(m_lDate - rRHS.m_lDate);
}

inline void CDate::operator +=(const CDateSpan& rRHS)
{
	m_lDate += rRHS.m_lSpan;
}

inline void CDate::operator -=(const CDateSpan& rRHS)
{
	m_lDate -= rRHS.m_lSpan;
}

/******************************************************************************
**
** Implementation of CDateSpan inline functions.
**
*******************************************************************************
*/

inline CDateSpan::CDateSpan()
	: m_lSpan(0)
{
}

inline CDateSpan::CDateSpan(int iDays)
	: m_lSpan(iDays)
{
}

inline CDateSpan::CDateSpan(const CDate& rDate)
	: m_lSpan(rDate.m_lDate)
{
}

inline int CDateSpan::Days() const
{
	return m_lSpan;
}

#endif //DATE_HPP
