////////////////////////////////////////////////////////////////////////////////
//! \file   MiscTests.cpp
//! \brief  The unit tests for the CRect class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/Rect.hpp>

TEST_SET(Rect)
{
	CRect rc;

	TEST_TRUE(rc.left == 0);
	TEST_TRUE(rc.top == 0);
	TEST_TRUE(rc.right == 0);
	TEST_TRUE(rc.bottom == 0);

	CRect rc1(1, 2, 3, 4);
	CRect rc2(1, 2, 3, 4);
	CRect rc3(-1, -2, -3, -4);

	TEST_TRUE(rc1 == rc2);
	TEST_TRUE(rc1 != rc3);
}
TEST_SET_END
