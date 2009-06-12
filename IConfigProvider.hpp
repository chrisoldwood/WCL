////////////////////////////////////////////////////////////////////////////////
//! \file   IConfigProvider.hpp
//! \brief  The IConfigProvider interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_ICONFIGPROVIDER_HPP
#define WCL_ICONFIGPROVIDER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The interface for providers that store application settings.

class IConfigProvider
{
public:
	//! Destructor.
	virtual ~IConfigProvider() {};

	//
	// Methods.
	//

	//! Read a string value.
	virtual tstring readString(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue) const = 0;

	//! Write a string value.
	virtual void writeString(const tstring& sectionName, const tstring& keyName, const tstring& value) = 0;

	//! Delete the entire section.
	virtual void deleteSection(const tstring& sectionName) = 0;
};

//! The default IConfigProvider smart-pointer type.
typedef Core::SharedPtr<IConfigProvider> IConfigProviderPtr;

//namespace WCL
}

#endif // WCL_ICONFIGPROVIDER_HPP
