////////////////////////////////////////////////////////////////////////////////
//! \file   TestComStr.cpp
//! \brief  The unit tests for the ComStr class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ComStr.hpp>

TEST_SET(ComStr)
{
{
	WCL::ComStr bstr;

	TEST_TRUE(bstr.Get() == nullptr);
}
{
	WCL::ComStr bstr("Unit Test");

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
{
	WCL::ComStr bstr(L"Unit Test");

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
{
	CString     cstr(TXT("Unit Test"));
	WCL::ComStr bstr(cstr);

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
{
	tstring     tstr(TXT("Unit Test"));
	WCL::ComStr bstr(tstr);

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
{
	BSTR        raw(::SysAllocString(L"Unit Test"));
	WCL::ComStr bstr(raw);

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
{
	WCL::ComStr bstr(::SysAllocString(L"original"));

	bstr.Attach(::SysAllocString(L"Unit Test"));

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);

	::SysFreeString(bstr.Detach());

	TEST_TRUE(bstr.Get() == nullptr);
}
}
TEST_SET_END
