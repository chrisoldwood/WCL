////////////////////////////////////////////////////////////////////////////////
//! \file   Exception.hpp
//! \brief  The Exception class declaration and utility functions.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_EXCEPTION_HPP
#define WCL_EXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/Exception.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The base class for all WCL exceptions.

class CException : public Core::Exception
{
public:
	//! Retrieve the error message.
	virtual const tchar* ErrorText() const;

	//! Get the exception details.
	virtual const tchar* What() const;

	//! Retrieve the ANSI only error message.
	virtual const char* what() const;

protected:
	//! Default constructor.
	CException();

	//! Destructor.
	virtual ~CException();

	//
	// Members.
	//
	CString				m_strErrorText;		//!< The error message.
#ifdef UNICODE_BUILD
	mutable std::string	m_strAnsiText;		//!< The ANSI error message.
#endif
};

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
// Report an unhandled exception.

void ReportUnhandledException(const tchar* pszMsg, ...);

//namespace WCL
}

#endif // WCL_EXCEPTION_HPP
