////////////////////////////////////////////////////////////////////////////////
//! \file   ResourceString.hpp
//! \brief  Utility functions for handling strings in module resources.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_RESOURCESTRING_HPP
#define WCL_RESOURCESTRING_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
// Load a string from the specified module.

tstring loadString(HMODULE module, uint resourceId);

////////////////////////////////////////////////////////////////////////////////
// Load a string from the application module resources.

tstring loadString(uint resourceId);

//namespace WCL
}

#endif // WCL_RESOURCESTRING_HPP
