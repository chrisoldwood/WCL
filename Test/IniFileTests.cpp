////////////////////////////////////////////////////////////////////////////////
//! \file   IniFileTests.cpp
//! \brief  The unit tests for the IniFile class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/IniFile.hpp>

TEST_SET(IniFile)
{

TEST_CASE("default construction refers to a file with the name of the process and an .ini extension")
{
	const tchar* processName = TXT("test");
	const CPath  folder = CPath::ApplicationDir();

	tstring expected = Core::fmt(TXT("%s\\%s.ini"), folder.c_str(), processName);

	CIniFile oIniFile;

	TEST_TRUE(tstricmp(expected.c_str(), oIniFile.m_strPath) == 0);
}
TEST_CASE_END

}
TEST_SET_END
