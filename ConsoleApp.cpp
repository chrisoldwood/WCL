////////////////////////////////////////////////////////////////////////////////
//! \file   ConsoleApp.cpp
//! \brief  The ConsoleApp class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ConsoleApp.hpp"
#include <Core/CmdLineException.hpp>
#include <ostream>
#include <WCL/Path.hpp>
#include <WCL/VerInfoReader.hpp>
#include "StrCvt.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
// Local variables.

//! The singleton application object.
static ConsoleApp* g_this = NULL;

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

ConsoleApp::ConsoleApp()
	: m_abortEvent(CEvent::MANUAL, CEvent::NOT_SIGNALLED)
{
	ASSERT(g_this == nullptr);

	g_this = this;

	// Install the ctrl-c handler.
	BOOL installed = ::SetConsoleCtrlHandler(ctrlHandler, TRUE);

	if (!installed)
	{
		tstring message = CStrCvt::FormatError().c_str();

		Core::debugWrite(TXT("Failed to install Ctrl+C handler - %s"), message.c_str());
	}

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

int ConsoleApp::main(int argc, tchar* argv[], tistream& in, tostream& out, tostream& err)
{
	int result = EXIT_FAILURE;

	try
	{
		// Run the app.
		result = run(argc, argv, in, out, err);
	}
	catch (const Core::CmdLineException& e)
	{
		err << TXT("ERROR: ") << e.twhat() << std::endl;
		showUsage(out);
	}
	catch (const Core::Exception& e)
	{
		err << TXT("ERROR: ") << e.twhat() << std::endl;
	}
	catch (const std::exception& e)
	{
		err << "ERROR: " << e.what() << std::endl;
	}
	catch (...)
	{
		err << TXT("ERROR: An unknown exception occured") << std::endl;
	}

	out.flush();
	err.flush();

	return result;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the main thread.

CMainThread& ConsoleApp::mainThread()
{
	return m_mainThread;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the abort event.

CEvent& ConsoleApp::getAbortEvent()
{
	return m_abortEvent;
}

////////////////////////////////////////////////////////////////////////////////
//! Query if the app should terminate.

bool ConsoleApp::isAbortSignalled() const
{
	return m_abortEvent.IsSignalled();
}

////////////////////////////////////////////////////////////////////////////////
//! Display the program version.

void ConsoleApp::showVersion(tostream& out) const
{
	// Extract details from the resources.
	tstring filename  = CPath::Application().c_str();
	tstring version   = WCL::VerInfoReader::GetStringValue(filename, WCL::VerInfoReader::PRODUCT_VERSION);
	tstring copyright = WCL::VerInfoReader::GetStringValue(filename, WCL::VerInfoReader::LEGAL_COPYRIGHT);

#ifdef ANSI_BUILD
	version += TXT(" [ANSI]");
#endif

#ifdef _DEBUG
	version += TXT(" [Debug]");
#endif

	// Display version etc.
	out << std::endl;
	out << applicationName() << TXT(" v") << version << std::endl;
	out << std::endl;
	out << copyright << std::endl;
	out << TXT("gort@cix.co.uk") << std::endl;
	out << TXT("www.chrisoldwood.com") << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//! Display the manual.

void ConsoleApp::showManual(tostream& err) const
{
	tstring processName = CPath::Application().FileTitle().c_str();

	// Look for .mht based helpfile first.
	tstring helpfile_mht = processName + TXT(".mht");
	CPath   fullpath_mht = CPath::ApplicationDir() / helpfile_mht.c_str();

	if (fullpath_mht.Exists())
	{
		::ShellExecute(NULL, NULL, fullpath_mht.c_str(), NULL, NULL, SW_SHOW);
	}

	// Fall back to .html based helpfile.
	tstring helpfile_html = processName + TXT(".html");
	CPath   fullpath_html = CPath::ApplicationDir() / helpfile_html.c_str();

	if (fullpath_html.Exists())
	{
		::ShellExecute(NULL, NULL, fullpath_html, NULL, NULL, SW_SHOW);
	}

	err << TXT("ERROR: Manual missing - '") << fullpath_html.c_str() << TXT("'") << std::endl;
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
	m_abortEvent.Signal();

	return TRUE;
}

//namespace WCL
}
