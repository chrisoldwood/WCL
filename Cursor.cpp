/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CURSOR.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCursor class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Cursor.hpp"
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

CCursor::CCursor()
	: m_hCursor(NULL)
	, m_bOwner(false)
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

CCursor::~CCursor()
{
	Release();
}

////////////////////////////////////////////////////////////////////////////////
//! Release the resource.

void CCursor::Release()
{
	// Aquired AND we own it?
	if ( (m_hCursor != NULL) && m_bOwner )
		::DestroyCursor(m_hCursor);

	// Reset state.
	m_hCursor = NULL;
	m_bOwner  = false;
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads the cursor from the resource file.
**
** Parameters:	iRscID		The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCursor::LoadRsc(uint nRscID)
{
	ASSERT(m_hCursor == NULL);

	m_hCursor = ::LoadCursor(CModule::This().Handle(), MAKEINTRESOURCE(nRscID));
	m_bOwner  = false;

	ASSERT(m_hCursor != NULL);
}

void CCursor::LoadRsc(const tchar* pszRsc)
{
	ASSERT(m_hCursor == NULL);

	m_hCursor = ::LoadCursor(NULL, pszRsc);
	m_bOwner  = false;

	ASSERT(m_hCursor != NULL);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the current cursor postion in screen co-ordinates.

CPoint CCursor::CurrentPos()
{
	CPoint ptCursor;

	::GetCursorPos(&ptCursor);

	return ptCursor;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the current cursor postion in screen co-ordinates.

CPoint CCursor::CurrentPos(HWND hWnd)
{
	CPoint ptCursor;

	::GetCursorPos(&ptCursor);
	::ScreenToClient(hWnd, &ptCursor);

	return ptCursor;
}
