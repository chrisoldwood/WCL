////////////////////////////////////////////////////////////////////////////////
//! \file   TestAppConfig.cpp
//! \brief  The unit tests for the AppConfig class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/AppConfig.hpp>
#include <WCL/RegKey.hpp>
#include <Core/StringUtils.hpp>
#include <WCL/IniFile.hpp>
#include <WCL/File.hpp>

TEST_SET(AppConfig)
{
	HKEY    rootKey     = HKEY_CURRENT_USER;
	tstring publisher   = TXT("Chris Oldwood");
	tstring pubPath     = Core::fmt(TXT("Software\\%s"), publisher.c_str());
	tstring application = TXT("Unit Tests");
	tstring appPath     = Core::fmt(TXT("Software\\%s\\%s"), publisher.c_str(), application.c_str());

	WCL::RegKey::DeleteTree(rootKey, appPath.c_str());
	ASSERT(!WCL::RegKey::Exists(rootKey, appPath.c_str()));

	CIniFile iniFile;
	CFile::Delete(iniFile.m_strPath);
	ASSERT(!iniFile.m_strPath.Exists());
{
	WCL::AppConfig appConfig(publisher, application);

	TEST_TRUE(appConfig.getStorageType() == WCL::AppConfig::REGISTRY);

	appConfig.writeString(TXT("Section"), TXT("Key"), TXT("Value"));

	TEST_TRUE(WCL::RegKey::ReadKeyStringValue(HKEY_CURRENT_USER, (appPath + TXT("\\Section")).c_str(), TXT("Key"), TXT("default")) == TXT("Value"));

	appConfig.writeString(WCL::AppConfig::DEFAULT_SECTION, TXT("Key2"), TXT("Value2"));

	TEST_TRUE(WCL::RegKey::ReadKeyStringValue(HKEY_CURRENT_USER, appPath.c_str(), TXT("Key2"), TXT("default")) == TXT("Value2"));
}
{
	WCL::AppConfig appConfig(publisher, application);

	TEST_TRUE(appConfig.getStorageType() == WCL::AppConfig::REGISTRY);

	TEST_TRUE(appConfig.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));
}
{
	WCL::AppConfig appConfig(publisher, application);

	appConfig.setStorageType(WCL::AppConfig::INIFILE);

	TEST_TRUE(WCL::RegKey::Exists(rootKey, pubPath.c_str()) && !WCL::RegKey::Exists(rootKey, appPath.c_str()));

	appConfig.writeString(TXT("Section"), TXT("Key"), TXT("Value"));

	TEST_TRUE(iniFile.ReadString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));

	appConfig.writeString(WCL::AppConfig::DEFAULT_SECTION, TXT("Key2"), TXT("Value2"));

	TEST_TRUE(iniFile.ReadString(application, TXT("Key2"), TXT("default")) == TXT("Value2"));

	appConfig.setStorageType(WCL::AppConfig::REGISTRY);

	TEST_TRUE(!iniFile.m_strPath.Exists());
}
{
	WCL::AppConfig appConfig(publisher, application);

	const size_t value    = 1234;
	const size_t defValue = 5678;

	TEST_TRUE(appConfig.readValue<size_t>(TXT("Section"), TXT("Name"), defValue) == defValue);

	appConfig.writeValue<size_t>(TXT("Section"), TXT("Name"), value);

	TEST_TRUE(appConfig.readValue<size_t>(TXT("Section"), TXT("Name"), defValue) == value);
}
{
	WCL::AppConfig appConfig(publisher, application);

	WCL::AppConfig::StringArray list;

	list.push_back(TXT("1234"));
	list.push_back(TXT("5678"));

	appConfig.writeList(TXT("Section"), TXT("List"), list);

	WCL::AppConfig::StringArray result;

	appConfig.readList(TXT("Section"), TXT("List"), TXT(""), result);

	TEST_TRUE(result == list);

	appConfig.deleteSection(TXT("Section"));

	TEST_TRUE(appConfig.readString(TXT("Section"), TXT("List"), TXT("")) == TXT(""));
}

	WCL::RegKey::DeleteTree(rootKey, appPath.c_str());
	ASSERT(!WCL::RegKey::Exists(rootKey, appPath.c_str()));

	CFile::Delete(iniFile.m_strPath);
	ASSERT(!iniFile.m_strPath.Exists());
}
TEST_SET_END
