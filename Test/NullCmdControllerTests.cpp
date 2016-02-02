////////////////////////////////////////////////////////////////////////////////
//! \file   NullCmdControllerTests.cpp
//! \brief  The unit tests for the NullCmdController class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/NullCmdController.hpp>
#include <WCL/DC.hpp>
#include <Core/UniquePtr.hpp>

TEST_SET(NullCmdController)
{

TEST_CASE("All methods should throw a not implemented exception")
{
	typedef Core::UniquePtr<WCL::ICmdController> ICmdControllerPtr;

	const uint TEST_COMMAND_ID = 99;

	ICmdControllerPtr controller(new WCL::NullCmdController);

	TEST_THROWS(controller->Execute(TEST_COMMAND_ID));

	TEST_THROWS(controller->UpdateUI());

	CDC& dc = *((CDC*)nullptr); // Shouldn't be invoked.

	TEST_THROWS(controller->DrawCmd(TEST_COMMAND_ID, dc, CRect(), true));

	TEST_THROWS(controller->CmdHintStr(TEST_COMMAND_ID));

	TEST_THROWS(controller->CmdToolTipStr(TEST_COMMAND_ID));
}
TEST_CASE_END

}
TEST_SET_END
