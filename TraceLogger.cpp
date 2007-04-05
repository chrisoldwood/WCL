////////////////////////////////////////////////////////////////////////////////
//! \author Chris Oldwood
//! \file   TraceLogger.cpp
//! \brief  The TraceLogger class definition.

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
// Class members.

//! Trace log file path.
char TraceLogger::g_szTraceLog[];

//! Did last message include CRLF?
bool TraceLogger::g_bNewLine = true;

//! Disable ASSERT dialogs?
bool TraceLogger::g_bConsume = false;

////////////////////////////////////////////////////////////////////////////////
//! Install the logger..

void TraceLogger::Install()
{
	_CrtSetReportHook(ReportHook);
}

////////////////////////////////////////////////////////////////////////////////
//! Set the logfile.

void TraceLogger::SetLogFile(const char* pszLogFile)
{
	ASSERT(pszLogFile != NULL);
	ASSERT(strlen(pszLogFile) <= MAX_PATH);

	strncpy(g_szTraceLog, pszLogFile, MAX_PATH);
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
	if (g_szTraceLog[0] == '\0')
		strcpy(g_szTraceLog, CPath(CPath::ApplicationDir(), "TraceLog.txt"));

	FILE* fLogFile = fopen(g_szTraceLog, "a");

	// Opened log file okay?
	if (fLogFile != NULL)
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
		for (const char* psz = pszMessage; *psz != '\0'; psz++)
			g_bNewLine = ((*psz == '\r') || (*psz == '\n'));
	}

	// Don't force a debug break.
	*piRetVal = FALSE;

	// Chain to _CrtDbgReport.
	return g_bConsume;
}

//namespace WCL
}
