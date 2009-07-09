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
//! Constructor for use with non-IErrorInfo errors. The pszOperation parameter
//! is used as the prefix for the message and the error code is appended.

ComException::ComException(HRESULT hResult, const tchar* pszOperation)
	: m_hResult(hResult)
{
	m_strDetails = Core::Fmt(TXT("%s [0x%08X - %s]"), pszOperation, hResult, CStrCvt::FormatError(hResult).c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ComException::~ComException() throw()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Format the error using the IErrorInfo details.

void ComException::FormatError(HRESULT hResult, IUnknown* pObject, const IID& rIID, const tchar* pszOperation)
{
	// Type shorthands.
	typedef WCL::ComPtr<ISupportErrorInfo> ISupportErrorInfoPtr;
	typedef WCL::ComPtr<IErrorInfo> IErrorInfoPtr;

	tstring strSource;
	tstring strDescription;

	ISupportErrorInfoPtr pSupportErrorInfo;

	// Query if the object supports IErrorInfo on the interface.
	if ( (SUCCEEDED(QueryInterface(pObject, AttachTo(pSupportErrorInfo))))
	  && (pSupportErrorInfo->InterfaceSupportsErrorInfo(rIID) == S_OK) )
	{
		IErrorInfoPtr pErrorInfo;

		// Get the IErrorInfo object.
		if (::GetErrorInfo(0, AttachTo(pErrorInfo)) == S_OK)
		{
			WCL::ComStr bstrSource;
			WCL::ComStr bstrDescription;

			// Get the exception details.
			pErrorInfo->GetSource(AttachTo(bstrSource));
			pErrorInfo->GetDescription(AttachTo(bstrDescription));

			// Convert to C++ strings.
			strSource      = W2T(bstrSource.Get());
			strDescription = W2T(bstrDescription.Get());
		}
	}

	tstring strResCode(CStrCvt::FormatError(hResult));

	// Format the error string.
	if (!strSource.empty() || !strDescription.empty())
		m_strDetails = Core::Fmt(TXT("%s [0x%08X - %s] {%s : %s}"), pszOperation, hResult, strResCode.c_str(), strSource.c_str(), strDescription.c_str());
	else
		m_strDetails = Core::Fmt(TXT("%s [0x%08X - %s]"), pszOperation, hResult, strResCode.c_str());
}

//namespace WCL
}
