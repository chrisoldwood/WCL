////////////////////////////////////////////////////////////////////////////////
//! \file   DateTimeTests.cpp
//! \brief  The unit tests for the CDateTime class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/DateTime.hpp>

TEST_SET(DateTime)
{
	CDateTime oDateTime(CDate(1, 2, 2003), CTime(1, 2, 3));

	TEST_TRUE(oDateTime.ToString(CDate::FMT_ISO,       CTime::FMT_ISO)       == TXT("2003-02-01T01:02:03"));
	TEST_TRUE(oDateTime.ToString(CDate::FMT_WIN_SHORT, CTime::FMT_WIN_SHORT) == TXT("01/02/2003 01:02"));
}
TEST_SET_END
