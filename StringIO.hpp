////////////////////////////////////////////////////////////////////////////////
//! \file   StringIO.hpp
//! \brief  I/O stream helper functions for the legacy CString class.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_STRINGIO_HPP
#define WCL_STRINGIO_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <ostream>

////////////////////////////////////////////////////////////////////////////////
//! STL output stream inserter.

inline tostream& operator<<(tostream& os, const CString& str)
{
	os << str.c_str();

	return os;
}

#endif // WCL_STRINGIO_HPP
