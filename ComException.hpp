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
	ComException(HRESULT result, const tchar* operation);

	//! Construction from an IErrorInfo supported error.
	template<typename T>
	ComException(HRESULT result, IFacePtr<T>& object, const tchar* operation);

	//! Destructor.
	virtual ~ComException() throw();

	//
	// Members.
	//
	HRESULT	m_result;	//!< The underlying COM error code.

protected:
	//
	// Internal methods.
	//

	//! Construction from an error code.
	ComException(HRESULT result);

	//! Extract the ErrorInfo details from the COM object, if present.
	static bool extractErrorInfo(IUnknown* object, const IID& iid, tstring& source, tstring& description);

private:
	//
	// Internal methods.
	//

	//! Format the error using the IErrorInfo details.
	void formatError(HRESULT result, IUnknown* object, const IID& iid, const tchar* operation);
};

////////////////////////////////////////////////////////////////////////////////
//! Construction from an IErrorInfo supported error.

template<typename T>
inline ComException::ComException(HRESULT result, IFacePtr<T>& object, const tchar* operation)
	: m_result(result)
{
	formatError(result, object.get(), IFaceTraits<T>::uuidof(), operation);
}

//namespace WCL
}

#endif // WCL_COMEXCEPTION_HPP
