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

#include "IAppConfigReader.hpp"
#include "IAppConfigWriter.hpp"
#include "IConfigProvider.hpp"
#include <vector>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The facade used for reading and writing application settings. The class
//! encapsulates the details of where the settings are being stored, e.g. the
//! Registry, an .ini file etc. However, it is possible to explicitly set the
//! storage type as some users may want to do this.

class AppConfig : public IAppConfigReader, public IAppConfigWriter
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
	virtual ~AppConfig();

	//
	// Properties.
	//

	//! Get the current storage mechanism.
	Storage getStorageType() const;

	//! Set the storage mechanism.
	void setStorageType(Storage storage);

	//
	// IAppConfigReader methods.
	//

	//! Read a string value.
	virtual tstring readString(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue) const;

	//! Read a list of string values.
	virtual void readStringList(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue, StringArray& list) const;

	//
	// IAppConfigWriter methods.
	//

	//! Write a string value.
	virtual void writeString(const tstring& sectionName, const tstring& keyName, const tstring& value);

	//! Write a list of string values.
	virtual void writeStringList(const tstring& sectionName, const tstring& keyName, const StringArray& list);

	//! Delete the entire section.
	virtual void deleteSection(const tstring& sectionName);

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

//namespace WCL
}

#endif // WCL_APPCONFIG_HPP
