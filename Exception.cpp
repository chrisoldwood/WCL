////////////////////////////////////////////////////////////////////////////////
//! \file   Exception.cpp
//! \brief  The Exception class definition and utility functions.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Exception.hpp"
#include "App.hpp"
#include <Core/AnsiWide.hpp>

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
//! Retrieve the error message in the native string format.

const tchar* CException::ErrorText() const
{
	return m_strErrorText;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the exception details.

const tchar* CException::What() const
{
	return m_strErrorText;
}

////////////////////////////////////////////////////////////////////////////////
//! Retrieve the ANSI only error message. For Unicode builds we create the ANSI
//! version of the error message on demand.

const char* CException::what() const
{
#ifdef ANSI_BUILD
	return m_strErrorText.c_str();
#else
	// Convert ANSI error message on demand.
	if (m_strAnsiText.empty())
		m_strAnsiText = Core::WideToAnsi(m_strErrorText.c_str(), m_strErrorText.c_str()+m_strErrorText.Length());

	return m_strAnsiText.c_str();
#endif
}

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
