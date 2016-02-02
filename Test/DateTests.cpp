////////////////////////////////////////////////////////////////////////////////
//! \file   DateTests.cpp
//! \brief  The unit tests for the CDate class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/Date.hpp>

TEST_SET(Date)
{
	CDate testDate(1, 2, 2003);

TEST_CASE("using ISO format outputs year, month and day separated by a dash")
{
	TEST_TRUE(testDate.ToString(CDate::FMT_ISO) == TXT("2003-02-01"));
}
TEST_CASE_END

TEST_CASE("using Windows short format outputs day, month and year separated by a slash")
{
	TEST_TRUE(testDate.ToString(CDate::FMT_WIN_SHORT) == TXT("01/02/2003"));
}
TEST_CASE_END

TEST_CASE("using Windows long format day, month name and year separated by a space")
{
	TEST_TRUE(testDate.ToString(CDate::FMT_WIN_LONG) == TXT("01 February 2003"));
}
TEST_CASE_END

}
TEST_SET_END
