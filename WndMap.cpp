/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WNDMAP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CWndMap class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

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

CWndMap::CWndMap()
{
	Reserve(MAX_WINDOWS);
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

CWndMap::~CWndMap()
{
	ASSERT(m_iCount == 0);
	ASSERT(m_pMap   == NULL);
}

/******************************************************************************
** Method:		Add()
**
** Description:	Adds a window to the map.
**
** Parameters:	rWnd	The window to add.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWndMap::Add(CWnd& rWnd)
{
	ASSERT(rWnd.Handle() != NULL);

	CHandleMap::Add(rWnd.Handle(), &rWnd);
}

/******************************************************************************
** Method:		Remove()
**
** Description:	Removes a window from the map.
**
** Parameters:	rWnd	The window to remove.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CWndMap::Remove(CWnd& rWnd)
{
	ASSERT(rWnd.Handle() != NULL);

	CHandleMap::Remove(rWnd.Handle());
}

/******************************************************************************
** Method:		Find()
**
** Description:	Attempts to find a window in the map.
**
** Parameters:	hWnd	The window to find.
**
** Returns:		The window if found or NULL.
**
*******************************************************************************
*/

CWnd* CWndMap::Find(HWND hWnd) const
{
	ASSERT(hWnd != NULL);

	return (CWnd*) CHandleMap::Find(hWnd);
}
