////////////////////////////////////////////////////////////////////////////////
//! \file   ConsoleCmd.hpp
//! \brief  The ConsoleCmd class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_CONSOLECMD_HPP
#define WCL_CONSOLECMD_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/CmdLineParser.hpp>
#include <Core/tiosfwd.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The base class for all commands.

class ConsoleCmd
{
public:
	//! Destructor.
	virtual ~ConsoleCmd();

	//
	// Methods.
	//

	//! Execute the command.
	virtual int execute(tostream& out, tostream& err);

protected:
	//! Type aliases.
	typedef Core::CmdLineParser::SwitchCIter SwitchCIter;

	//! Default constructor.
	ConsoleCmd(SwitchCIter itFirstSwitch, SwitchCIter itLastSwitch, int argc, tchar* argv[], int usageId);

	//
	// Members.
	//
	int					m_argc;		//!< The number of command line arguments.
	tchar**				m_argv;		//!< The array of command line arguments
	Core::CmdLineParser m_parser;	//!< The command specifc command line parser.
	int					m_usageId;	//!< The ID of the usage switch.

	//
	// Callback methods.
	//

	//! Get the description of the command.
	virtual const tchar* getDescription() = 0;

	//! Get the expected command usage.
	virtual const tchar* getUsage() = 0;

	//! The implementation of the command.
	virtual int doExecute(tostream& out, tostream& err) = 0;

private:
	//! Display the command specific usage.
	void showUsage(tostream& out);
};

//! The default ConsoleCmd smart-pointer type.
typedef Core::SharedPtr<ConsoleCmd> ConsoleCmdPtr;

//namespace WCL
}

#endif // WCL_CONSOLECMD_HPP
