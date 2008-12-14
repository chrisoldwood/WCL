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
extern void TestStringUtils();
extern void TestDateAndTime();
extern void TestIFacePtr();
extern void TestComPtr();
extern void TestVerInfoReader();
extern void TestIniFile();
extern void TestRect();
extern void TestFolderIterator();
extern void TestIniFileCfgProvider();
extern void TestRegistryCfgProvider();
extern void TestAppConfig();

////////////////////////////////////////////////////////////////////////////////
//! The entry point for the test harness.

int _tmain(int argc, _TCHAR* argv[])
{
	TEST_SUITE_BEGIN(argc, argv)
	{
		TEST_CASE(TestMisc);
		TEST_CASE(TestString);
		TEST_CASE(TestStringUtils);
		TEST_CASE(TestDateAndTime);
		TEST_CASE(TestIFacePtr);
		TEST_CASE(TestComPtr);
		TEST_CASE(TestVerInfoReader);
		TEST_CASE(TestIniFile);
		TEST_CASE(TestRect);
		TEST_CASE(TestFolderIterator);
		TEST_CASE(TestIniFileCfgProvider);
		TEST_CASE(TestRegistryCfgProvider);
		TEST_CASE(TestAppConfig);

		Core::SetTestRunFinalStatus(true);
	}
	TEST_SUITE_END
}
