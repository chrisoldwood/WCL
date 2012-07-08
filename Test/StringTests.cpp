////////////////////////////////////////////////////////////////////////////////
//! \file   StringTests.cpp
//! \brief  The unit tests for the CString class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <Core/tiosfwd.hpp>
#include <sstream>
#include <WCL/StringIO.hpp>

TEST_SET(String)
{
	CString str = CString::Fmt(TXT("%s"), TXT("Hello World"));

TEST_CASE("[in]equality operator performs a case-sensitive comparison")
{
	TEST_TRUE(str == TXT("Hello World"));
	TEST_TRUE(str != TXT("hello world"));
}
TEST_CASE_END

TEST_CASE("less operator performs a case-sensitive comparison")
{
	TEST_FALSE(str < TXT("HELLO WORLD"));
	TEST_TRUE (str < TXT("hello world"));
	TEST_FALSE(str < TXT("Hello World"));

	TEST_FALSE(str < CString(TXT("HELLO WORLD")));
	TEST_TRUE (str < CString(TXT("hello world")));
	TEST_FALSE(str < CString(TXT("Hello World")));
}
TEST_CASE_END

TEST_CASE("stream inserter writes character sequence")
{
	CString value(TXT("unit test"));

	tostringstream out;

	out << value;

	TEST_TRUE(tstrstr(out.str().c_str(), value.c_str()) != nullptr);
}
TEST_CASE_END

}
TEST_SET_END
