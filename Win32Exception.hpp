////////////////////////////////////////////////////////////////////////////////
//! \file   Win32Exception.hpp
//! \brief  The Win32Exception class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_WIN32EXCEPTION_HPP
#define WCL_WIN32EXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Exception.hpp"
#include "StrCvt.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The base class for all exception types that are the result of Win32 API
//! calls.

class Win32Exception : public CException
{
public:
	//! Partial constructor.
	Win32Exception(DWORD dwError);

	//! Partial constructor that assumes ::GetLastError().
	Win32Exception(const tchar* pszOperation);

	//! Full constructor.
	Win32Exception(DWORD dwError, const tchar* pszOperation);

	//
	// Members.
	//
	DWORD	m_dwError;		//!< The Win32 error code.

protected:
	//! Default constructor.
	Win32Exception();
};

////////////////////////////////////////////////////////////////////////////////
//! Partial constructor.

inline Win32Exception::Win32Exception(DWORD dwError)
	: m_dwError(dwError)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Partial constructor that assumes ::GetLastError().

inline Win32Exception::Win32Exception(const tchar* pszOperation)
	: m_dwError(::GetLastError())
{
	m_strErrorText.Format(TXT("%s [0x%08X - %s]"), pszOperation, m_dwError, CStrCvt::FormatError(m_dwError));
}

////////////////////////////////////////////////////////////////////////////////
//! Full constructor.

inline Win32Exception::Win32Exception(DWORD dwError, const tchar* pszOperation)
	: m_dwError(dwError)
{
	m_strErrorText.Format(TXT("%s [0x%08X - %s]"), pszOperation, m_dwError, CStrCvt::FormatError(m_dwError));
}

////////////////////////////////////////////////////////////////////////////////
//! Default constructor. This should only be used by derived classes that set
//! the error and string directly.

inline Win32Exception::Win32Exception()
	: m_dwError(0)
{
}

//namespace WCL
}

#endif // WCL_WIN32EXCEPTION_HPP
