////////////////////////////////////////////////////////////////////////////////
//! \file   ComException.hpp
//! \brief  The ComException class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_COMEXCEPTION_HPP
#define WCL_COMEXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Exception.hpp"
#include <Core/IFacePtr.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The exception type thrown for COM errors.

class ComException : public CException
{
public:
	//! Construction from a non-IErrorInfo supported error.
	ComException(HRESULT hResult, const char* pszOperation);

	//! Construction from an IErrorInfo supported error.
	template<typename T>
	ComException(HRESULT hResult, Core::IFacePtr<T>& pObject, const char* pszOperation);

	//! Destructor.
	virtual ~ComException();
	
	//
	// Members.
	//
	HRESULT	m_hResult;	//!< The underlying COM error code.

private:
	//
	// Internal methods.
	//

	//! Format the error using the IErrorInfo details.
	void FormatError(HRESULT hResult, IUnknown* pObject, const IID& rIID, const char* pszOperation);
};

////////////////////////////////////////////////////////////////////////////////
//! Construction from an IErrorInfo supported error.

template<typename T>
inline ComException::ComException(HRESULT hResult, Core::IFacePtr<T>& pObject, const char* pszOperation)
{
	FormatError(hResult, pObject.Get(), __uuidof(T), pszOperation);
}

//namespace WCL
}

#endif // WCL_COMEXCEPTION_HPP
