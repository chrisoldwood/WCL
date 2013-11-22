////////////////////////////////////////////////////////////////////////////////
//! \file   IAppConfigWriter.hpp
//! \brief  The IAppConfigWriter interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_IAPPCONFIGWRITER_HPP
#define WCL_IAPPCONFIGWRITER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/StringUtils.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The writer interface for the application configuration files.

class IAppConfigWriter
{
public:
	//
	// Types.
	//

	//! An array based list of strings.
	typedef std::vector<tstring> StringArray;

public:
	// Make abstract.
	virtual ~IAppConfigWriter() {};

	//
	// Methods.
	//

	//! Write a string value.
	virtual void writeString(const tstring& sectionName, const tstring& keyName, const tstring& value) = 0;

	//! Write a value.
	template<typename T>
	void writeValue(const tstring& sectionName, const tstring& keyName, const T& value);

	//! Write a list of string values.
	virtual void writeStringList(const tstring& sectionName, const tstring& keyName, const StringArray& list) = 0;

	//! Write a list of values.
	template<typename T>
	void writeList(const tstring& sectionName, const tstring& keyName, const std::vector<T>& list);

	//! Delete the entire section.
	virtual void deleteSection(const tstring& sectionName) = 0;
};

////////////////////////////////////////////////////////////////////////////////
//! Write a value.

template<typename T>
inline void IAppConfigWriter::writeValue(const tstring& sectionName, const tstring& keyName, const T& value)
{
	tstring buffer = Core::format<T>(value);

	writeString(sectionName, keyName, buffer);
}

////////////////////////////////////////////////////////////////////////////////
//! Write a list of values.

template<typename T>
inline void IAppConfigWriter::writeList(const tstring& sectionName, const tstring& keyName, const std::vector<T>& list)
{
	typedef typename std::vector<T>::const_iterator ConstIter;

	StringArray stringValues;

	for (ConstIter it = list.begin(); it != list.end(); ++it)
		stringValues.push_back(Core::format<T>(*it));

	writeStringList(sectionName, keyName, stringValues);
}

//namespace WCL
}

#endif // WCL_IAPPCONFIGWRITER_HPP
