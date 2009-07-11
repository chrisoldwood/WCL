////////////////////////////////////////////////////////////////////////////////
//! \file   RegistryCfgProvider.cpp
//! \brief  The RegistryCfgProvider class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "RegistryCfgProvider.hpp"
#include <Core/StringUtils.hpp>
#include "RegKey.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

RegistryCfgProvider::RegistryCfgProvider(const tstring& publisher, const tstring& application)
	: m_publisher(publisher)
	, m_application(application)
	, m_rootKey(HKEY_CURRENT_USER)
	, m_keyPath(Core::fmt(TXT("Software\\%s\\%s"), publisher.c_str(), application.c_str()))
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

RegistryCfgProvider::~RegistryCfgProvider()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Check if there is a config tree already.

bool RegistryCfgProvider::isAvailable(const tstring& publisher, const tstring& application)
{
	HKEY    rootKey = HKEY_CURRENT_USER;
	tstring path    = Core::fmt(TXT("Software\\%s\\%s"), publisher.c_str(), application.c_str());

	return RegKey::Exists(rootKey, path.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Remove the config information.

void RegistryCfgProvider::removeConfig(const tstring& publisher, const tstring& application)
{
	HKEY    rootKey = HKEY_CURRENT_USER;
	tstring path    = Core::fmt(TXT("Software\\%s\\%s"), publisher.c_str(), application.c_str());

	RegKey::DeleteTree(rootKey, path.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Read a string value.

tstring RegistryCfgProvider::readString(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue) const
{
	tstring path = m_keyPath;

	if (!sectionName.empty())
		path += TXT("\\") + sectionName;

	return tstring(RegKey::ReadKeyStringValue(m_rootKey, path.c_str(), keyName.c_str(), defaultValue.c_str()));
}

////////////////////////////////////////////////////////////////////////////////
//! Write a string value.

void RegistryCfgProvider::writeString(const tstring& sectionName, const tstring& keyName, const tstring& value)
{
	tstring path = m_keyPath;

	if (!sectionName.empty())
		path += TXT("\\") + sectionName;

	RegKey::WriteKeyStringValue(m_rootKey, path.c_str(), keyName.c_str(), value.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Delete the entire section.

void RegistryCfgProvider::deleteSection(const tstring& sectionName)
{
	tstring path = m_keyPath + TXT("\\") + sectionName;

	RegKey::DeleteTree(m_rootKey, path.c_str());
}

//namespace WCL
}
