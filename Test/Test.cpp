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

////////////////////////////////////////////////////////////////////////////////
//! The entry point for the test harness.

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
#ifdef _DEBUG
	Core::EnableLeakReporting(true);
#endif

	try
	{
		TestMisc();
		TestString();
		TestDateAndTime();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	Core::WriteTestsSummary();

	return Core::GetTestProcessResult();
}
