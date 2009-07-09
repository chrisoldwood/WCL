/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATETIMEPICKER.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDateTimePicker class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "DateTimePicker.hpp"
#include "DateTime.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Does nothing.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDateTimePicker::CDateTimePicker()
{
}

/******************************************************************************
** Method:		GetCreateParams()
**
** Description:	Template method to get the window creation data.
**
** Parameters:	rParams		The create structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDateTimePicker::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = DATETIMEPICK_CLASS;
	rParams.dwStyle     |= DTS_SHORTDATEFORMAT;
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Set the range.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDateTimePicker::OnCreate(const CRect&)
{
	SetDateTimeRange(CDateTime::Min(), CDateTime::Max());
}

/******************************************************************************
** Methods:		SetDate()
**				GetDate()
**
** Description:	Set/Get the date to/from the control.
**
** Parameters:	rDate		The date to set the control to.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDateTimePicker::SetDate(const CDate& rDate)
{
	SYSTEMTIME	SysTime;
	int			nDay, nMonth, nYear;

	// Extract date components.
	rDate.Get(nDay, nMonth, nYear);

	// Initialise date part.
	SysTime.wDay       = static_cast<WORD>(nDay);
	SysTime.wMonth     = static_cast<WORD>(nMonth);
	SysTime.wYear      = static_cast<WORD>(nYear);
	SysTime.wDayOfWeek = 0;

	// Set time part to midnight.
	SysTime.wHour         = 0;
	SysTime.wMinute       = 0;
	SysTime.wSecond       = 0;
	SysTime.wMilliseconds = 0;

	// Set the date in the control.
	DateTime_SetSystemtime(m_hWnd, GDT_VALID, &SysTime);
}

CDate CDateTimePicker::GetDate()
{
	SYSTEMTIME	SysTime;

	// Get the date from the control.
	DateTime_GetSystemtime(m_hWnd, &SysTime);

	return CDate(SysTime.wDay, SysTime.wMonth, SysTime.wYear);
}

/******************************************************************************
** Methods:		SetDateRange()
**				GetDateRange()
**
** Description:	Set/Get the range of dates to/from the control.
**
** Parameters:	rMin, rMax		The date range to set the control to OR
**								The output parameters to return the range in.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDateTimePicker::SetDateRange(const CDate& rMin, const CDate& rMax)
{
	SYSTEMTIME	SysTime[2] = { { 0 }, { 0 } };
	int			nDay, nMonth, nYear;

	// Set time parts to 00:00:00.
	SysTime[0].wHour         = SysTime[1].wHour         = 0;
	SysTime[0].wMinute       = SysTime[1].wMinute       = 0;
	SysTime[0].wSecond       = SysTime[1].wSecond       = 0;
	SysTime[0].wMilliseconds = SysTime[1].wMilliseconds = 0;

	// Extract min date components.
	rMin.Get(nDay, nMonth, nYear);

	// Initialise min date part.
	SysTime[0].wDay       = static_cast<WORD>(nDay);
	SysTime[0].wMonth     = static_cast<WORD>(nMonth);
	SysTime[0].wYear      = static_cast<WORD>(nYear);
	SysTime[0].wDayOfWeek = 0;

	// Extract max date components.
	rMax.Get(nDay, nMonth, nYear);

	// Initialise max date part.
	SysTime[1].wDay       = static_cast<WORD>(nDay);
	SysTime[1].wMonth     = static_cast<WORD>(nMonth);
	SysTime[1].wYear      = static_cast<WORD>(nYear);
	SysTime[1].wDayOfWeek = 0;

	// Set the date range in the control.
	DateTime_SetRange(m_hWnd, GDTR_MIN | GDTR_MAX, SysTime);
}

void CDateTimePicker::GetDateRange(CDate& rMin, CDate& rMax)
{
	SYSTEMTIME	SysTime[2] = { { 0 }, { 0 } };

	// Get the date range from the control.
	DateTime_GetRange(m_hWnd, SysTime);

	// Fill in return parameters.
	rMin.Set(SysTime[0].wDay, SysTime[0].wMonth, SysTime[0].wYear);
	rMax.Set(SysTime[1].wDay, SysTime[1].wMonth, SysTime[1].wYear);
}

/******************************************************************************
** Methods:		SetTime()
**				GetTime()
**
** Description:	Set/Get the time to/from the control.
**
** Parameters:	rTime		The time to set the control to.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDateTimePicker::SetTime(const CTime& rTime)
{
	SYSTEMTIME	SysTime;
	int			nHours, nMins, nSecs;

	// Extract time components.
	rTime.Get(nHours, nMins, nSecs);

	// Set date part to 01/01/2000.
	SysTime.wDay       = 1;
	SysTime.wMonth     = 1;
	SysTime.wYear      = 2000;
	SysTime.wDayOfWeek = 0;

	// Initialise time part.
	SysTime.wHour         = static_cast<WORD>(nHours);
	SysTime.wMinute       = static_cast<WORD>(nMins);
	SysTime.wSecond       = static_cast<WORD>(nSecs);
	SysTime.wMilliseconds = 0;

	// Set the time in the control.
	DateTime_SetSystemtime(m_hWnd, GDT_VALID, &SysTime);
}

CTime CDateTimePicker::GetTime()
{
	SYSTEMTIME	SysTime;

	// Get the time from the control.
	DateTime_GetSystemtime(m_hWnd, &SysTime);

	return CTime(SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
}

/******************************************************************************
** Methods:		SetTimeRange()
**				GetTimeRange()
**
** Description:	Set/Get the range of times to/from the control.
**
** Parameters:	rMin, rMax		The time range to set the control to OR
**								The output parameters to return the range in.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDateTimePicker::SetTimeRange(const CTime& rMin, const CTime& rMax)
{
	SYSTEMTIME	SysTime[2] = { { 0 }, { 0 } };
	int			nHours, nMins, nSecs;

	// Set date parts to 01/01/2000.
	SysTime[0].wDay       = SysTime[1].wDay       = 1;
	SysTime[0].wMonth     = SysTime[1].wMonth     = 1;
	SysTime[0].wYear      = SysTime[1].wYear      = 2000;
	SysTime[0].wDayOfWeek = SysTime[1].wDayOfWeek = 0;

	// Extract min time components.
	rMin.Get(nHours, nMins, nSecs);

	// Initialise min time part.
	SysTime[0].wHour         = static_cast<WORD>(nHours);
	SysTime[0].wMinute       = static_cast<WORD>(nMins);
	SysTime[0].wSecond       = static_cast<WORD>(nSecs);
	SysTime[0].wMilliseconds = 0;

	// Extract max time components.
	rMax.Get(nHours, nMins, nSecs);

	// Initialise max time part.
	SysTime[1].wHour         = static_cast<WORD>(nHours);
	SysTime[1].wMinute       = static_cast<WORD>(nMins);
	SysTime[1].wSecond       = static_cast<WORD>(nSecs);
	SysTime[1].wMilliseconds = 0;

	// Set the time range in the control.
	DateTime_SetRange(m_hWnd, GDTR_MIN | GDTR_MAX, SysTime);
}

void CDateTimePicker::GetTimeRange(CTime& rMin, CTime& rMax)
{
	SYSTEMTIME	SysTime[2] = { { 0 }, { 0 } };

	// Get the time range from the control.
	DateTime_GetRange(m_hWnd, SysTime);

	// Fill in return parameters.
	rMin.Set(SysTime[0].wHour, SysTime[0].wMinute, SysTime[0].wSecond);
	rMax.Set(SysTime[1].wHour, SysTime[1].wMinute, SysTime[1].wSecond);
}

/******************************************************************************
** Methods:		SetDateTime()
**				GetDateTime()
**
** Description:	Set/Get the datetime to/from the control.
**
** Parameters:	rDate		The datetime to set the control to.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDateTimePicker::SetDateTime(const CDateTime& rDateTime)
{
	SYSTEMTIME	SysTime;
	int			nDay,   nMonth, nYear;
	int			nHours, nMins,  nSecs;

	// Extract datetime components.
	rDateTime.Get(nDay, nMonth, nYear, nHours, nMins, nSecs);

	// Initialise datetime parts
	SysTime.wDay          = static_cast<WORD>(nDay);
	SysTime.wMonth        = static_cast<WORD>(nMonth);
	SysTime.wYear         = static_cast<WORD>(nYear);
	SysTime.wDayOfWeek    = 0;
	SysTime.wHour         = static_cast<WORD>(nHours);
	SysTime.wMinute       = static_cast<WORD>(nMins);
	SysTime.wSecond       = static_cast<WORD>(nSecs);
	SysTime.wMilliseconds = 0;

	// Set the time in the control.
	DateTime_SetSystemtime(m_hWnd, GDT_VALID, &SysTime);
}

CDateTime CDateTimePicker::GetDateTime()
{
	SYSTEMTIME	SysTime;

	// Get the datetime from the control.
	DateTime_GetSystemtime(m_hWnd, &SysTime);

	return CDateTime(SysTime.wDay, SysTime.wMonth, SysTime.wYear, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
}

/******************************************************************************
** Methods:		SetDateTimeRange()
**				GetDateTimeRange()
**
** Description:	Set/Get the range of datetimes to/from the control.
**
** Parameters:	rMin, rMax		The range to set the control to OR
**								The output parameters to return the range in.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDateTimePicker::SetDateTimeRange(const CDateTime& rMin, const CDateTime& rMax)
{
	SYSTEMTIME	SysTime[2] = { { 0 }, { 0 } };
	int			nDay,   nMonth, nYear;
	int			nHours, nMins,  nSecs;

	// Extract min datetime components.
	rMin.Get(nDay, nMonth, nYear, nHours, nMins, nSecs);

	// Initialise min datetime part.
	SysTime[0].wDay          = static_cast<WORD>(nDay);
	SysTime[0].wMonth        = static_cast<WORD>(nMonth);
	SysTime[0].wYear         = static_cast<WORD>(nYear);
	SysTime[0].wDayOfWeek    = 0;
	SysTime[0].wHour         = static_cast<WORD>(nHours);
	SysTime[0].wMinute       = static_cast<WORD>(nMins);
	SysTime[0].wSecond       = static_cast<WORD>(nSecs);
	SysTime[0].wMilliseconds = 0;

	// Extract max datetime components.
	rMax.Get(nDay, nMonth, nYear, nHours, nMins, nSecs);

	// Initialise max datetime part.
	SysTime[1].wDay          = static_cast<WORD>(nDay);
	SysTime[1].wMonth        = static_cast<WORD>(nMonth);
	SysTime[1].wYear         = static_cast<WORD>(nYear);
	SysTime[1].wDayOfWeek    = 0;
	SysTime[1].wHour         = static_cast<WORD>(nHours);
	SysTime[1].wMinute       = static_cast<WORD>(nMins);
	SysTime[1].wSecond       = static_cast<WORD>(nSecs);
	SysTime[1].wMilliseconds = 0;

	// Set the time range in the control.
	DateTime_SetRange(m_hWnd, GDTR_MIN | GDTR_MAX, SysTime);
}

void CDateTimePicker::GetDateTimeRange(CDateTime& rMin, CDateTime& rMax)
{
	SYSTEMTIME	SysTime[2] = { { 0 }, { 0 } };

	// Get the time range from the control.
	DateTime_GetRange(m_hWnd, SysTime);

	// Fill in return parameters.
	rMin.Set(SysTime[0].wDay, SysTime[0].wMonth, SysTime[0].wYear, SysTime[0].wHour, SysTime[0].wMinute, SysTime[0].wSecond);
	rMax.Set(SysTime[1].wDay, SysTime[1].wMonth, SysTime[1].wYear, SysTime[1].wHour, SysTime[1].wMinute, SysTime[1].wSecond);
}
