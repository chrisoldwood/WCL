/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDate class declarations.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_DATE_HPP
#define WCL_DATE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "DateSpan.hpp"
#include "Time.hpp"

// Forward declarations.
class CDateTime;

namespace WCL
{
class IInputStream;
class IOutputStream;
}

/******************************************************************************
** 
** This class is used to represent a date. It is stored and manipulated as if
** it was a UTC time_t, with the time part set to midnight.
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
	CDate(WCL::Seconds tSecs);
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
	void Set(WCL::Seconds tSecs);
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

	WCL::Seconds GetDateInSecs() const;

	static CDate Current();

	//
	// Date string ordering (See LOCALE_IDATE).
	//
	enum DateOrder
	{
		MONTH_DAY_YEAR	= 0x0000,
		DAY_MONTH_YEAR	= 0x0001,
		YEAR_MONTH_DAY	= 0x0002,
	};

	//
	// Date string formats.
	//
	enum Format
	{
		FMT_ISO			= 0x0001,		// ISO standard format (YYYY-MM-DD).
		FMT_WIN_SHORT	= 0x0002,		// Windows locale short format (e.g. DD/MM/YYYY).
		FMT_WIN_LONG	= 0x0003,		// Windows locale long format (e.g. DD MONTH YYYY).
	};

	//
	// Locale information.
	//
	static DateOrder DateFormatOrder();
	static CString   FieldSeparator();
	static CString   DayOfWeekName(int nDay, bool bFullName = true);
	static CString   MonthName(int nMonth, bool bFullName = true);

	//
	// Conversion methods.
	//
	CString DayOfWeekStr(bool bFullName) const;
	CString MonthStr(bool bFullName) const;
	CString ToString(int nFormat = FMT_WIN_SHORT) const;
	bool    FromString(const tchar* pszDate);

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

protected:
	//
	// Members.
	//
	WCL::Seconds	m_tDate;

	//
	// Internal methods.
	//
	int DaysInMonth(int iMonth, int iYear) const;

	//
	// Friends.
	//
	friend class CDateSpan;
	friend class CDateTime;

	//
	// Persistance.
	//
	friend void operator >>(WCL::IInputStream&  rStream, CDate& rDate);
	friend void operator <<(WCL::IOutputStream& rStream, const CDate& rDate);
};

/******************************************************************************
**
** Implementation of CDate inline functions.
**
*******************************************************************************
*/

inline CDate::CDate()
	: m_tDate(0)
{
}

inline CDate::CDate(WCL::Seconds tDate)
{
	Set(tDate);
}

inline CDate::CDate(int iDay, int iMonth, int iYear)
{
	Set(iDay, iMonth, iYear);
}

inline CDate CDate::Min()
{
	return CDate(1, 1, 1970);
}

inline CDate CDate::Max()
{
	return CDate(1, 1, 2038);
}

inline void CDate::Set(WCL::Seconds tDate)
{
	m_tDate = (tDate - (tDate % WCL::SECS_PER_DAY));
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
	return static_cast<int>(((m_tDate / WCL::SECS_PER_DAY) + 3) % 7);
}

inline int CDate::DaysInMonth() const
{
	int iDay, iMonth, iYear;

	Get(iDay, iMonth, iYear);

	return DaysInMonth(iMonth, iYear);
}

inline WCL::Seconds CDate::GetDateInSecs() const
{
	return m_tDate;
}

inline bool CDate::operator ==(const CDate& rRHS) const
{
	return (m_tDate == rRHS.m_tDate);
}

inline bool CDate::operator !=(const CDate& rRHS) const
{
	return (m_tDate != rRHS.m_tDate);
}

inline bool CDate::operator <(const CDate& rRHS) const
{
	return (m_tDate < rRHS.m_tDate);
}

inline bool CDate::operator >(const CDate& rRHS) const
{
	return (m_tDate > rRHS.m_tDate);
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
	return CDateSpan(static_cast<int>((m_tDate - rRHS.m_tDate) / WCL::SECS_PER_DAY));
}

inline void CDate::operator +=(const CDateSpan& rRHS)
{
	m_tDate += (rRHS.m_nSpan * WCL::SECS_PER_DAY);
}

inline void CDate::operator -=(const CDateSpan& rRHS)
{
	m_tDate -= (rRHS.m_nSpan * WCL::SECS_PER_DAY);
}

#endif // WCL_DATE_HPP
