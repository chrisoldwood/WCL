////////////////////////////////////////////////////////////////////////////////
//! \file   ExternalCmdControllerTests.cpp
//! \brief  The unit tests for the ExternalCmdController class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ExternalCmdController.hpp>
#include <WCL/DC.hpp>
#include "Resource.h"
#include <WCL/Module.hpp>

namespace
{

class TestCommand : public WCL::IUiCommand
{
public:
	TestCommand()
		: m_id(ID)
		, m_commandInvoked(false)
		, m_updateInvoked(false)
		, m_drawInvoked(false)
	{ }

	TestCommand(uint id)
		: m_id(id)
		, m_commandInvoked(false)
		, m_updateInvoked(false)
		, m_drawInvoked(false)
	{ }

	virtual uint id() const
	{
		return m_id;
	}

	virtual tstring hint() const
	{
		return HINT;
	}

	virtual tstring toolTip() const
	{
		return TOOLTIP;
	}

	virtual void execute()
	{
		m_commandInvoked = true;
	}

	virtual void updateUi()
	{
		m_updateInvoked = true;
	}

	virtual void drawIcon(CDC& /*dc*/, const CRect& /*rect*/, bool /*enabled*/) const
	{
		m_drawInvoked = true;
	}

	uint m_id;
	bool m_commandInvoked;
	bool m_updateInvoked;
	mutable bool m_drawInvoked;

	static const uint ID = 42;
	static const tchar* HINT;
	static const tchar* TOOLTIP;
};

const tchar* TestCommand::HINT = TXT("hint");
const tchar* TestCommand::TOOLTIP = TXT("tooltip");

typedef Core::SharedPtr<TestCommand> TestCommandPtr;

const uint ID_UNDEFINED_COMMAND = 999;

}

