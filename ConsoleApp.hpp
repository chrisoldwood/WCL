////////////////////////////////////////////////////////////////////////////////
//! \file   ConsoleApp.hpp
//! \brief  The ConsoleApp class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_CONSOLEAPP_HPP
#define WCL_CONSOLEAPP_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/CmdLineParser.hpp>
#include "MainThread.hpp"
#include <Core/tiosfwd.hpp>
#include <WCL/Event.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The base class for Console type applications.

class ConsoleApp
{
public:
	//! Destructor.
	virtual ~ConsoleApp();

	//
	// Properties.
	//

	//! Get the main thread.
	CMainThread& mainThread();

	//! Get the abort event.
	CEvent& getAbortEvent();

	//! Query if the app should terminate.
	bool isAbortSignalled() const;

	//
	// Methods.
	//

	//! Get the singleton object.
	static ConsoleApp& instance();

	//! The application C++ entry point.
	virtual int main(int argc, tchar* argv[], tistream& in, tostream& out, tostream& err);

protected:
	//
	// Members.
	//
	CMainThread		m_mainThread;	//!< The main application thread.
	CEvent			m_abortEvent;	//!< The event used to signal aborting of the app.

	//
	// Internal Methods.
	//

	//! Default constructor.
	ConsoleApp();

	//! Run the application.
	virtual int run(int nArgc, tchar* apszArgv[], tistream& in, tostream& out, tostream& err) = 0;

	//! Get the name of the application.
	virtual tstring applicationName() const = 0;

	//! Display the program options syntax.
	virtual void showUsage(tostream& out) const = 0;

	//! Display the program version.
	virtual void showVersion(tostream& out) const;

	//! Display the manual.
	virtual void showManual(tostream& err) const;

	//! The actual ctrl signal handler.
	static BOOL WINAPI ctrlHandler(DWORD signal);

	//! The ctrl signal handler.
	virtual BOOL onCtrlSignal(DWORD signal);
};

//namespace WCL
}

#endif // WCL_CONSOLEAPP_HPP
