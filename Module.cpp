/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MODULE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CModule class definition.
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

// The module object.
static CModule* pThis = NULL;

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

CModule::CModule()
	: m_hInstance(NULL)
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

CModule::~CModule()
{
	pThis = NULL;
}

/******************************************************************************
** Method:		This()
**
** Description:	Get the module object.
**
** Parameters:	None.
**
** Returns:		The module object.
**
*******************************************************************************
*/

CModule& CModule::This()
{
	ASSERT(pThis != NULL);

	return *pThis;
}
