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

int ConsoleApp::Main(int nArgc, tchar* apszArgv[])
{
	int nResult = EXIT_FAILURE;

	try
	{
		nResult = Run(nArgc, apszArgv);
	}
	catch (const Core::CmdLineException& e)
	{
		tcout << TXT("ERROR: ") << e.What() << std::endl;
		ShowUsage();
	}
	catch (const Core::Exception& e)
	{
		tcout << TXT("ERROR: ") << e.What() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	catch (...)
	{
		tcout << TXT("ERROR: An unknown exception occured") << std::endl;
	}

	return nResult;
}

//namespace WCL
}
