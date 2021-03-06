////////////////////////////////////////////////////////////////////////////////
//! \file   ComStrTests.cpp
//! \brief  The unit tests for the ComStr class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/ComStr.hpp>

TEST_SET(ComStr)
{

TEST_CASE("initial state is a null pointer")
{
	WCL::ComStr bstr;

	TEST_TRUE(bstr.Get() == nullptr);
}
TEST_CASE_END

TEST_CASE("string can be constructed from an ANSI string")
{
	WCL::ComStr bstr("Unit Test");

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE("string can be constructed from an Unicode string")
{
	WCL::ComStr bstr(L"Unit Test");

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE("string can be constructed from a CString")
{
	CString     cstr(TXT("Unit Test"));
	WCL::ComStr bstr(cstr);

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE("string can be constructed from a std::string")
{
	tstring     tstr(TXT("Unit Test"));
	WCL::ComStr bstr(tstr);

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE("string can be constructed from a BSTR (a non-const Unicode string)")
{
	BSTR        raw(::SysAllocString(L"Unit Test"));
	WCL::ComStr bstr(raw);

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE("a string can be manually attached and detached from the holder")
{
	WCL::ComStr bstr(::SysAllocString(L"original"));

	bstr.Attach(::SysAllocString(L"Unit Test"));

	TEST_TRUE(wcscmp(bstr.Get(), L"Unit Test") == 0);

	::SysFreeString(bstr.Detach());

	TEST_TRUE(bstr.Get() == nullptr);
}
TEST_CASE_END

TEST_CASE("smart pointer unaware functions can attach a pointer to an empty instance")
{
	WCL::ComStr test;

	BSTR expected = ::SysAllocString(L"Unit Test");

	*AttachTo(test) = expected;

	TEST_TRUE(test.Get() == expected);
}
TEST_CASE_END

TEST_CASE("attaching a pointer to a non-empty smart pointer throws an exception")
{
	WCL::ComStr test("Unit Test");

	TEST_THROWS(AttachTo(test));
}
TEST_CASE_END

TEST_CASE("the string is empty when it owns nothing")
{
	const WCL::ComStr test;

	TEST_TRUE(test.Empty());
}
TEST_CASE_END

TEST_CASE("the string is not empty when it owns something")
{
	const WCL::ComStr test("Unit Test");

	TEST_FALSE(test.Empty());
}
TEST_CASE_END

}
TEST_SET_END
