////////////////////////////////////////////////////////////////////////////////
//! \file   TestTime.cpp
//! \brief  The unit tests for the CTime class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/Time.hpp>

TEST_SET(Time)
{
	CTime oTime(1, 2, 3);

	TEST_TRUE(oTime.ToString(CTime::FMT_ISO)       == TXT("01:02:03"));
	TEST_TRUE(oTime.ToString(CTime::FMT_WIN_SHORT) == TXT("01:02"));
	TEST_TRUE(oTime.ToString(CTime::FMT_WIN_LONG)  == TXT("01:02:03"));
}
TEST_SET_END
