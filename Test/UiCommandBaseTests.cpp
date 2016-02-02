////////////////////////////////////////////////////////////////////////////////
//! \file   UiCommandBaseTests.cpp
//! \brief  The unit tests for the CCmdControl class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/UiCommandBase.hpp>
#include <WCL/DC.hpp>
#include "Resource.h"
#include <WCL/Module.hpp>
#include <WCL/ExternalCmdController.hpp>

namespace
{

class TestCommand : public WCL::UiCommandBase
{
public:
	TestCommand()
		: UiCommandBase(ID_TEST_COMMAND)
	{ }

	TestCommand(uint id)
		: UiCommandBase(id)
	{ }
};

const uint ID_UNDEFINED_COMMAND = 999;

}

TEST_SET(UiCommandBase)
{
	CModule module(::GetModuleHandle(NULL));

TEST_CASE("The default hint is the left 'half' of a resource string with the same ID")
{
	const tstring expected = WCL::ExternalCmdController::defaultHint(ID_TEST_COMMAND);

	TestCommand command;

	TEST_TRUE(command.hint() == expected);
}
TEST_CASE_END

TEST_CASE("The default tool tip is the right 'half' of a resource string with the same ID")
{
	const tstring expected = WCL::ExternalCmdController::defaultToolTip(ID_TEST_COMMAND);

	TestCommand command;

	TEST_TRUE(command.toolTip() == expected);
}
TEST_CASE_END

TEST_CASE("Executing does nothing by default")
{
	TestCommand command;

	command.execute();

	TEST_PASSED("No side effects observed");
}
TEST_CASE_END

TEST_CASE("Updating the UI does nothing by default")
{
	TestCommand command;

	command.updateUi();

	TEST_PASSED("No side effects observed");
}
TEST_CASE_END

TEST_CASE("Drawing the icon does nothing by default")
{
	CDC&  dc = *((CDC*)nullptr); // Shouldn't be invoked.
	CRect rect;

	TestCommand command;

	command.drawIcon(dc, rect, true);

	TEST_PASSED("No side effects observed");
}
TEST_CASE_END

}
TEST_SET_END