TEST_SET(ExternalCmdController)
{
	CDC&  dc = *((CDC*)nullptr); // Shouldn't be invoked.
	CRect rect;

	CModule module(::GetModuleHandle(NULL));

TEST_CASE("Executing unmapped command should not generate an error")
{
	const uint INVALID_COMMAND_ID = 99;

	WCL::ExternalCmdController controller;

	controller.Execute(INVALID_COMMAND_ID);

	TEST_PASSED("No error thrown");
}
TEST_CASE_END

TEST_CASE("Executing command should invoke execute on command object")
{
	TestCommandPtr command(new TestCommand);

	std::vector<WCL::IUiCommandPtr> commands;

	commands.push_back(command);

	WCL::ExternalCmdController controller(commands);

	controller.Execute(command->id());

	TEST_TRUE(command->m_commandInvoked);
}
TEST_CASE_END

TEST_CASE("Updating the UI should invoke updateUi on the command object")
{
	TestCommandPtr command(new TestCommand);

	std::vector<WCL::IUiCommandPtr> commands;

	commands.push_back(command);

	WCL::ExternalCmdController controller(commands);

	controller.UpdateUI();

	TEST_TRUE(command->m_updateInvoked);
}
TEST_CASE_END

TEST_CASE("Querying the hint for an unmapped command should return the default")
{
	WCL::ExternalCmdController controller;

	CString hint = controller.CmdHintStr(ID_TEST_COMMAND);

	TEST_TRUE(hint == WCL::ExternalCmdController::defaultHint(ID_TEST_COMMAND));
}
TEST_CASE_END

TEST_CASE("Querying the hint for a command should invoke the command object")
{
	TestCommandPtr command(new TestCommand);

	std::vector<WCL::IUiCommandPtr> commands;

	commands.push_back(command);

	WCL::ExternalCmdController controller(commands);

	CString hint = controller.CmdHintStr(command->id());

	TEST_TRUE(hint == TestCommand::HINT);
}
TEST_CASE_END

TEST_CASE("Querying the tool tip for an unmapped command should return the default")
{
	WCL::ExternalCmdController controller;

	CString toolTip = controller.CmdToolTipStr(ID_TEST_COMMAND);

	TEST_TRUE(toolTip == WCL::ExternalCmdController::defaultToolTip(ID_TEST_COMMAND));
}
TEST_CASE_END

TEST_CASE("Querying the tool tip for a command should invoke the command object")
{
	TestCommandPtr command(new TestCommand);

	std::vector<WCL::IUiCommandPtr> commands;

	commands.push_back(command);

	WCL::ExternalCmdController controller(commands);

	CString toolTip = controller.CmdToolTipStr(command->id());

	TEST_TRUE(toolTip == TestCommand::TOOLTIP);
}
TEST_CASE_END

TEST_CASE("Registering a set of commands should add to the existing set")
{
	TestCommandPtr oldCommand(new TestCommand(10));

	std::vector<WCL::IUiCommandPtr> oldCommands;

	oldCommands.push_back(oldCommand);

	WCL::ExternalCmdController controller(oldCommands);

	TestCommandPtr newCommand(new TestCommand(20));

	std::vector<WCL::IUiCommandPtr> newCommands;

	newCommands.push_back(newCommand);

	controller.registerCommands(newCommands);

	controller.Execute(oldCommand->id());

	TEST_TRUE(oldCommand->m_commandInvoked);

	controller.Execute(newCommand->id());

	TEST_TRUE(newCommand->m_commandInvoked);
}
TEST_CASE_END

TEST_CASE("Registering a set of commands should replace the command where a duplicate ID exists")
{
	TestCommandPtr oldCommand(new TestCommand);

	std::vector<WCL::IUiCommandPtr> oldCommands;

	oldCommands.push_back(oldCommand);

	WCL::ExternalCmdController controller(oldCommands);

	TestCommandPtr newCommand(new TestCommand);

	std::vector<WCL::IUiCommandPtr> newCommands;

	newCommands.push_back(newCommand);

	controller.registerCommands(newCommands);

	controller.Execute(newCommand->id());

	TEST_FALSE(oldCommand->m_commandInvoked);
	TEST_TRUE(newCommand->m_commandInvoked);
}
TEST_CASE_END

TEST_CASE("Drawing the icon for an unmapped command should not generate an error")
{
	const uint INVALID_COMMAND_ID = 99;

	WCL::ExternalCmdController controller;

	controller.DrawCmd(INVALID_COMMAND_ID, dc, rect, true);

	TEST_PASSED("No error thrown");
}
TEST_CASE_END

TEST_CASE("Drawing the icon for a command should invoke execute on command object")
{
	TestCommandPtr command(new TestCommand);

	std::vector<WCL::IUiCommandPtr> commands;

	commands.push_back(command);

	WCL::ExternalCmdController controller(commands);

	controller.DrawCmd(command->id(), dc, rect, true);

	TEST_TRUE(command->m_drawInvoked);
}
TEST_CASE_END

TEST_CASE("The default hint for a command with no resource string defined is an empty string")
{
	const tchar* expected = TXT("");

	TEST_TRUE(WCL::ExternalCmdController::defaultHint(ID_UNDEFINED_COMMAND) == expected);
}
TEST_CASE_END

TEST_CASE("The default hint is the left 'half' of a resource string with the same ID")
{
	const tchar* expected = TXT("Hint");

	TEST_TRUE(WCL::ExternalCmdController::defaultHint(ID_TEST_COMMAND) == expected);
}
TEST_CASE_END

TEST_CASE("The default hint is the entire resource string when no tool tip is defined")
{
	const tchar* expected = TXT("Hint");

	TEST_TRUE(WCL::ExternalCmdController::defaultHint(ID_HINT_NO_TOOLTIP) == expected);
}
TEST_CASE_END

TEST_CASE("The default hint is the empty string when the resource string only has a tool tip defined")
{
	const tchar* expected = TXT("");

	TEST_TRUE(WCL::ExternalCmdController::defaultHint(ID_EMPTY_HINT) == expected);
}
TEST_CASE_END

TEST_CASE("The default tool tip for a command with no resource string defined is an empty string")
{
	const tchar* expected = TXT("");

	TEST_TRUE(WCL::ExternalCmdController::defaultToolTip(ID_UNDEFINED_COMMAND) == expected);
}
TEST_CASE_END

TEST_CASE("The default tool tip is the right 'half' of a resource string with the same ID")
{
	const tchar* expected = TXT("ToolTip");

	TEST_TRUE(WCL::ExternalCmdController::defaultToolTip(ID_TEST_COMMAND) == expected);
}
TEST_CASE_END

TEST_CASE("The default hint & tip is the empty string when the resource string only has a separator")
{
	const tchar* expected = TXT("");

	TEST_TRUE(WCL::ExternalCmdController::defaultHint(ID_HINT_TIP_SEP_ONLY) == expected);
	TEST_TRUE(WCL::ExternalCmdController::defaultToolTip(ID_HINT_TIP_SEP_ONLY) == expected);
}
TEST_CASE_END

}
TEST_SET_END
