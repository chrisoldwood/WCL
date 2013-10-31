////////////////////////////////////////////////////////////////////////////////
//! \file   IAppConfigReader.hpp
//! \brief  The IAppConfigReader interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_IAPPCONFIGREADER_HPP
#define WCL_IAPPCONFIGREADER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/StringUtils.hpp>
#include <vector>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The reader interface for the application configuration files.

class IAppConfigReader
{
public:
	//
	// Types.
	//

	//! An array based list of strings.
	typedef std::vector<tstring> StringArray;

public:
	// Make abstract.
	virtual ~IAppConfigReader() {};

	//
	// Methods.
	//

	//! Read a string value.
	virtual tstring readString(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue) const = 0;

	//! Read a value.
	template<typename T>
	T readValue(const tstring& sectionName, const tstring& keyName, const T& defaultValue) const;

	//! Read a list of string values.
	virtual void readStringList(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue, StringArray& list) const = 0;

	//! Read a list of values.
	template<typename T>
	void readList(const tstring& sectionName, const tstring& keyName, const std::vector<T>& defaultList, std::vector<T>& list) const;
};

////////////////////////////////////////////////////////////////////////////////
//! Read a value.

template<typename T>
inline T IAppConfigReader::readValue(const tstring& sectionName, const tstring& keyName, const T& defaultValue) const
{
	tstring value = readString(sectionName, keyName, tstring());

	if (value.empty())
		return defaultValue;

	return Core::parse<T>(value);
}


////////////////////////////////////////////////////////////////////////////////
//! Read a list of values.

template<typename T>
inline void IAppConfigReader::readList(const tstring& sectionName, const tstring& keyName, const std::vector<T>& defaultList, std::vector<T>& list) const
{
	typedef StringArray::const_iterator ConstIter;

	StringArray stringValues;

	readStringList(sectionName, keyName, tstring(), stringValues);

	if (stringValues.empty())
	{
		list = defaultList;
	}
	else
	{
		for (ConstIter it = stringValues.begin(); it != stringValues.end(); ++it)
			list.push_back(Core::parse<T>(*it));
	}
}

//namespace WCL
}

#endif // WCL_IAPPCONFIGREADER_HPP
