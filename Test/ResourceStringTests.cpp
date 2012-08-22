////////////////////////////////////////////////////////////////////////////////
//! \file   ResourceStringTests.cpp
//! \brief  The unit tests for the resource string utility functions.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ResourceString.hpp>
#include "Resource.h"

TEST_SET(ResourceString)
{
	HMODULE module = ::GetModuleHandle(NULL);

TEST_CASE("Loading a string for an invalid ID returns an empty string")
{
	const uint INVALID_STRING_ID = 999;
	const tstring expected = TXT("");

	const tstring actual = WCL::loadString(module, INVALID_STRING_ID);

	TEST_TRUE(actual == expected);
}
TEST_CASE_END

TEST_CASE("A string can be loaded from the application module resources")
{
	const tstring expected = TXT("unit test");
	const tstring actual = WCL::loadString(module, ID_TEST_STRING);

	TEST_TRUE(actual == expected);
}
TEST_CASE_END

}
TEST_SET_END
