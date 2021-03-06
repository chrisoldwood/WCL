////////////////////////////////////////////////////////////////////////////////
//! \file   StructuredException.hpp
//! \brief  The StructuredException class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_STRUCTUREDEXCEPTION_HPP
#define WCL_STRUCTUREDEXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/Exception.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The type of exception thrown when a Win32 structured exception occurs.

class StructuredException : public Core::Exception
{
public:
	//! Constructor.
	StructuredException(uint nCode, _EXCEPTION_POINTERS* pInfo);

	//! Destructor.
	~StructuredException() throw();
	
	//
	// Members.
	//
	uint	m_nCode;	//!< The Win32 exception code.

private:
	//
	// Internal methods.
	//

	//! Internal method to convert the exception code to a string.
	static const tchar* FormatCode(uint nCode);
};

//namespace WCL
}

#endif // WCL_STRUCTUREDEXCEPTION_HPP
