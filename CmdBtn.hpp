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
	bool	m_bOnToolbar;
	bool	m_bTimerOn;

	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnNCDestroy();
	virtual void OnDrawItem(uint iID, uint iAction, uint iState, CDC& rDC, uint iItem, const CRect& rcItem);
	virtual void OnMouseMove(const CPoint& ptCursor, uint iKeyFlags);
	virtual void OnTimer(uint iTimerID);

	//
	// Class members.
	//
	static CCmdButton* g_pActiveBtn;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //CMDBTN_HPP
