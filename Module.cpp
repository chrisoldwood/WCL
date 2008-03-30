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
	//ASSERT(pThis == NULL);

	pThis = this;
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	This overload is only intended to be used during tesing.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CModule::CModule(HINSTANCE hInstance)
	: m_hInstance(hInstance)
{
	ASSERT(m_hInstance != NULL);
	//ASSERT(pThis == NULL);

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
	//ASSERT(pThis == this);

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
