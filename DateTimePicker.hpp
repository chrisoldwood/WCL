/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATETIMEPICKER.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDateTimePicker class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef DATETIMEPICKER_HPP
#define DATETIMEPICKER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"
#include "Date.hpp"
#include <commctrl.h>

/******************************************************************************
** 
** This is a date-time picker control.
**
*******************************************************************************
*/

class CDateTimePicker : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CDateTimePicker();

	//
	// Standard methods.
	//
	void  SetDate(const CDate& rDate);
	CDate GetDate();

	void SetDateRange(const CDate& rMin, const CDate& rMax);
	void GetDateRange(CDate& rMin, CDate& rMax);

	void  SetTime(const CTime& rTime);
	CTime GetTime();

	void SetTimeRange(const CTime& rMin, const CTime& rMax);
	void GetTimeRange(CTime& rMin, CTime& rMax);

	void SetDateTime(const CDateTime& rDateTime);
	CDateTime GetDateTime();

	void SetDateTimeRange(const CDateTime& rMin, const CDateTime& rMax);
	void GetDateTimeRange(CDateTime& rMin, CDateTime& rMax);

	void Format(const char* pszFormat);

protected:
	//
	// Members.
	//
	
	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CDateTimePicker::Format(const char* pszFormat)
{
	DateTime_SetFormat(m_hWnd, pszFormat);
}

#endif //DATETIMEPICKER_HPP
