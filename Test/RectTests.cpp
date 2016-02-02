////////////////////////////////////////////////////////////////////////////////
//! \file   MiscTests.cpp
//! \brief  The unit tests for the CRect class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/Rect.hpp>

TEST_SET(Rect)
{

TEST_CASE("initial state is an empty rectangle positioned at the origin")
{
	CRect rc;

	TEST_TRUE(rc.Empty());	

	TEST_TRUE(rc.left == 0);
	TEST_TRUE(rc.top == 0);
	TEST_TRUE(rc.right == 0);
	TEST_TRUE(rc.bottom == 0);
}
TEST_CASE_END

TEST_CASE("equality is dependent on the left, top, right and bottom members being equal")
{
	CRect rect(1, 2, 3, 4);

	TEST_TRUE(rect == rect);

	TEST_TRUE(rect != CRect(0, 2, 3, 4));
	TEST_TRUE(rect != CRect(1, 0, 3, 4));
	TEST_TRUE(rect != CRect(1, 2, 0, 4));
	TEST_TRUE(rect != CRect(1, 2, 3, 0));
}
TEST_CASE_END

}
TEST_SET_END
