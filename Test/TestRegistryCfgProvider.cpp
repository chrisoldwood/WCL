////////////////////////////////////////////////////////////////////////////////
//! \file   TestRegistryCfgProvider.cpp
//! \brief  The unit tests for the RegistryCfgProvider class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/RegistryCfgProvider.hpp>
#include <WCL/Path.hpp>
#include <Core/StringUtils.hpp>
#include <WCL/RegKey.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the RegistryCfgProvider class.

void TestRegistryCfgProvider()
{
	HKEY    rootKey     = HKEY_CURRENT_USER;
	tstring publisher   = TXT("Chris Oldwood");
	tstring pubPath     = Core::fmt(TXT("Software\\%s"), publisher.c_str());
	tstring application = TXT("Unit Tests");
	tstring appPath     = Core::fmt(TXT("Software\\%s\\%s"), publisher.c_str(), application.c_str());

	WCL::RegKey::DeleteTree(rootKey, appPath.c_str());
	ASSERT(!WCL::RegKey::Exists(rootKey, appPath.c_str()));

	TEST_FALSE(WCL::RegistryCfgProvider::isAvailable(publisher, application));

	WCL::RegKey key;

	key.Create(rootKey, pubPath.c_str());
	key.Close();

	key.Create(rootKey, appPath.c_str());
	key.Close();

	key.Create(rootKey, (appPath + TXT("\\Section")).c_str());
	key.Close();

	key.Create(rootKey, (appPath + TXT("\\Section")).c_str());
	key.WriteStringValue(TXT("Key"), TXT("Value"));
	key.Close();

	TEST_TRUE(WCL::RegistryCfgProvider::isAvailable(publisher, application));

	WCL::RegistryCfgProvider provider(publisher, application);

	TEST_TRUE(provider.readString(TXT("Section"), TXT("Key"), TXT("default")) == TXT("Value"));

	provider.writeString(TXT("Section2"), TXT("Key2"), TXT("Value2"));
	
	TEST_TRUE(provider.readString(TXT("Section2"), TXT("Key2"), TXT("default")) == TXT("Value2"));

	provider.deleteSection(TXT("Section2"));

	TEST_FALSE(provider.readString(TXT("Section2"), TXT("Key2"), TXT("default")) == TXT("Value2"));

	WCL::RegKey::DeleteTree(rootKey, appPath.c_str());
	ASSERT(!WCL::RegKey::Exists(rootKey, appPath.c_str()));
}
