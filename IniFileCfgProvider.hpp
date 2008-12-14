////////////////////////////////////////////////////////////////////////////////
//! \file   IniFileCfgProvider.hpp
//! \brief  The IniFileCfgProvider class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_INIFILECFGPROVIDER_HPP
#define WCL_INIFILECFGPROVIDER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "IConfigProvider.hpp"
#include "IniFile.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The config data provider that uses an .ini file for storage. The .ini file
//! resides in the application folder.

class IniFileCfgProvider : public IConfigProvider
{
public:
	//! Constructor.
	IniFileCfgProvider(const tstring& publisher, const tstring& application);

	//! Destructor.
	virtual ~IniFileCfgProvider();
	
	//
	// Methods.
	//

	//! Check if there is a config file already.
	static bool isAvailable();

	//! Remove the config information.
	static void removeConfig();

	//
	// IConfigProvider methods.
	//

	//! Read a string value.
	virtual tstring readString(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue) const;

	//! Write a string value.
	virtual void writeString(const tstring& sectionName, const tstring& keyName, const tstring& value);

	//! Delete the entire section.
	virtual void deleteSection(const tstring& sectionName);

private:
	//
	// Members.
	//
	tstring		m_publisher;		//!< The name of the publisher.
	tstring		m_application;		//!< The application name.
	CIniFile	m_iniFile;		//!< The underlying storage.
};

//namespace WCL
}

#endif // WCL_INIFILECFGPROVIDER_HPP
