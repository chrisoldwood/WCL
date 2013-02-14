////////////////////////////////////////////////////////////////////////////////
//! \file   ConsoleCmd.cpp
//! \brief  The ConsoleCmd class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ConsoleCmd.hpp"
#include <Core/CmdLineException.hpp>
#include <Core/tiostream.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

ConsoleCmd::ConsoleCmd(SwitchCIter itFirstSwitch, SwitchCIter itLastSwitch, int argc, tchar* argv[], int usageId)
	: m_argc(argc)
	, m_argv(argv)
	, m_parser(itFirstSwitch, itLastSwitch)
	, m_usageId(usageId)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ConsoleCmd::~ConsoleCmd()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Execute the command.

int ConsoleCmd::execute(tostream& out, tostream& err)
{
	try
	{
		// Parse the command line.
		m_parser.parse(m_argc, m_argv);

		// Request for command help?
		if (m_parser.isSwitchSet(m_usageId))
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

void ConsoleCmd::showUsage(tostream& out)
{
	out << std::endl;
	out << getDescription() << std::endl;
	out << std::endl;
	out << getUsage() << std::endl;
	out << std::endl;
	out << m_parser.formatSwitches(Core::CmdLineParser::UNIX);
}

//namespace WCL
}
