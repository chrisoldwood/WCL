/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROPERTYPAGE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPropertyPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PROPERTYPAGE_HPP
#define PROPERTYPAGE_HPP

/******************************************************************************
** 
** This is the base class for all property page dialogs.
**
*******************************************************************************
*/

class CPropertyPage : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CPropertyPage(uint nRscID);
	virtual	~CPropertyPage();
	
protected:
	//
	// Members.
	//

	//
	// General message handlers.
	//
	friend BOOL DIALOGPROC PropPageProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//
	// Message processors.
	//
	virtual LRESULT OnCtrlMsg(NMHDR& rMsgHdr);
	virtual bool    OnValidate();
	virtual bool    OnOk();

	//
	// Friends.
	//
	friend class CPropertySheet;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //PROPERTYPAGE_HPP
