/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DLLMAIN.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	DLL entry point.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

// Symbol used to ensure DllMain.cpp is linked.
bool g_bLinkDllMain = false;

/******************************************************************************
** Function: 	DllMain()
**
** Description:	This is the entry point for the DLL.
**
** Parameters:	hInst		The instance.
**				dwReason	The reason flags.
**				lpvReserved	Reserved.
**
** Returns:		TRUE		For a premature exit.
**				FALSE		For a normal exit.
**
*******************************************************************************
*/

/*extern "C"*/
BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID /*lpvReserved*/)
{
	// Get dll object.
	CDll& oDll = CDll::This();

	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			// Initialise members.
			oDll.m_Module.m_hInstance = hInst;
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
	}

	return TRUE;
}
