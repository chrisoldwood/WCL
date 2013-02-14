////////////////////////////////////////////////////////////////////////////////
//! \file   Command.cpp
//! \brief  The Command class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Command.hpp"
#include <Core/CmdLineException.hpp>
#include "CmdLineArgs.hpp"
#include <Core/tiostream.hpp>

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Command::Command(SwitchCIter itFirstSwitch, SwitchCIter itLastSwitch, int argc, tchar* argv[])
	: m_argc(argc)
	, m_argv(argv)
	, m_parser(itFirstSwitch, itLastSwitch)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Command::~Command()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Execute the command.

int Command::execute(tostream& out, tostream& err)
{
	try
	{
		// Parse the command line.
		m_parser.parse(m_argc, m_argv);

		// Request for command help?
		if (m_parser.isSwitchSet(USAGE))
		{
			showUsage(out);
			return EXIT_SUCCESS;
		}

		// Execute it.
		return doExecute(out, err);
	}
	catch (const Core::CmdLineException& e)
	{
		err << TXT("ERROR: ") << e.twhat() << std::endl;
		showUsage(out);
		return EXIT_FAILURE;
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Display the command specific usage.

void Command::showUsage(tostream& out)
{
	out << std::endl;
	out << getDescription() << std::endl;
	out << std::endl;
	out << getUsage() << std::endl;
	out << std::endl;
	out << m_parser.formatSwitches(Core::CmdLineParser::UNIX);
}
