////////////////////////////////////////////////////////////////////////////////
//! \file   StringTests.cpp
//! \brief  The unit tests for the CString class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>

TEST_SET(String)
{
	CString str = CString::Fmt(TXT("%s"), TXT("Hello World"));

	TEST_TRUE(str == TXT("Hello World"));
	TEST_TRUE(str != TXT("hello world"));

	TEST_FALSE(str < TXT("HELLO WORLD"));
	TEST_TRUE (str < TXT("hello world"));
	TEST_FALSE(str < TXT("Hello World"));

	TEST_FALSE(str < CString(TXT("HELLO WORLD")));
	TEST_TRUE (str < CString(TXT("hello world")));
	TEST_FALSE(str < CString(TXT("Hello World")));
}
TEST_SET_END
