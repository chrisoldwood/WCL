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

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The base class for Console type applications.

class ConsoleApp
{
public:
	//! Default constructor.
	ConsoleApp();

	//! Destructor.
	virtual ~ConsoleApp();

	//
	// Properties.
	//

	//! Get the main thread.
	CMainThread& mainThread();

	//! Get if the app should terminate.
	bool abort() const;

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
	volatile bool	m_abort;		//!< The flag to signal aborting of the app.

	//
	// Internal Methods.
	//

	//! Run the application.
	virtual int run(int nArgc, tchar* apszArgv[], tistream& in, tostream& out, tostream& err) = 0;

	//! Display the program options syntax.
	virtual void showUsage(tostream& out) = 0;

	//! The actual ctrl signal handler.
	static BOOL WINAPI ctrlHandler(DWORD signal);

	//! The ctrl signal handler.
	virtual BOOL onCtrlSignal(DWORD signal);
};

////////////////////////////////////////////////////////////////////////////////
//! Get the main thread.

inline CMainThread& ConsoleApp::mainThread()
{
	return m_mainThread;
}

////////////////////////////////////////////////////////////////////////////////
//! Get if the app should terminate.

inline bool ConsoleApp::abort() const
{
	return m_abort;
}

//namespace WCL
}

#endif // WCL_CONSOLEAPP_HPP
