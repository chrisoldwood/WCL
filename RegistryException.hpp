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
	//! Construction from a fully formatted error message.
	RegistryException(const std::tstring& strOperation);

	//! Full constructor.
	RegistryException(LONG lError, const tchar* pszOperation);

	//! Full constructor.
	RegistryException(LONG lError, const std::tstring& strOperation);
};

////////////////////////////////////////////////////////////////////////////////
//! Construction from a fully formatted error message.

inline RegistryException::RegistryException(const std::tstring& strOperation)
	: Win32Exception()
{
	m_strErrorText = strOperation.c_str();
}

////////////////////////////////////////////////////////////////////////////////
//! Full constructor.

inline RegistryException::RegistryException(LONG lError, const tchar* pszOperation)
	: Win32Exception(lError, pszOperation)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Full constructor.

inline RegistryException::RegistryException(LONG lError, const std::tstring& strOperation)
	: Win32Exception(lError, strOperation.c_str())
{
}

//namespace WCL
}

#endif // REGISTRYEXCEPTION_HPP
