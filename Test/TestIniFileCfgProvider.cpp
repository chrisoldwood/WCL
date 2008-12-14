////////////////////////////////////////////////////////////////////////////////
//! \file   TestIniFileCfgProvider.cpp
//! \brief  The unit tests for the IniFileCfgProvider class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/IniFileCfgProvider.hpp>
#include <WCL/File.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the IniFileCfgProvider class.

void TestIniFileCfgProvider()
{
	tstring publisher   = TXT("Chris Oldwood");
	tstring application = TXT("Unit Tests");
	CIniFile iniFile;

	CFile::Delete(iniFile.m_strPath);
	ASSERT(!iniFile.m_strPath.Exists());

	TEST_FALSE(WCL::IniFileCfgProvider::isAvailable());

	CString testData = TXT("[Section]\r\nKey=Value");
	CFile::WriteTextFile(iniFile.m_strPath, testData, ANSI_TEXT);

	TEST_TRUE(WCL::IniFileCfgProvider::isAvailable());

	WCL::IniFileCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));

	provider.writeString(TXT("Section2"), TXT("Key2"), TXT("Value2"));
	
	TEST_TRUE(provider.readString(TXT("Section2"), TXT("Key2"), TXT("default")) == TXT("Value2"));

	provider.deleteSection(TXT("Section2"));

	TEST_FALSE(provider.readString(TXT("Section2"), TXT("Key2"), TXT("default")) == TXT("Value2"));

	CFile::Delete(iniFile.m_strPath);
	ASSERT(!iniFile.m_strPath.Exists());
}
