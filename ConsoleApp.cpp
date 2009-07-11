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
// Local variables.

//! The singleton application object.
static ConsoleApp* g_this = NULL;

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

ConsoleApp::ConsoleApp()
	: m_abort(false)
{
	ASSERT(g_this == nullptr);

	g_this = this;

	// Install the ctrl-c handler.
	::SetConsoleCtrlHandler(ctrlHandler, TRUE);

	// Report memory leaks.
	Core::enableLeakReporting(true);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ConsoleApp::~ConsoleApp()
{
	ASSERT(g_this == this);

	// Remove the ctrl-c handler.
	::SetConsoleCtrlHandler(ctrlHandler, FALSE);

	g_this = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the singleton object.

ConsoleApp& ConsoleApp::instance()
{
	ASSERT(g_this != nullptr);

	return *g_this;
}

////////////////////////////////////////////////////////////////////////////////
//! The application C++ entry point. This should be invoked by the C based entry
//! point to run the application.

int ConsoleApp::main(int argc, tchar* argv[])
{
	int result = EXIT_FAILURE;

	try
	{
		// Run the app.
		result = run(argc, argv);
	}
	catch (const Core::CmdLineException& e)
	{
		tcerr << TXT("ERROR: ") << e.twhat() << std::endl;
		showUsage();
	}
	catch (const Core::Exception& e)
	{
		tcerr << TXT("ERROR: ") << e.twhat() << std::endl;
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

////////////////////////////////////////////////////////////////////////////////
//! The actual ctrl signal handler.

BOOL WINAPI ConsoleApp::ctrlHandler(DWORD signal)
{
	return instance().onCtrlSignal(signal);
}

////////////////////////////////////////////////////////////////////////////////
//! The ctrl signal handler.

BOOL ConsoleApp::onCtrlSignal(DWORD /*signal*/)
{
	m_abort = true;
	m_mainThread.PostMessage(WM_QUIT, CMsgThread::THREAD_EXIT_FAILURE);

	return TRUE;
}

//namespace WCL
}
