////////////////////////////////////////////////////////////////////////////////
//! \file   StrConvs.hpp
//! \brief  String conversion functions for Windows specfic types.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_STRCONVS_HPP
#define WCL_STRCONVS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/AnsiWide.hpp>

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

#endif // WCL_STRCONVS_HPP
