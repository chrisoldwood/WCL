/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DLGFRAME.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDlgFrame class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef DLGFRAME_HPP
#define DLGFRAME_HPP

/******************************************************************************
** 
** This is a frame window derived class used in applications that have a dialog
** as their main window.
**
*******************************************************************************
*/

class CDlgFrame : public CFrameWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CDlgFrame(uint iIconID, CMainDlg& rDialog, bool bFixedSize);
	virtual	~CDlgFrame();

protected:
	//
	// Members.
	//
	CMainDlg&	m_rDialog;
	bool		m_bFixedSize;
	
	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual void OnDestroy();
	virtual void OnResize(int iFlag, const CSize& NewSize);
	virtual void OnFocus();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //DLGFRAME_HPP
