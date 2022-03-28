////////////////////////////////////////////////////////////////////////////////
//! \file   WinMain.cpp
//! \brief  Application entry point.
//! \author Chris Oldwood

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

namespace WCL
{

#if (__GNUC__ >= 8) // GCC 8+
// error: format '%hs' expects argument of type 'short int*', but argument 3 has type 'const char*' [-Werror=format=]
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif

////////////////////////////////////////////////////////////////////////////////
//! The logical (WCL) entry point for a Windows application.

int winMain(HINSTANCE hInstance,
			LPSTR     lpszCmdLine,
			int       nCmdShow)
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
		oApp.m_Module.m_hInstance = hInstance;
		oApp.m_strCmdLine         = A2T(lpszCmdLine);
		oApp.m_iCmdShow           = nCmdShow;

		// Open, run and close the app...
		if (oApp.Open())
		{
			oApp.Run();
			oApp.Close();

			// Get the WM_QUIT message result code.
			nResult = oApp.m_MainThread.Result();
		}
	}
	catch (const Core::Exception& e)
	{
		WCL::ReportUnhandledException(TXT("Unexpected exception caught in WinMain()\n\n%s"), e.twhat());
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

#if (__GNUC__ >= 8) // GCC 8+
#pragma GCC diagnostic pop
#endif

//namespace WCL
}

#ifndef __GNUG__

////////////////////////////////////////////////////////////////////////////////
//! This is the real (C SDK) entry point for a Windows application.
//!
//! \note This entry point is linked via a weak reference, which Visual C++
//! happily finds, but GCC doesn't seem to. One workaround is to copy this stub
//! to the application codebase where GCC will find it too.

extern "C" int WINAPI WinMain(HINSTANCE hInstance,
							  HINSTANCE /*hPrevInstance*/,
							  LPSTR     lpszCmdLine,
							  int       nCmdShow)
{
	return WCL::winMain(hInstance, lpszCmdLine, nCmdShow);
}

#endif //__GNUG__
