////////////////////////////////////////////////////////////////////////////////
//! \file   AppConfig.cpp
//! \brief  The AppConfig class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "AppConfig.hpp"
#include "IniFileCfgProvider.hpp"
#include "RegistryCfgProvider.hpp"
#include <Core/Tokeniser.hpp>

namespace WCL
{

//! The name for the default section.
const tstring AppConfig::DEFAULT_SECTION = TXT("");

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

AppConfig::AppConfig(const tstring& publisher, const tstring& application)
	: m_storage(AUTOMATIC)
	, m_provider()
	, m_publisher(publisher)
	, m_application(application)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

AppConfig::~AppConfig()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get the current storage mechanism.

AppConfig::Storage AppConfig::getStorageType() const
{
	if (m_storage == AUTOMATIC)
		getProvider();

	return m_storage;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the storage mechanism. This makes the storage mechanism explicit.

void AppConfig::setStorageType(Storage storage)
{
	// Clean up existing storage.
	if (m_storage != storage)
	{
		// Determine provider?
		if (storage == AUTOMATIC)
			storage = determineProvider();

		ASSERT(storage != AUTOMATIC);

		if (storage == INIFILE)
			RegistryCfgProvider::removeConfig(m_publisher, m_application);

		if (storage == REGISTRY)
			IniFileCfgProvider::removeConfig();

		// Update state.
		m_storage = storage;
		m_provider.reset();
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read a string value.

tstring AppConfig::readString(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue) const
{
	return getProvider()->readString(sectionName, keyName, defaultValue);
}

////////////////////////////////////////////////////////////////////////////////
//! Read a list of string values.

void AppConfig::readStringList(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue, StringArray& list) const
{
	tstring value = readString(sectionName, keyName, defaultValue);

	Core::Tokeniser::split(value, TXT(","), list);
}

////////////////////////////////////////////////////////////////////////////////
//! Write a string value.

void AppConfig::writeString(const tstring& sectionName, const tstring& keyName, const tstring& value)
{
	return getProvider()->writeString(sectionName, keyName, value);
}

////////////////////////////////////////////////////////////////////////////////
//! Write a list of string values.

void AppConfig::writeStringList(const tstring& sectionName, const tstring& keyName, const StringArray& list)
{
	tstring value;

	for (StringArray::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		if (!value.empty())
			value += TXT(",");

		value += *it;
	}

	writeString(sectionName, keyName, value);
}

////////////////////////////////////////////////////////////////////////////////
//! Delete the entire section.

void AppConfig::deleteSection(const tstring& sectionName)
{
	return getProvider()->deleteSection(sectionName);
}

////////////////////////////////////////////////////////////////////////////////
//! Determine which provider to use.

AppConfig::Storage AppConfig::determineProvider() const
{
	// Sniff the filesystem first.
	if (IniFileCfgProvider::isAvailable())
	{
		return INIFILE;
	}
	// Sniff the Registry next.
	else if (RegistryCfgProvider::isAvailable(m_publisher, m_application))
	{
		return REGISTRY;
	}

	// Default to the Registry.
	return REGISTRY;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the provider. The provider is created on-demand and then cached for
//! subsequent queries.

IConfigProviderPtr AppConfig::getProvider() const
{
	// Return cached provider.
	if (m_provider.get() != nullptr)
		return m_provider;

	// Need to determine the provider?
	if (m_storage == AUTOMATIC)
		m_storage = determineProvider();

	ASSERT(m_storage != AUTOMATIC);

	// Allocate provider.
	if (m_storage == REGISTRY)
	{
		m_provider = IConfigProviderPtr(new RegistryCfgProvider(m_publisher, m_application));
	}
	else if (m_storage == INIFILE)
	{
		m_provider = IConfigProviderPtr(new IniFileCfgProvider(m_publisher, m_application));
	}

	ASSERT(m_provider.get() != nullptr);

	return m_provider;
}

//namespace WCL
}
