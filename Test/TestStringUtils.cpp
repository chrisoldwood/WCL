////////////////////////////////////////////////////////////////////////////////
//! \file   TestStringUtils.cpp
//! \brief  The unit tests for the string utility functions.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/StringUtils.hpp>
#include <WCL/Rect.hpp>

TEST_SET(StringUtils)
{
	TEST_TRUE(Core::format<>(CRect(1,2,3,4)) == TXT("1,2,3,4"));
	TEST_TRUE(Core::parse<CRect>(TXT("1,2,3,4")) == CRect(1,2,3,4));
	TEST_THROWS(Core::parse<CRect>(TXT("1,2,3")));
	TEST_THROWS(Core::parse<CRect>(TXT("A,B,C,D")));
}
TEST_SET_END
