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
{
	ASSERT(g_pThis == NULL);

	// Ensure DllMain.cpp is linked in.
	g_bLinkDllMain = true;

	g_pThis = this;
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

	g_pThis = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//! Check if the app singleton is valid.

bool CDll::IsValid()
{
	return (g_pThis != NULL);
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
	ASSERT(g_pThis != NULL);

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
		Core::DebugWrite("Unhandled exception caught in CDll::Load() - %s\n", e.what());
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
		Core::DebugWrite("Unhandled exception caught in CDll::OnUnload() - %s\n", e.what());
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
		Core::DebugWrite("Unhandled exception caught in CDll::OnThreadAttached() - %s\n", e.what());
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
		Core::DebugWrite("Unhandled exception caught in CDll::OnThreadDetached() - %s\n", e.what());
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
