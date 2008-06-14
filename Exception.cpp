////////////////////////////////////////////////////////////////////////////////
//! \file   Exception.cpp
//! \brief  The Exception class definition and utility functions.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Exception.hpp"
#include "App.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Report an unhandled exception. This is called by all the outer try/catch
//! blocks to report an unexpected exception.

void ReportUnhandledException(const tchar* pszMsg, ...)
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Format message.
	strMsg.FormatEx(pszMsg, args);

	// Display message if an application.
	if (CApp::IsValid())
	{
		CApp::This().FatalMsg(strMsg);
	}
	// Otherwise send to debugger.
	else
	{
		ASSERT_FALSE();

		Core::DebugWrite(TXT("%s\n"), strMsg);
	}
}

//namespace WCL
}
