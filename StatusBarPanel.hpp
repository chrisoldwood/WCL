/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATUSBARPANEL.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CStatusBarPanel class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATUSBARPANEL_HPP
#define STATUSBARPANEL_HPP

/******************************************************************************
** 
** The base class for child windows that sit on the right of the status bar.
**
*******************************************************************************
*/

class CStatusBarPanel : public CCtrlWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CStatusBarPanel();
	virtual	~CStatusBarPanel();
	
	//
	// Constants.
	//
	static const int BORDER_SIZE = 2;		// Width of border around content.

protected:
	//
	// Members.
	//

	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnPaint(CDC& rDC);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // STATUSBARPANEL_HPP
