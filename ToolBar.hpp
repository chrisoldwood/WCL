/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TOOLBAR.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CToolBar class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

// A space between controls.
#define IDC_SEPARATOR	(uint)-1

/******************************************************************************
** 
** A child window used as a container for buttons and other controls.
**
*******************************************************************************
*/

class CToolBar : public CCtrlWnd, public CMsgFilter
{
public:
	//
	// Constructors/Destructor.
	//
	CToolBar();
	~CToolBar();

	//
	// Message filtering.
	//
	virtual bool ProcessMsg(MSG& rMsg);

protected:
	///////////////////////////////////////////////////////
	// Structure used to hold the control table.
	///////////////////////////////////////////////////////

	typedef struct tagCTRL
	{
		CCtrlWnd*	pWnd;
		uint		iID;
	} CTRL;

	//
	// Members.
	//
	CTRL*	m_pCtrlTable;		// Table of controls.

	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual void OnPaint(CDC& rDC);
	virtual void OnCtrlMsg(uint iID, uint iMsg, HWND hControl);

	//
	// Tooltip/Hint support.
	//
	virtual void CToolBar::OnShowHint(const CWnd* pWnd) const;
};

/******************************************************************************
** 
** Macros used to ease the definition of the control table.
**
*******************************************************************************
*/

#define DEFINE_TOOLBAR		static CTRL Ctrls[] = {

#define TBCTL(wnd, id)		(wnd), (id),
#define TBGAP()				NULL,  IDC_SEPARATOR,

#define END_TOOLBAR			NULL,  0, }; \
							m_pCtrlTable = Ctrls;

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //TOOLBAR_HPP
