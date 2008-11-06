////////////////////////////////////////////////////////////////////////////////
//! \file   ConsoleApp.cpp
//! \brief  The ConsoleApp class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ConsoleApp.hpp"
#include <Core/tiostream.hpp>
#include <Core/CmdLineException.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

ConsoleApp::ConsoleApp()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ConsoleApp::~ConsoleApp()
{
}

////////////////////////////////////////////////////////////////////////////////
//! The application C++ entry point. This should be invoked by the C based entry
//! point to run the application.

int ConsoleApp::main(int argc, tchar* argv[])
{
	int result = EXIT_FAILURE;

	try
	{
		result = run(argc, argv);
	}
	catch (const Core::CmdLineException& e)
	{
		tcerr << TXT("ERROR: ") << e.What() << std::endl;
		showUsage();
	}
	catch (const Core::Exception& e)
	{
		tcerr << TXT("ERROR: ") << e.What() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	catch (...)
	{
		tcerr << TXT("ERROR: An unknown exception occured") << std::endl;
	}

	tcout.flush();
	tcerr.flush();

	return result;
}

//namespace WCL
}
