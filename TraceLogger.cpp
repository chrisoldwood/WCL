////////////////////////////////////////////////////////////////////////////////
//! \file   TraceLogger.cpp
//! \brief  The TraceLogger class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "TraceLogger.hpp"
#include "Path.hpp"
#include <stdio.h>
#include <tchar.h>

#if __GNUC__
// missing initializer for member 'X'
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
// Class members.

//! Trace log file path.
tchar TraceLogger::g_szTraceLog[];

//! Did last message include CRLF?
bool TraceLogger::g_bNewLine = true;

//! Disable ASSERT dialogs?
bool TraceLogger::g_bConsume = false;

////////////////////////////////////////////////////////////////////////////////
//! Install the logger.

void TraceLogger::Install()
{
#ifdef CORE_CRTDBG_ENABLED
	_CrtSetReportHook(ReportHook);
#endif
}

////////////////////////////////////////////////////////////////////////////////
//! Set the logfile.

void TraceLogger::SetLogFile(const tchar* pszLogFile)
{
	ASSERT(pszLogFile != nullptr);
	ASSERT(tstrlen(pszLogFile) <= MAX_PATH);

	tstrncpy(g_szTraceLog, pszLogFile, MAX_PATH);
}

////////////////////////////////////////////////////////////////////////////////
//! Set whether to display ASSERTs.

void TraceLogger::EnableDialogs(bool bEnable)
{
	g_bConsume = !bEnable;
}

////////////////////////////////////////////////////////////////////////////////
//! The CRT hook function to write all TRACE and ASSERTs to a file.

int TraceLogger::ReportHook(int /*nType*/, char* pszMessage, int* piRetVal)
{
	// Create default logfile path.
	if (g_szTraceLog[0] == TXT('\0'))
		tstrcpy(g_szTraceLog, CPath(CPath::ApplicationDir(), TXT("TraceLog.txt")));

	FILE* fLogFile = _tfopen(g_szTraceLog, TXT("a"));

	// Opened log file okay?
	if (fLogFile != nullptr)
	{
		// Start of new message?
		if (g_bNewLine)
		{
			SYSTEMTIME st = {0};

			::GetSystemTime(&st);

			// Write the date and time.
			fprintf(fLogFile, "[%02d/%02d/%04d %02d:%02d:%02d.%03d] ",
						st.wDay,  st.wMonth,  st.wYear,
						st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		}

		// Write the message and close.
		fputs(pszMessage, fLogFile);
		fclose(fLogFile);

		// Message ended with CRLF?
		for (const char* psz = pszMessage; *psz != '\0'; ++psz)
			g_bNewLine = ((*psz == '\r') || (*psz == '\n'));
	}

	// Don't force a debug break.
	*piRetVal = FALSE;

	// Chain to _CrtDbgReport.
	return g_bConsume;
}

//namespace WCL
}
