////////////////////////////////////////////////////////////////////////////////
//! \file   StringUtils.hpp
//! \brief  String utility functions for Windows specific types.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_STRINGUTILS_HPP
#define WCL_STRINGUTILS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/StringUtils.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Convert a BSTR to a C-style wide character string. This functions adjusts
//! for the behaviour where a BSTR can be NULL to represent an empty string.

inline const wchar_t* BstrToWide(const BSTR bstr)
{
	return (bstr != nullptr) ? bstr : L"";
}

//! Convert a BSTR to a safe C++ wide character string.
#define BSTR2W(bstr)	WCL::BstrToWide(bstr)

//namespace WCL
}

// Forward declarations.
class CRect;

namespace Core
{

////////////////////////////////////////////////////////////////////////////////
// Format a rectangle into a string.

template<>
tstring format(const CRect& value);

////////////////////////////////////////////////////////////////////////////////
// Parse a rectangle from a string.

template<>
CRect parse(const tstring& buffer); // throw(ParseException)

//namespace Core
}

#endif // WCL_STRINGUTILS_HPP
