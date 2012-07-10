////////////////////////////////////////////////////////////////////////////////
//! \file   DllMain.hpp
//! \brief  DLL entry point.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_DLLMAIN_HPP
#define WCL_DLLMAIN_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The logical (WCL) entry point for a Windows application.

BOOL dllMain(HINSTANCE hInstance, DWORD dwReason);

//namespace WCL
}

#endif // WCL_DLLMAIN_HPP
