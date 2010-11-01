////////////////////////////////////////////////////////////////////////////////
//! \file   SeTranslatorTests.cpp
//! \brief  The unit tests for the SeTranslator class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/SeTranslator.hpp>
#include <WCL/StructuredException.hpp>

TEST_SET(SeTranslator)
{

TEST_CASE("dereferencing a null pointer causes an access violation exception to occur")
{
	WCL::SeTranslator oSeTranslator;

	tchar* p = nullptr;

	try
	{
		*p = TXT('\0');

		TEST_FAILED("No exception thrown");
	}
	catch (const WCL::StructuredException& /*e*/)
	{
		TEST_PASSED("StructuredException thrown");
	}
	catch (...)
	{
		TEST_FAILED("Non StructuredException exception thrown");
	}
}
TEST_CASE_END

}
TEST_SET_END
