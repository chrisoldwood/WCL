////////////////////////////////////////////////////////////////////////////////
//! \file   DateTimeTests.cpp
//! \brief  The unit tests for the CDateTime class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/DateTime.hpp>

TEST_SET(DateTime)
{
	CDateTime testDateTime(CDate(1, 2, 2003), CTime(1, 2, 3));

TEST_CASE("using ISO format outputs an ISO date and time separated by a 'T'")
{
	TEST_TRUE(testDateTime.ToString(CDate::FMT_ISO, CTime::FMT_ISO) == TXT("2003-02-01T01:02:03"));
}
TEST_CASE_END

TEST_CASE("using Windows short format ouputs a short date and time separated by a space")
{
	TEST_TRUE(testDateTime.ToString(CDate::FMT_WIN_SHORT, CTime::FMT_WIN_SHORT) == TXT("01/02/2003 01:02"));
}
TEST_CASE_END

}
TEST_SET_END
