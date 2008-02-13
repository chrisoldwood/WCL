////////////////////////////////////////////////////////////////////////////////
//! \file   TestDateTime.cpp
//! \brief  The unit tests for the CDate, CTime & CDateTime classes.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/Date.hpp>
#include <WCL/Time.hpp>
#include <WCL/DateTime.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the CDate class.

static void TestDate()
{
	CDate oDate(1, 2, 2003);

	TEST_TRUE(oDate.ToString(CDate::FMT_ISO)       == TXT("2003-02-01"));
	TEST_TRUE(oDate.ToString(CDate::FMT_WIN_SHORT) == TXT("01/02/2003"));
	TEST_TRUE(oDate.ToString(CDate::FMT_WIN_LONG)  == TXT("01 February 2003"));
}

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the CTime class.

static void TestTime()
{
	CTime oTime(1, 2, 3);

	TEST_TRUE(oTime.ToString(CTime::FMT_ISO)       == TXT("01:02:03"));
	TEST_TRUE(oTime.ToString(CTime::FMT_WIN_SHORT) == TXT("01:02"));
	TEST_TRUE(oTime.ToString(CTime::FMT_WIN_LONG)  == TXT("01:02:03"));
}

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the CDateTime class.

static void TestDateTime()
{
	CDateTime oDateTime(CDate(1, 2, 2003), CTime(1, 2, 3));

	TEST_TRUE(oDateTime.ToString(CDate::FMT_ISO,       CTime::FMT_ISO)       == TXT("2003-02-01T01:02:03"));
	TEST_TRUE(oDateTime.ToString(CDate::FMT_WIN_SHORT, CTime::FMT_WIN_SHORT) == TXT("01/02/2003 01:02"));
}

////////////////////////////////////////////////////////////////////////////////
//! The function for running the sub tests.

void TestDateAndTime()
{
	TestDate();
	TestTime();
	TestDateTime();
}
