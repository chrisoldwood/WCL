////////////////////////////////////////////////////////////////////////////////
//! \file   ComException.hpp
//! \brief  The ComException class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef COMEXCEPTION_HPP
#define COMEXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The exception type thrown by the COM library.

class ComException : public CException
{
public:
	//! Default constructor.
	ComException(HRESULT hResult, const char* pszOperation);

	//! Destructor.
	virtual ~ComException();
	
	//
	// Members.
	//
	HRESULT	m_hResult;	//!< The underlying COM error code.
};

//namespace WCL
}

#endif // COMEXCEPTION_HPP
