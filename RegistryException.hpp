////////////////////////////////////////////////////////////////////////////////
//! \file   RegistryException.hpp
//! \brief  The RegistryException class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef REGISTRYEXCEPTION_HPP
#define REGISTRYEXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Win32Exception.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The exception type thrown by the RegKey class.

class RegistryException : public Win32Exception
{
public:
	//! Full constructor.
	RegistryException(LONG lError, const char* pszOperation);
};

////////////////////////////////////////////////////////////////////////////////
//! Full constructor.

inline RegistryException::RegistryException(LONG lError, const char* pszOperation)
	: Win32Exception(lError, pszOperation)
{
}

//namespace WCL
}

#endif // REGISTRYEXCEPTION_HPP
