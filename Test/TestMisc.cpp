////////////////////////////////////////////////////////////////////////////////
//! \file   TestMisc.cpp
//! \brief  The unit tests for misc types and functions.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/SeTranslator.hpp>
#include <WCL/StructuredException.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for other misc types and functions.

void TestSE()
{
	WCL::SeTranslator oSeTranslator;

	tchar* p = nullptr;

	TEST_THROWS(*p = TXT('\0'));
}

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for other misc types and functions.

void TestMisc()
{
	TestSE();
}
