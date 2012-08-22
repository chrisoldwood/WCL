////////////////////////////////////////////////////////////////////////////////
//! \file   CmdControlTests.cpp
//! \brief  The unit tests for the CCmdControl class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/CmdCtrl.hpp>
#include <WCL/ICommandWnd.hpp>

class TestCommandWnd : public WCL::ICommandWnd
{
public:
	virtual void OnCommandsUpdated()
	{ }
};

class TestCmdController : public CCmdControl
{
public:
	static const uint TEST_COMMAND_ID = 10;
	static const uint TEST_COMMAND_BMP_INDEX = 5;

	TestCmdController()
		: CCmdControl(m_commandWnd)
		, m_commandInvoked(false)
		, m_updateInvoked(false)
	{
		DEFINE_CMD_TABLE
			CMD_ENTRY(TEST_COMMAND_ID, &TestCmdController::onTestCommand, &TestCmdController::onUpdateTestCommandUi, TEST_COMMAND_BMP_INDEX)
		END_CMD_TABLE
	}

	void onTestCommand()
	{
		m_commandInvoked = true;
	}

	void onUpdateTestCommandUi()
	{
		m_updateInvoked = true;
	}

	TestCommandWnd	m_commandWnd;
	bool			m_commandInvoked;
	bool			m_updateInvoked;
};

TEST_SET(CmdControl)
{

TEST_CASE("Executing command should invoke command callback function")
{
	TestCmdController controller;

	controller.Execute(TestCmdController::TEST_COMMAND_ID);

	TEST_TRUE(controller.m_commandInvoked);
}
TEST_CASE_END

TEST_CASE("Executing unmapped command should not generate an error")
{
	const uint INVALID_COMMAND_ID = 99;

	TestCmdController controller;

	controller.Execute(INVALID_COMMAND_ID);

	TEST_FALSE(controller.m_commandInvoked);
}
TEST_CASE_END

TEST_CASE("Updating the UI should invoke update UI callback function")
{
	TestCmdController controller;

	controller.UpdateUI();

	TEST_TRUE(controller.m_updateInvoked);
}
TEST_CASE_END

TEST_CASE("Initialising the UI should cause the UI to be updated")
{
	TestCmdController controller;

	controller.InitialiseUI();

	TEST_TRUE(controller.m_updateInvoked);
}
TEST_CASE_END

}
TEST_SET_END
