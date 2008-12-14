////////////////////////////////////////////////////////////////////////////////
//! \file   AppConfig.hpp
//! \brief  The AppConfig class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_APPCONFIG_HPP
#define WCL_APPCONFIG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "IConfigProvider.hpp"
#include <Core/StringUtils.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The facade used for reading and writing application settings. The class
//! encapsulates the details of where the settings are being stored, e.g. the
//! Registry, an .ini file etc. However, it is possible to explicitly set the
//! storage type as some users may want to do this.

class AppConfig
{
public:
	//
	// Types.
	//

	//! The storage types.
	enum Storage
	{
		AUTOMATIC	= -1,			//!< Automatically determine the storage.

		REGISTRY	= 1,			//!< Use the Registry.
		INIFILE		= 2,			//!< Use an .ini file.
	};

	//! An array based list of strings.
	typedef std::vector<tstring> StringArray;

	//! The name for the default section.
	static const tstring DEFAULT_SECTION;

public:
	//! Constructor.
	AppConfig(const tstring& publisher, const tstring& application);

	//! Destructor.
	~AppConfig();
	
	//
	// Properties.
	//

	//! Get the current storage mechanism.
	Storage getStorageType() const;

	//! Set the storage mechanism.
	void setStorageType(Storage storage);

	//
	// Methods.
	//

	//! Read a string value.
	tstring readString(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue) const;

	//! Read a value.
	template<typename T>
	T readValue(const tstring& sectionName, const tstring& keyName, const T& defaultValue) const;

	//! Read a list of values.
	void readList(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue, StringArray& list) const;

	//! Write a string value.
	void writeString(const tstring& sectionName, const tstring& keyName, const tstring& value);

	//! Write a value.
	template<typename T>
	void writeValue(const tstring& sectionName, const tstring& keyName, const T& value);

	//! Write a list of values.
	void writeList(const tstring& sectionName, const tstring& keyName, const StringArray& list);

	//! Delete the entire section.
	void deleteSection(const tstring& sectionName);

private:
	//
	// Members.
	//
	mutable Storage				m_storage;		//!< The current storage mechanism.
	mutable IConfigProviderPtr	m_provider;		//!< The data provider.
	tstring						m_publisher;	//!< The name of the publisher.
	tstring						m_application;	//!< The name of the application.

	//
	// Internal methods.
	//

	//! Determine which provider to use.
	Storage determineProvider() const;

	//! Get the provider.
	IConfigProviderPtr getProvider() const;
};

////////////////////////////////////////////////////////////////////////////////
//! Read a value.

template<typename T>
inline T AppConfig::readValue(const tstring& sectionName, const tstring& keyName, const T& defaultValue) const
{
	tstring value = readString(sectionName, keyName, tstring());

	if (value.empty())
		return defaultValue;

	return Core::parse<T>(value);
}

////////////////////////////////////////////////////////////////////////////////
//! Write a value.

template<typename T>
inline void AppConfig::writeValue(const tstring& sectionName, const tstring& keyName, const T& value)
{
	tstring buffer = Core::format<T>(value);

	writeString(sectionName, keyName, buffer);
}

//namespace WCL
}

#endif // WCL_APPCONFIG_HPP
