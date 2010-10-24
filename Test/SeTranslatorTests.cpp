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
	WCL::SeTranslator oSeTranslator;

	tchar* p = nullptr;

	TEST_THROWS(*p = TXT('\0'));
}
TEST_SET_END
