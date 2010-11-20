////////////////////////////////////////////////////////////////////////////////
//! \file   RegistryCfgProvider.hpp
//! \brief  The RegistryCfgProvider class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_REGISTRYCFGPROVIDER_HPP
#define WCL_REGISTRYCFGPROVIDER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "IConfigProvider.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The config data provider that uses the Registry for storage. The values are
//! stored in the HKCU branch.

class RegistryCfgProvider : public IConfigProvider
{
public:
	//! Constructor.
	RegistryCfgProvider(const tstring& publisher, const tstring& application);

	//! Destructor.
	virtual ~RegistryCfgProvider();

	//
	// Methods.
	//

	//! Check if there is a config tree already.
	static bool isAvailable(const tstring& publisher, const tstring& application);

	//! Remove the config information.
	static void removeConfig(const tstring& publisher, const tstring& application);

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
	tstring	m_publisher;		//!< The name of the publisher.
	tstring	m_application;		//!< The application name.
	HKEY    m_rootKey;			//!< The config root key.
	tstring	m_keyPath;			//!< The config path.

	// NotCopyable.
	RegistryCfgProvider(const RegistryCfgProvider&);
	RegistryCfgProvider& operator=(const RegistryCfgProvider&);
};

//namespace WCL
}

#endif // WCL_REGISTRYCFGPROVIDER_HPP
