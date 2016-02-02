////////////////////////////////////////////////////////////////////////////////
//! \file   ComExceptionTests.cpp
//! \brief  The unit tests for the ComException class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/ComException.hpp>
#include <WCL/AutoCom.hpp>
#include <WCL/ComPtr.hpp>
#ifndef _MSC_VER
#include <ocidl.h>
#endif
#include "TestIFaceTraits.hpp"

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) // GCC 4.2+
// Caused by the DEBUG_USE_ONLY macro.
#pragma GCC diagnostic ignored "-Wunused-value"
#endif

class TestComClass : public IErrorLog,
					 public ISupportErrorInfo
{
public:
	virtual ~TestComClass()
	{ }

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

TEST_SET(ComException)
{

TEST_CASE("construction is from a result code and c-style string")
{
	const HRESULT testCode = E_FAIL;
	const tchar*  testMessage = TXT("UnitTest");

	WCL::ComException exception(testCode, testMessage);

	tstring message = exception.twhat();

	TEST_TRUE(exception.m_result == testCode);
	TEST_TRUE(message.find(testMessage) != tstring::npos);
}
TEST_CASE_END

TEST_CASE("construction is from a result code and a std::string")
{
	const HRESULT testCode = E_FAIL;
	const tstring testMessage = TXT("UnitTest");

	WCL::ComException exception(testCode, testMessage);

	tstring message = exception.twhat();

	TEST_TRUE(exception.m_result == testCode);
	TEST_TRUE(message.find(testMessage) != tstring::npos);
}
TEST_CASE_END

	WCL::AutoCom com(COINIT_APARTMENTTHREADED);

TEST_CASE("message contains the numeric value of the result code")
{
	const HRESULT testCode = E_FAIL;
	const tstring testCodeAsString = TXT("0x80004005");
	const tstring testMessage = TXT("UnitTest");

	WCL::ComException exception(testCode, testMessage);

	tstring message = exception.twhat();

	TEST_TRUE(message.find(testCodeAsString) != tstring::npos);
}
TEST_CASE_END

TEST_CASE("message contains some extra detail when constructed from an object supplying partial IErrorInfo details")
{
	typedef WCL::IFacePtr<IMalloc> IMallocPtr;

	IMallocPtr allocator;

	HRESULT hr = CoGetMalloc(1, WCL::AttachTo(allocator));

	ASSERT(hr == S_OK);
	DEBUG_USE_ONLY(hr);

	WCL::ComException exception(E_FAIL, allocator, TXT("UnitTest"));

	tstring str = exception.twhat();

	TEST_TRUE(exception.m_result == E_FAIL);
	TEST_TRUE(str.find(TXT('{')) == tstring::npos);
}
TEST_CASE_END

TEST_CASE("message contains full details when constructed from a complete IErrorInfo object")
{
	typedef WCL::ComPtr<ICreateErrorInfo> ICreateErrorInfoPtr;
	typedef WCL::ComPtr<IErrorInfo>       IErrorInfoPtr;

	ICreateErrorInfoPtr pCreateErrorInfo;
	HRESULT hr = ::CreateErrorInfo(AttachTo(pCreateErrorInfo));

	ASSERT(SUCCEEDED(hr));

	pCreateErrorInfo->SetSource(const_cast<wchar_t*>(L"TestSource"));
	pCreateErrorInfo->SetDescription(const_cast<wchar_t*>(L"TestDescription"));

	IErrorInfoPtr pErrorInfo;
	hr = WCL::QueryInterface(pCreateErrorInfo, pErrorInfo);

	ASSERT(SUCCEEDED(hr));

	hr = ::SetErrorInfo(0, pErrorInfo.get());

	ASSERT(SUCCEEDED(hr));

	typedef WCL::IFacePtr<IErrorLog> IErrorLogPtr;

	TestComClass		object;
	IErrorLogPtr		iface(&object);
	WCL::ComException	exception(E_POINTER, iface, TXT("UnitTest"));

	tstring str = exception.twhat();

	TEST_TRUE(exception.m_result == E_POINTER);
	TEST_TRUE(str.find(TXT("TestSource")) != tstring::npos);
	TEST_TRUE(str.find(TXT("TestDescription")) != tstring::npos);
}
TEST_CASE_END

}
TEST_SET_END
