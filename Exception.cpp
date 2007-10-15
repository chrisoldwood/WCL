////////////////////////////////////////////////////////////////////////////////
//! \file   Exception.cpp
//! \brief  The Exception class definition and utility functions.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Exception.hpp"
#include "App.hpp"

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

CException::CException()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

CException::~CException()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Retrieve the error message.
//! \deprecated This should be removed and what() used instead.

const char* CException::ErrorText() const
{
	return m_strErrorText;
}

////////////////////////////////////////////////////////////////////////////////
//! Retrieve the error message. This method is overriden from the base class.

const char* CException::what() const
{
	return m_strErrorText;
}

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Report an unhandled exception. This is called by all the outer try/catch
//! blocks to report an unexpected exception.

void ReportUnhandledException(const tchar* pszMsg, ...)
{
	ASSERT_FALSE();

	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Format message.
	strMsg.FormatEx(pszMsg, args);

	// Display message if an application.
	if (CApp::IsValid())
		CApp::This().FatalMsg(strMsg);
	else
		Core::DebugWrite("%s\n", strMsg);
}

//namespace WCL
}
