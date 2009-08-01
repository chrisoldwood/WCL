////////////////////////////////////////////////////////////////////////////////
//! \file   ComException.cpp
//! \brief  The ComException class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ComException.hpp"
#include "ComStr.hpp"
#include <Core/AnsiWide.hpp>
#include "StrCvt.hpp"
#include "ComPtr.hpp"
#include <Core/StringUtils.hpp>

#ifndef _MSC_VER
WCL_DECLARE_IFACETRAITS(ISupportErrorInfo, IID_ISupportErrorInfo);
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Construction from an error code.

ComException::ComException(HRESULT result)
	: m_result(result)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Constructor for use with non-IErrorInfo errors. The pszOperation parameter
//! is used as the prefix for the message and the error code is appended.

ComException::ComException(HRESULT result, const tchar* operation)
	: m_result(result)
{
	m_strDetails = Core::fmt(TXT("%s [0x%08X - %s]"), operation, result, CStrCvt::FormatError(result).c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ComException::~ComException() throw()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Format the error using the IErrorInfo details.

void ComException::formatError(HRESULT result, IUnknown* object, const IID& iid, const tchar* operation)
{
	tstring source;
	tstring description;
	tstring resultCode(CStrCvt::FormatError(result));

	// Query for IErrorInfo details.
	extractErrorInfo(object, iid, source, description);

	// Format the error string.
	if (!source.empty() || !description.empty())
		m_strDetails = Core::fmt(TXT("%s [0x%08X - %s] {%s : %s}"), operation, result, resultCode.c_str(), source.c_str(), description.c_str());
	else
		m_strDetails = Core::fmt(TXT("%s [0x%08X - %s]"), operation, result, resultCode.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Extract the ErrorInfo details from the COM object, if present.

bool ComException::extractErrorInfo(IUnknown* object, const IID& iid, tstring& source, tstring& description)
{
	// Type shorthands.
	typedef WCL::ComPtr<ISupportErrorInfo> ISupportErrorInfoPtr;
	typedef WCL::ComPtr<IErrorInfo> IErrorInfoPtr;

	ISupportErrorInfoPtr supportErrorInfo;

	// Query if the object supports IErrorInfo on the interface.
	if ( (SUCCEEDED(QueryInterface(object, AttachTo(supportErrorInfo))))
	  && (supportErrorInfo->InterfaceSupportsErrorInfo(iid) == S_OK) )
	{
		IErrorInfoPtr errorInfo;

		// Get the IErrorInfo object.
		if (::GetErrorInfo(0, AttachTo(errorInfo)) == S_OK)
		{
			WCL::ComStr bstrSource;
			WCL::ComStr bstrDescription;

			// Get the exception details.
			errorInfo->GetSource(AttachTo(bstrSource));
			errorInfo->GetDescription(AttachTo(bstrDescription));

			// Convert to C++ strings.
			source      = W2T(bstrSource.Get());
			description = W2T(bstrDescription.Get());

			return true;
		}
	}

	return false;
}

//namespace WCL
}
