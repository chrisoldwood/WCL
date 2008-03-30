////////////////////////////////////////////////////////////////////////////////
//! \file   Test.cpp
//! \brief  The test harness entry point.
//! \author Chris Oldwood

#include "stdafx.h"
#include <tchar.h>
#include <Core/UnitTest.hpp>

////////////////////////////////////////////////////////////////////////////////
// The test group functions.

extern void TestMisc();
extern void TestString();
extern void TestDateAndTime();
extern void TestIFacePtr();
extern void TestComPtr();

////////////////////////////////////////////////////////////////////////////////
//! The entry point for the test harness.

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	TEST_SUITE_BEGIN
	{
		TestMisc();
		TestString();
		TestDateAndTime();
		TestIFacePtr();
		TestComPtr();

		Core::SetTestRunFinalStatus(true);
	}
	TEST_SUITE_END
}
