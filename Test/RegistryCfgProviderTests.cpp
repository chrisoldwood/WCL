////////////////////////////////////////////////////////////////////////////////
//! \file   RegistryCfgProviderTests.cpp
//! \brief  The unit tests for the RegistryCfgProvider class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/RegistryCfgProvider.hpp>
#include <WCL/Path.hpp>
#include <Core/StringUtils.hpp>
#include <WCL/RegKey.hpp>

static const HKEY    rootKey     = HKEY_CURRENT_USER;
static const tstring publisher   = TXT("Chris Oldwood");
static const tstring pubPath     = Core::fmt(TXT("Software\\%s"), publisher.c_str());
static const tstring application = TXT("Unit Tests");
static const tstring appPath     = Core::fmt(TXT("Software\\%s\\%s"), publisher.c_str(), application.c_str());

TEST_SET(RegistryCfgProvider)
{

TEST_CASE_SETUP()
{
	ASSERT(!WCL::RegKey::Exists(rootKey, appPath.c_str()));

	WCL::RegKey::CreateSubKey(rootKey, pubPath.c_str());
	WCL::RegKey::CreateSubKey(rootKey, appPath.c_str());
	WCL::RegKey::CreateSubKey(rootKey, (appPath + TXT("\\Section")).c_str());

	WCL::RegKey key;

	key.Create(rootKey, (appPath + TXT("\\Section")).c_str());
	key.WriteStringValue(TXT("Key"), TXT("Value"));
	key.Close();
}
TEST_CASE_SETUP_END

TEST_CASE_TEARDOWN()
{
	WCL::RegKey::DeleteTree(rootKey, appPath.c_str());
}
TEST_CASE_TEARDOWN_END

TEST_CASE("configuration data exists when the application registry key exists")
{
	TEST_TRUE(WCL::RegistryCfgProvider::isAvailable(publisher, application));

	WCL::RegKey::DeleteTree(rootKey, appPath.c_str());

	TEST_FALSE(WCL::RegistryCfgProvider::isAvailable(publisher, application));
}
TEST_CASE_END

TEST_CASE("reading the value for a key when it exists returns the value")
{
	WCL::RegistryCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));
}
TEST_CASE_END

TEST_CASE("reading the value for a key when it doesn't exist returns the default value")
{
	WCL::RegistryCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Invalid"), TXT("Invalid"), TXT("default")) == TXT("default"));
}
TEST_CASE_END

TEST_CASE("writing the value for a new section and key creates the section and key")
{
	WCL::RegistryCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Section2"), TXT("Key2"), TXT("default")) == TXT("default"));

	provider.writeString(TXT("Section2"), TXT("Key2"), TXT("Value2"));
	
	TEST_TRUE(provider.readString(TXT("Section2"), TXT("Key2"), TXT("default")) == TXT("Value2"));
}
TEST_CASE_END

TEST_CASE("deleting a section removes all entries in that section")
{
	WCL::RegistryCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));

	provider.deleteSection(TXT("Section"));

	TEST_FALSE(provider.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));
}
TEST_CASE_END

}
TEST_SET_END
