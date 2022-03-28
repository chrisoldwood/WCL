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

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
// Report an unhandled exception.

CORE_MSPRINTF(1, 2)
void ReportUnhandledException(const tchar* pszMsg, ...);

//namespace WCL
}

#endif // WCL_EXCEPTION_HPP
