////////////////////////////////////////////////////////////////////////////////
//! \file   WinMain.hpp
//! \brief  Application entry point.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_WINMAIN_HPP
#define WCL_WINMAIN_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The logical (WCL) entry point for a Windows application.

int winMain(HINSTANCE hInstance, LPSTR lpszCmdLine, int nCmdShow);

//namespace WCL
}

#endif // WCL_WINMAIN_HPP
