////////////////////////////////////////////////////////////////////////////////
//! \file   IniFileCfgProviderTests.cpp
//! \brief  The unit tests for the IniFileCfgProvider class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/IniFileCfgProvider.hpp>
#include <WCL/File.hpp>

TEST_SET(IniFileCfgProvider)
{
	const tstring publisher   = TXT("Chris Oldwood");
	const tstring application = TXT("Unit Tests");

TEST_CASE_SETUP()
{
	CIniFile iniFile;

	ASSERT(!iniFile.m_strPath.Exists());

	CString testData = TXT("[Section]\r\nKey=Value");
	CFile::WriteTextFile(iniFile.m_strPath, testData, ANSI_TEXT);
}
TEST_CASE_SETUP_END

TEST_CASE_TEARDOWN()
{
	CIniFile iniFile;

	CFile::Delete(iniFile.m_strPath);
}
TEST_CASE_TEARDOWN_END

TEST_CASE("configuration data exists when the .ini file exists")
{
	TEST_TRUE(WCL::IniFileCfgProvider::isAvailable());

	CFile::Delete(CIniFile().m_strPath);

	TEST_FALSE(WCL::IniFileCfgProvider::isAvailable());
}
TEST_CASE_END

TEST_CASE("reading the value for a key when it exists returns the value")
{
	WCL::IniFileCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));
}
TEST_CASE_END

TEST_CASE("reading the value for a key when it doesn't exist returns the default value")
{
	WCL::IniFileCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Invalid"), TXT("Invalid"), TXT("default")) == TXT("default"));
}
TEST_CASE_END

TEST_CASE("writing the value for a new section and key creates the section and key")
{
	WCL::IniFileCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Section2"), TXT("Key2"), TXT("default")) == TXT("default"));

	provider.writeString(TXT("Section2"), TXT("Key2"), TXT("Value2"));
	
	TEST_TRUE(provider.readString(TXT("Section2"), TXT("Key2"), TXT("default")) == TXT("Value2"));
}
TEST_CASE_END

TEST_CASE("deleting a section removes all entries in that section")
{
	WCL::IniFileCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));

	provider.deleteSection(TXT("Section"));

	TEST_FALSE(provider.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));
}
TEST_CASE_END

}
TEST_SET_END
