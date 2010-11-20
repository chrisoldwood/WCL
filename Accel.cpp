/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCEL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CAccel class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Accel.hpp"
#include "Module.hpp"

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

CAccel::CAccel()
	: m_hAccel(NULL)
{
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

CAccel::~CAccel()
{
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads an accelerator table from the resource file.
**
** Parameters:	iRscID		The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccel::LoadRsc(uint iRscID)
{
	ASSERT(m_hAccel == NULL);

	// Load the resource.
	m_hAccel = ::LoadAccelerators(CModule::This().Handle(), MAKEINTRESOURCE(iRscID));

	ASSERT(m_hAccel != NULL);
}

/******************************************************************************
** Method:		Translate()
**
** Description:	Attempts to translate an accelerator keystroke.
**
** Parameters:	hWnd	The message window destination.
**				pMsg	The message.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CAccel::Translate(HWND hWnd, MSG& rMsg)
{
	// Attempt to translate it.
	if (m_hAccel)
		return TranslateAccelerator(hWnd, m_hAccel, &rMsg);

	return false;
}
