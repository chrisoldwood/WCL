////////////////////////////////////////////////////////////////////////////////
//! \file   Win32Exception.hpp
//! \brief  The Win32Exception class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WIN32EXCEPTION_HPP
#define WIN32EXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The base class for all exception types that are the result of Win32 API
//! calls.

class Win32Exception : public CException
{
protected:
	//! Partial constructor.
	Win32Exception(DWORD dwError);

	//! Full constructor.
	Win32Exception(DWORD dwError, const char* pszOperation);

public:
	//
	// Members.
	//
	DWORD	m_dwError;		//!< The Win32 error code.
};

////////////////////////////////////////////////////////////////////////////////
//! Partial constructor.

inline Win32Exception::Win32Exception(DWORD dwError)
	: CException(-1)
	, m_dwError(dwError)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Full constructor.

inline Win32Exception::Win32Exception(DWORD dwError, const char* pszOperation)
	: CException(-1)
	, m_dwError(dwError)
{
	m_strErrorText.Format("%s [0x%08X - %s]", pszOperation, dwError, CStrCvt::FormatError(dwError));
}

//namespace WCL
}

#endif // WIN32EXCEPTION_HPP
