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

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// The application object.
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
** Returns:		true or false.
**
*******************************************************************************
*/

bool CDll::Load()
{
	return OnLoad();
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
** Method:		OnLoad()
**				OnUnload()
**
** Description:	Default versions of the template methods called by the Load()
**				and Unload() methods during dll startup and shutdown.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CDll::OnLoad()
{
	return true;
}

bool CDll::OnUnload()
{
	return true;
}
