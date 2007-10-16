/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MODULE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CModule class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Module.hpp"

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

////////////////////////////////////////////////////////////////////////////////
//! Get the full path to the module.

CPath CModule::Path() const
{
	ASSERT(m_hInstance != NULL);

	return CPath::Module(m_hInstance);
}
