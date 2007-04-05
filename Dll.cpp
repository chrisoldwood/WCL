/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DLL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDll class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

// Symbol used to ensure DllMain.cpp is linked.
extern bool g_bLinkDllMain;

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// The component object.
static CDll* pThis = NULL;

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
	// Ensure DllMain.cpp is linked in.
	g_bLinkDllMain = true;

	pThis = this;
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
	pThis = NULL;

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
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
	ASSERT(pThis != NULL);

	return *pThis;
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
	OnLoad();
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
	OnUnload();
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
	OnThreadAttached();
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
	OnThreadDetached();
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
