/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATICCTRL.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CStaticCtrl class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATICCTRL_HPP
#define STATICCTRL_HPP

/******************************************************************************
** 
** This a static control.
**
*******************************************************************************
*/

class CStaticCtrl : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CStaticCtrl();

	//
	// Standard methods.
	//

protected:
	//
	// Members.
	//
	
	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //STATICCTRL_HPP
