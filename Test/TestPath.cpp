////////////////////////////////////////////////////////////////////////////////
//! \file   TestPath.cpp
//! \brief  The unit tests for the CPath class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/Path.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the CPath class.

void TestPath()
{
{
	TEST_TRUE(CPath().Empty());
	TEST_TRUE(CPath().Length() == 0);
	TEST_TRUE(CPath() == TXT(""));
	TEST_TRUE(CPath(TXT("\\")) == TXT("\\"));
	TEST_TRUE(CPath(TXT("C:\\")) == TXT("C:\\"));
	TEST_TRUE(CPath(TXT("C:\\Temp\\")) == TXT("C:\\Temp"));
	TEST_TRUE(CPath(CString(TXT("C:\\Temp\\"))) == TXT("C:\\Temp"));
	TEST_TRUE(CPath(TXT("C:\\"), TXT("Temp\\")) == TXT("C:\\Temp"));
}
{
	CPath path;

	path = TXT("C:\\");
	TEST_TRUE(path == TXT("C:\\"));
	path = TXT("C:\\Temp\\");
	TEST_TRUE(path == TXT("C:\\Temp"));
	path = CString(TXT("C:\\Temp\\"));
	TEST_TRUE(path == TXT("C:\\Temp"));
}
}
