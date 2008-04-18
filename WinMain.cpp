/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WINMAIN.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	Application entry point.
**
*******************************************************************************
*/

#include "Common.hpp"
#include <stdio.h>
#include <locale.h>
#include "TraceLogger.hpp"
#include "App.hpp"
#include "SeTranslator.hpp"
#include "MsgThread.hpp"
#include "Exception.hpp"
#include <Core/AnsiWide.hpp>
#include <tchar.h>

// Using declarations.
using namespace WCL;

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
	int nResult = CMsgThread::THREAD_EXIT_FAILURE;

	// Translate structured exceptions.
	WCL::SeTranslator::Install();

	try
	{
#ifdef _DEBUG
		// Install TRACE/ASSERT logging function.
		TraceLogger::Install();
#endif

		// Use the Windows locale.
		setlocale(LC_ALL, "");

		// Get application object.
		CApp& oApp = CApp::This();

		// Initialise members.
		oApp.m_Module.m_hInstance = hCurrInst;
		oApp.m_strCmdLine         = A2T(lpszCmdLine);	
		oApp.m_iCmdShow           = iCmdShow;

		// Open, run and close the app...
		if (oApp.Open())
			oApp.Run();

		oApp.Close();

		// Get the WM_QUIT message result code.
		nResult = oApp.m_MainThread.Result();
	}
	catch (const Core::Exception& e)
	{
		WCL::ReportUnhandledException(TXT("Unexpected exception caught in WinMain()\n\n%s"), e.What());
	}
	catch (const std::exception& e)
	{
		WCL::ReportUnhandledException(TXT("Unexpected exception caught in WinMain()\n\n%hs"), e.what());
	}
	catch (...)
	{
		WCL::ReportUnhandledException(TXT("Unexpected unknown exception caught in WinMain()"));
	}

	return nResult;
}
