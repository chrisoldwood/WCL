/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DLL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDll class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Dll.hpp"
#include "TraceLogger.hpp"

#if (__GNUC__ >= 8) // GCC 8+
// error: format '%hs' expects argument of type 'short int*', but argument 3 has type 'const char*' [-Werror=format=]
#pragma GCC diagnostic ignored "-Wformat"
#endif

#ifdef _MSC_VER
// Linker directives.
// NB: Required for building with VC++ Express.
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "advapi32")
#pragma comment(lib, "comctl32")
#pragma comment(lib, "ole32")
#endif

// Symbol used to ensure DllMain.cpp is linked.
extern bool g_bLinkDllMain;

/******************************************************************************
**
** Class members.
**
*******************************************************************************
*/

//! The singleton DLL component object.
CDll* CDll::g_pThis = NULL;

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDll::CDll()
	: m_Module()
{
	ASSERT(g_pThis == nullptr);

	// Ensure DllMain.cpp is linked in.
	g_bLinkDllMain = true;

	g_pThis = this;

	// Report memory leaks.
//	Core::EnableLeakReporting(true);
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDll::~CDll()
{
	ASSERT(g_pThis == this);

	g_pThis = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//! Check if the app singleton is valid.

bool CDll::IsValid()
{
	return (g_pThis != nullptr);
}

/******************************************************************************
** Method:		This()
**
** Description:	Get the dll object.
**
** Parameters:	None.
**
** Returns:		The dll object.
**
*******************************************************************************
*/

CDll& CDll::This()
{
	ASSERT(g_pThis != nullptr);

	return *g_pThis;
}

/******************************************************************************
** Method:		Load()
**
** Description:	Called by DllMain when the dll is first loaded.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDll::Load()
{
	try
	{
#ifdef _DEBUG
		// Install TRACE/ASSERT logging function.
		WCL::TraceLogger::Install();
#endif

		OnLoad();
	}
	catch (const std::exception& e)
	{
		Core::debugWrite(TXT("Unhandled exception caught in CDll::Load() - %hs\n"), e.what());
	}
}

/******************************************************************************
** Method:		Unload()
**
** Description:	Called by DllMain just before unloading the dll.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDll::Unload()
{
	try
	{
		OnUnload();
	}
	catch (const std::exception& e)
	{
		Core::debugWrite(TXT("Unhandled exception caught in CDll::OnUnload() - %hs\n"), e.what());
	}
}

/******************************************************************************
** Method:		ThreadAttached()
**
** Description:	Called by DllMain when a new thread has started.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDll::ThreadAttached()
{
	try
	{
		OnThreadAttached();
	}
	catch (const std::exception& e)
	{
		Core::debugWrite(TXT("Unhandled exception caught in CDll::OnThreadAttached() - %hs\n"), e.what());
	}
}

/******************************************************************************
** Method:		ThreadDetached()
**
** Description:	Called by DllMain when an existing thread has terminated.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDll::ThreadDetached()
{
	try
	{
		OnThreadDetached();
	}
	catch (const std::exception& e)
	{
		Core::debugWrite(TXT("Unhandled exception caught in CDll::OnThreadDetached() - %hs\n"), e.what());
	}
}

/******************************************************************************
** Methods:		OnLoad()
**				OnUnload()
**				OnThreadAttached()
**				OnThreadDetached()
**
** Description:	Default versions of the template methods called by the private
**				entry point methods from DllMain().
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDll::OnLoad()
{
}

void CDll::OnUnload()
{
}

void CDll::OnThreadAttached()
{
}

void CDll::OnThreadDetached()
{
}
