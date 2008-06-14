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

#include <Core/Exception.hpp>
#include "IFacePtr.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The exception type thrown for COM errors.

class ComException : public Core::Exception
{
public:
	//! Construction from a non-IErrorInfo supported error.
	ComException(HRESULT hResult, const tchar* pszOperation);

	//! Construction from an IErrorInfo supported error.
	template<typename T>
	ComException(HRESULT hResult, IFacePtr<T>& pObject, const tchar* pszOperation);

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
	void FormatError(HRESULT hResult, IUnknown* pObject, const IID& rIID, const tchar* pszOperation);
};

////////////////////////////////////////////////////////////////////////////////
//! Construction from an IErrorInfo supported error.

template<typename T>
inline ComException::ComException(HRESULT hResult, IFacePtr<T>& pObject, const tchar* pszOperation)
{
	FormatError(hResult, pObject.Get(), __uuidof(T), pszOperation);
}

//namespace WCL
}

#endif // WCL_COMEXCEPTION_HPP
