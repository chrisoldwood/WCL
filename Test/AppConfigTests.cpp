////////////////////////////////////////////////////////////////////////////////
//! \file   AppConfigTests.cpp
//! \brief  The unit tests for the AppConfig class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/AppConfig.hpp>
#include <WCL/RegKey.hpp>
#include <Core/StringUtils.hpp>
#include <WCL/IniFile.hpp>
#include <WCL/File.hpp>

static HKEY    s_rootKey     = HKEY_CURRENT_USER;
static tstring s_publisher   = TXT("Chris Oldwood");
static tstring s_pubPath     = Core::fmt(TXT("Software\\%s"), s_publisher.c_str());
static tstring s_application = TXT("Unit Tests");
static tstring s_appPath     = Core::fmt(TXT("Software\\%s\\%s"), s_publisher.c_str(), s_application.c_str());

namespace
{

class FakeAppConfigReader : public WCL::IAppConfigReader
{
public:
	virtual tstring readString(const tstring& /*sectionName*/, const tstring& /*keyName*/, const tstring& /*defaultValue*/) const
	{
		return m_value;
	}

	virtual void readList(const tstring& /*sectionName*/, const tstring& /*keyName*/, const tstring& /*defaultValue*/, StringArray& /*list*/) const
	{
	}

	tstring	m_value;
};

class FakeAppConfigWriter : public WCL::IAppConfigWriter
{
public:
	virtual void writeString(const tstring& /*sectionName*/, const tstring& /*keyName*/, const tstring& value)
	{
		m_value = value;
	}

	virtual void writeList(const tstring& /*sectionName*/, const tstring& /*keyName*/, const StringArray& /*list*/)
	{
	}

	virtual void deleteSection(const tstring& /*sectionName*/)
	{
	}

	tstring	m_value;
};

}

TEST_SET(AppConfig)
{

TEST_CASE_TEARDOWN()
{
	WCL::RegKey::DeleteTree(s_rootKey, s_appPath.c_str());
	ASSERT(!WCL::RegKey::Exists(s_rootKey, s_appPath.c_str()));

	CIniFile iniFile;
	CFile::Delete(iniFile.m_strPath);
	ASSERT(!iniFile.m_strPath.Exists());
}
TEST_CASE_TEARDOWN_END

TEST_CASE("default configuration provider is the registry")
{

{
	WCL::AppConfig appConfig(s_publisher, s_application);

	TEST_TRUE(appConfig.getStorageType() == WCL::AppConfig::REGISTRY);

	appConfig.writeString(TXT("Section"), TXT("Key"), TXT("Value"));

	TEST_TRUE(WCL::RegKey::ReadKeyStringValue(HKEY_CURRENT_USER, (s_appPath + TXT("\\Section")).c_str(), TXT("Key"), TXT("default")) == TXT("Value"));

	appConfig.writeString(WCL::AppConfig::DEFAULT_SECTION, TXT("Key2"), TXT("Value2"));

	TEST_TRUE(WCL::RegKey::ReadKeyStringValue(HKEY_CURRENT_USER, s_appPath.c_str(), TXT("Key2"), TXT("default")) == TXT("Value2"));
}

{
	WCL::AppConfig appConfig(s_publisher, s_application);

	TEST_TRUE(appConfig.getStorageType() == WCL::AppConfig::REGISTRY);

	TEST_TRUE(appConfig.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));
}

}
TEST_CASE_END

TEST_CASE("one alternate configuration provider is an .ini file")
{
	CIniFile       iniFile;
	WCL::AppConfig appConfig(s_publisher, s_application);

	appConfig.setStorageType(WCL::AppConfig::INIFILE);

	TEST_TRUE(WCL::RegKey::Exists(s_rootKey, s_pubPath.c_str()) && !WCL::RegKey::Exists(s_rootKey, s_appPath.c_str()));

	appConfig.writeString(TXT("Section"), TXT("Key"), TXT("Value"));

	TEST_TRUE(iniFile.ReadString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));

	appConfig.writeString(WCL::AppConfig::DEFAULT_SECTION, TXT("Key2"), TXT("Value2"));

	TEST_TRUE(iniFile.ReadString(s_application, TXT("Key2"), TXT("default")) == TXT("Value2"));

	appConfig.setStorageType(WCL::AppConfig::REGISTRY);

	TEST_TRUE(!iniFile.m_strPath.Exists());
}
TEST_CASE_END

TEST_CASE("the default value is returned when no configuration value exists")
{
	WCL::AppConfig appConfig(s_publisher, s_application);

	const size_t value    = 1234;
	const size_t defValue = 5678;

	TEST_TRUE(appConfig.readValue<size_t>(TXT("Section"), TXT("Name"), defValue) == defValue);

	appConfig.writeValue<size_t>(TXT("Section"), TXT("Name"), value);

	TEST_TRUE(appConfig.readValue<size_t>(TXT("Section"), TXT("Name"), defValue) == value);
}
TEST_CASE_END

TEST_CASE("a list of strings can be written and read")
{
	WCL::AppConfig appConfig(s_publisher, s_application);

	WCL::AppConfig::StringArray list;

	list.push_back(TXT("1234"));
	list.push_back(TXT("5678"));

	appConfig.writeList(TXT("Section"), TXT("List"), list);

	WCL::AppConfig::StringArray result;

	appConfig.readList(TXT("Section"), TXT("List"), TXT(""), result);

	TEST_TRUE(result == list);
}
TEST_CASE_END

TEST_CASE("a section can be deleted by name")
{
	WCL::AppConfig appConfig(s_publisher, s_application);

	const size_t value    = 1234;
	const size_t defValue = 5678;

	appConfig.writeValue<size_t>(TXT("Section"), TXT("Name"), value);

	appConfig.deleteSection(TXT("Section"));

	TEST_TRUE(appConfig.readValue<size_t>(TXT("Section"), TXT("Name"), defValue) == defValue);
}
TEST_CASE_END

TEST_CASE("The app config reader interface can be mocked")
{
	const tstring expectedString = TXT("unit test");
	const size_t  expectedValue = 12345;

	FakeAppConfigReader fake;

	fake.m_value = expectedString;

	TEST_TRUE(fake.readString(TXT("any"), TXT("any"), TXT("default")) == expectedString);

	fake.m_value = Core::fmt(TXT("%u"), expectedValue);

	TEST_TRUE(fake.readValue<size_t>(TXT("any"), TXT("any"), 0u) == expectedValue);
}
TEST_CASE_END

TEST_CASE("The app config writer interface can be mocked")
{
	const tstring expectedString = TXT("unit test");
	const size_t  expectedValue = 12345;

	FakeAppConfigWriter fake;

	fake.writeString(TXT("any"), TXT("any"), expectedString);

	TEST_TRUE(fake.m_value == expectedString);

	fake.writeValue<size_t>(TXT("any"), TXT("any"), expectedValue);

	TEST_TRUE(fake.m_value == Core::fmt(TXT("%u"), expectedValue));
}
TEST_CASE_END

}
TEST_SET_END
