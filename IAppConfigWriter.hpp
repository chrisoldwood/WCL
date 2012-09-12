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
	//! Abstract destructor.
	virtual ~IAppConfigWriter() = 0 {}; 

	//
	// Methods.
	//

	//! Write a string value.
	virtual void writeString(const tstring& sectionName, const tstring& keyName, const tstring& value) = 0;

	//! Write a value.
	template<typename T>
	void writeValue(const tstring& sectionName, const tstring& keyName, const T& value);

	//! Write a list of values.
	virtual void writeList(const tstring& sectionName, const tstring& keyName, const StringArray& list) = 0;

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

//namespace WCL
}

#endif // WCL_IAPPCONFIGWRITER_HPP
