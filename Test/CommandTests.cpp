////////////////////////////////////////////////////////////////////////////////
//! \file   CommandTests.cpp
//! \brief  The unit tests for the Command class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include "Command.hpp"
#include <Core/CmdLineException.hpp>
#include <sstream>

static Core::CmdLineSwitch s_switches[] = 
{
	{ 1, TXT("?"), NULL, Core::CmdLineSwitch::ONCE, Core::CmdLineSwitch::NONE, NULL, TXT("Test") },
};
static size_t s_switchCount = ARRAY_SIZE(s_switches);

class TestCmd : public Command
{
public:
	TestCmd(int argc, tchar* argv[])
		: Command(s_switches, s_switches+s_switchCount, argc, argv)
		, m_description(TXT(""))
		, m_usage(TXT(""))
		, m_returnCode(-1)
		, m_exception(nullptr)
	{
	}

	const tchar* m_description;
	const tchar* m_usage;
	int m_returnCode;
	const tchar* m_exception;

private:
	virtual const tchar* getDescription()
	{
		return m_description;
	}

	virtual const tchar* getUsage()
	{
		return m_usage;
	}

	virtual int doExecute(tostream& /*out*/, tostream& /*err*/)
	{
		if (m_exception != nullptr)
			throw Core::CmdLineException(m_exception);
		else
			return m_returnCode;
	}
};

TEST_SET(Command)
{

TEST_CASE("execute should return result code from doExecute")
{
	const int expected = 42;

	tchar*    argv[] = { TXT("Test.exe"), TXT("command") };
	const int argc = ARRAY_SIZE(argv);

	TestCmd        command(argc, argv);
	tostringstream out, err;

	command.m_returnCode = expected;

	int result = command.execute(out, err);

	TEST_TRUE(result == expected);
}
TEST_CASE_END

TEST_CASE("execute should display command specific usage when a CmdLineException occurs")
{
	const tchar* expectedDescription = TXT("description");
	const tchar* expectedUsage = TXT("usage");
	const tchar* expectedException = TXT("error reason");
	const int    expectedReturnCode = EXIT_FAILURE;

	tchar*    argv[] = { TXT("Test.exe"), TXT("command") };
	const int argc = ARRAY_SIZE(argv);

	TestCmd        command(argc, argv);
	tostringstream out, err;

	command.m_description = expectedDescription;
	command.m_usage = expectedUsage;
	command.m_exception = expectedException;

	int result = command.execute(out, err);

	TEST_TRUE(result == expectedReturnCode);

	TEST_TRUE(tstrstr(out.str().c_str(), expectedDescription) != nullptr);
	TEST_TRUE(tstrstr(out.str().c_str(), expectedUsage) != nullptr);
	TEST_TRUE(tstrstr(err.str().c_str(), expectedException) != nullptr);
}
TEST_CASE_END

TEST_CASE("execute should display command specific usage when an invalid command switch is found")
{
	const tchar* expectedDescription = TXT("description");
	const tchar* expectedUsage = TXT("usage");
	const tchar* expectedException = TXT("--invalid-switch");
	const int    expectedReturnCode = EXIT_FAILURE;

	tchar*    argv[] = { TXT("Test.exe"), TXT("command"), TXT("--invalid-switch") };
	const int argc = ARRAY_SIZE(argv);

	TestCmd        command(argc, argv);
	tostringstream out, err;

	command.m_description = expectedDescription;
	command.m_usage = expectedUsage;
	command.m_exception = expectedException;

	int result = command.execute(out, err);

	TEST_TRUE(result == expectedReturnCode);

	TEST_TRUE(tstrstr(out.str().c_str(), expectedDescription) != nullptr);
	TEST_TRUE(tstrstr(out.str().c_str(), expectedUsage) != nullptr);
	TEST_TRUE(tstrstr(err.str().c_str(), expectedException) != nullptr);
}
TEST_CASE_END

}
TEST_SET_END
