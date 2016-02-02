////////////////////////////////////////////////////////////////////////////////
//! \file   TimeTests.cpp
//! \brief  The unit tests for the CTime class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/Time.hpp>

TEST_SET(Time)
{
	CTime testTime(1, 2, 3);

TEST_CASE("using ISO format outputs hours, minutes and seconds separated by a colon")
{
	TEST_TRUE(testTime.ToString(CTime::FMT_ISO) == TXT("01:02:03"));
}
TEST_CASE_END

TEST_CASE("using Windows short format outputs hours and minutes only separated by a colon")
{
	TEST_TRUE(testTime.ToString(CTime::FMT_WIN_SHORT) == TXT("01:02"));
}
TEST_CASE_END

TEST_CASE("using Windows long format outputs hours, minutes and seconds separated by a colon")
{
	TEST_TRUE(testTime.ToString(CTime::FMT_WIN_LONG) == TXT("01:02:03"));
}
TEST_CASE_END

}
TEST_SET_END
