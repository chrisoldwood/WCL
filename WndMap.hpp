/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WNDMAP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CWndMap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WNDMAP_HPP
#define WNDMAP_HPP

#if _MSC_VER > 1000
#pragma once
#endif

// Forward declarations.
class CWnd;

/******************************************************************************
** 
** This is the map used to link window handles to their objects.
** NB: This used to be based on the WCL HandleMap class.
**
*******************************************************************************
*/

class CWndMap
{
public:
	//
	// Constructors/Destructor.
	//
	CWndMap();
	~CWndMap();

	//
	// Methods.
	//
	void  Add(CWnd& rWnd);
	void  Remove(CWnd& rWnd);
	CWnd* Find(HWND hWnd) const;

private:
	// Type shorthands.
	typedef std::map<HWND, CWnd*> Map;

	//
	// Members.
	//
	Map	m_oMap;		//!< The underlying container.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //WNDMAP_HPP
