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

// Forward declarations.
class CWnd;

/******************************************************************************
** 
** This is the map used to link window handles to their objects.
**
*******************************************************************************
*/

class CWndMap : public CHandleMap
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
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //WNDMAP_HPP
