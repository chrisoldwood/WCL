/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CMDBTN.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CCmdButton class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CMDBTN_HPP
#define CMDBTN_HPP

/******************************************************************************
** 
** This is a bitmap based button control used on a toolbar.
**
*******************************************************************************
*/

class CCmdButton : public CButton
{
public:
	//
	// Constructors/Destructor.
	//
	CCmdButton();

protected:
	//
	// Members.
	//

	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnDrawItem(uint iID, uint iAction, uint iState, CDC& rDC, uint iItem, const CRect& rcItem);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //CMDBTN_HPP
