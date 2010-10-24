////////////////////////////////////////////////////////////////////////////////
//! \file   DateTests.cpp
//! \brief  The unit tests for the CDate class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/Date.hpp>

TEST_SET(Date)
{
	CDate oDate(1, 2, 2003);

	TEST_TRUE(oDate.ToString(CDate::FMT_ISO)       == TXT("2003-02-01"));
	TEST_TRUE(oDate.ToString(CDate::FMT_WIN_SHORT) == TXT("01/02/2003"));
	TEST_TRUE(oDate.ToString(CDate::FMT_WIN_LONG)  == TXT("01 February 2003"));
}
TEST_SET_END
