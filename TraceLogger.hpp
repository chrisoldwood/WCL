////////////////////////////////////////////////////////////////////////////////
//! \file   TraceLogger.hpp
//! \brief  The TraceLogger class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef TRACELOGGER_HPP
#define TRACELOGGER_HPP

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The logger used to write CRT output message to a file. This class consists
//! entirely of static members and functions as once installed, it can never be
//! uninstalled.

class TraceLogger
{
public:
	//! Install the logger..
	static void Install();

	//! Set the logfile.
	static void SetLogFile(const char* pszLogFile);

	//! Set whether to display ASSERTs.
	static void EnableDialogs(bool bEnable);

private:
	//
	// Class members.
	//
	static char g_szTraceLog[MAX_PATH+1];	//!< Trace log file path.
	static bool g_bNewLine;					//!< Did last message include CRLF?
	static bool g_bConsume;					//!< Disable ASSERT dialogs?

	//! The CRT callback.function.
	static int ReportHook(int /*nType*/, char* pszMessage, int* piRetVal);
};

//namespace WCL
}

#endif // TRACELOGGER_HPP
