////////////////////////////////////////////////////////////////////////////////
//! \file   DllMain.cpp
//! \brief  DLL entry point.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Dll.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The logical (WCL) entry point for a Windows DLL.

BOOL dllMain(HINSTANCE hInstance, DWORD dwReason)
{
	// Get dll object.
	CDll& oDll = CDll::This();

	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			// Initialise members.
			oDll.m_Module.m_hInstance = hInstance;
			oDll.Load();
			break;

		case DLL_THREAD_ATTACH:
			oDll.ThreadAttached();
			break;

		case DLL_THREAD_DETACH:
			oDll.ThreadDetached();
			break;

		case DLL_PROCESS_DETACH:
			oDll.Unload();
			break;

		default:
			ASSERT_FALSE();
			break;
	}

	return TRUE;
}

//namespace WCL
}

#ifdef __GNUG__
// no previous declaration for 'BOOL DllMain(HINSTANCE__*, DWORD, void*)'
extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
#endif

// Symbol used to ensure DllMain.cpp is linked.
bool g_bLinkDllMain = false;

////////////////////////////////////////////////////////////////////////////////
//! This is the real (C SDK) entry point for a Windows DLL.
//!
//! \note This entry point is linked by virtue of the CDll class referencing the
//! symbol above. If you're not using the CDll class you'll either need to do
//! the same or copy the stub below to the Dll project codebase.

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/)
{
	return WCL::dllMain(hInstance, dwReason);
}
