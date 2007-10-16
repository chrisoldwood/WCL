/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WNDMAP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CWndMap class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "WndMap.hpp"
#include "Wnd.hpp"

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
	ASSERT(m_oMap.empty());
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

	m_oMap.insert(std::make_pair(rWnd.Handle(), &rWnd));
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
	ASSERT(m_oMap.find(rWnd.Handle()) != m_oMap.end());

	m_oMap.erase(m_oMap.find(rWnd.Handle()));
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

	Map::const_iterator it = m_oMap.find(hWnd);

	return (it != m_oMap.end()) ? it->second : NULL;
}
