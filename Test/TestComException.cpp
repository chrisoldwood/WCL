////////////////////////////////////////////////////////////////////////////////
//! \file   TestComException.cpp
//! \brief  The unit tests for the ComException class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ComException.hpp>
#include <WCL/AutoCom.hpp>
#include <WCL/ComPtr.hpp>
#ifndef _MSC_VER
#include <ocidl.h>
#endif
#include "TestIFaceTraits.hpp"

////////////////////////////////////////////////////////////////////////////////
//! The com class used to implement ISupportErrorInfo.

class TestComClass : public IErrorLog,
					 public ISupportErrorInfo
{
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** object)
	{
		if (IsEqualIID(iid, IID_ISupportErrorInfo))
		{
			*object = static_cast<ISupportErrorInfo*>(this);
			return S_OK;
		}

		return E_FAIL;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		return 0;
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		return 0;
	}

	virtual HRESULT STDMETHODCALLTYPE AddError(LPCOLESTR /*property*/, EXCEPINFO* /*info*/)
	{
		return E_FAIL;
	}

	virtual HRESULT STDMETHODCALLTYPE InterfaceSupportsErrorInfo(REFIID iid)
	{
		if (IsEqualIID(iid, IID_IErrorLog))
		{
			return S_OK;
		}

		return S_FALSE;
	}
};

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the ComException class.

void TestComException()
{
	WCL::AutoCom com(COINIT_APARTMENTTHREADED);
{
	WCL::ComException e(S_FALSE, TXT("UnitTest"));

	tstring str = e.What();

	TEST_TRUE(str.find(TXT("UnitTest")) != tstring::npos);
	TEST_TRUE(str.find(TXT("0x00000001")) != tstring::npos);
}
{
	typedef WCL::IFacePtr<IMalloc> IMallocPtr;

	IMallocPtr allocator;

	HRESULT hr = CoGetMalloc(1, WCL::AttachTo(allocator));

	WCL::ComException e(hr, allocator, TXT("UnitTest"));

	tstring str = e.What();

	TEST_TRUE(str.find(TXT('{')) == tstring::npos);
}
{
	typedef WCL::ComPtr<ICreateErrorInfo> ICreateErrorInfoPtr;
	typedef WCL::ComPtr<IErrorInfo>       IErrorInfoPtr;

	ICreateErrorInfoPtr pCreateErrorInfo;
	HRESULT hr = ::CreateErrorInfo(AttachTo(pCreateErrorInfo));

	ASSERT(SUCCEEDED(hr));

	pCreateErrorInfo->SetSource(const_cast<wchar_t*>(L"Source"));
	pCreateErrorInfo->SetDescription(const_cast<wchar_t*>(L"Description"));

	IErrorInfoPtr pErrorInfo;
	hr = WCL::QueryInterface(pCreateErrorInfo, pErrorInfo);

	ASSERT(SUCCEEDED(hr));

	hr = ::SetErrorInfo(0, pErrorInfo.Get());

	ASSERT(SUCCEEDED(hr));

	typedef WCL::IFacePtr<IErrorLog> IErrorLogPtr;

	TestComClass		object;
	IErrorLogPtr		iface(&object);
	WCL::ComException	e(S_FALSE, iface, TXT("UnitTest"));

	tstring str = e.What();

	TEST_TRUE(str.find(TXT("Source")) != tstring::npos);
	TEST_TRUE(str.find(TXT("Description")) != tstring::npos);
}
}
