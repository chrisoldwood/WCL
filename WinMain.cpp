/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WINMAIN.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	Application entry point.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <stdio.h>

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Trace log file path.
static char g_szTraceLog[MAX_PATH];

// Did last message include CRLF?
static bool g_bNewLine = true;				

// Disable ASSERT dialogs?
static bool g_bConsume = false;

/******************************************************************************
** Function: 	TraceLogger()
**
** Description:	The CRT hook function to write all TRACE and ASSERTs to a file.
**
** Parameters:	See _CrtSetReportHook.
**
** Returns:		See _CrtSetReportHook.
**
*******************************************************************************
*/

static int TraceLogger(int /*nType*/, char* pszMessage, int* piRetVal)
{
	// Create full logfile path.
	if (g_szTraceLog[0] == '\0')
		strcpy(g_szTraceLog, CPath(CPath::ApplicationDir(), "TraceLog.txt"));

	FILE* fLogFile = fopen(g_szTraceLog, "a");

	// Opened log file okay?
	if (fLogFile != NULL)
	{
		// Start of new message?
		if (g_bNewLine)
		{
			time_t	tTime  = time(NULL);
			tm*		pTime  = localtime(&tTime);
			char	szTime[50];

			// Write the date and time.
			strftime(szTime, sizeof(szTime), "[%d/%m/%y %H:%M:%S] ", pTime);
			fputs(szTime, fLogFile);
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

/******************************************************************************
** Function: 	WinMain()
**
** Description:	This is the entry point to the Windows app.
**
** Parameters:	hCurrInst	The current instance.
**				hPrevInst	The previous instance (NULL if none).
**				lpszCmdLine	The command line.
**				iCmdShow	The initial state of the window.
**
** Returns:		TRUE		For a premature exit.
**				FALSE		For a normal exit.
**
*******************************************************************************
*/

extern "C" int WINAPI WinMain(HINSTANCE hCurrInst, HINSTANCE /*hPrevInst*/, 
								LPSTR lpszCmdLine, int iCmdShow)
{
#ifdef _DEBUG
	// Set TRACE/ASSERT logging function.
	_CrtSetReportHook(TraceLogger);
#endif

	// Get application object.
	CApp& oApp = CApp::This();

	// Initialise members.
	oApp.m_Module.m_hInstance = hCurrInst;
	oApp.m_strCmdLine         = lpszCmdLine;	
	oApp.m_iCmdShow           = iCmdShow;

	// Open, run and close the app...
	if (oApp.Open())
		oApp.Run();

	oApp.Close();

	return FALSE;
}
