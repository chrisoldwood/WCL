/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DIALOG.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDialog class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef DIALOG_HPP
#define DIALOG_HPP

// Forward declarations.
class CCtrlWnd;

/******************************************************************************
** 
** This is the base class from which all modal and modeless	dialogs are
** derived. The diaog can be run modal or modeless depending on the method
** used.
**
*******************************************************************************
*/

class CDialog : public CMsgWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CDialog(uint iRscID);
	~CDialog();
	
	//
	// Creation methods.
	//
	bool RunModeless(CWnd& rParent);
	int  RunModal(CWnd& rParent);

protected:
	///////////////////////////////////////////////////////
	// Structure used to hold the control table.
	///////////////////////////////////////////////////////

	typedef struct tagCTRL
	{
		uint		iID;
		CCtrlWnd*	pWnd;
	} CTRL;

	// Gravity edges.
	enum Gravity
	{
		LEFT_EDGE   = 0,
		RIGHT_EDGE  = 1,
		TOP_EDGE    = 0,
		BOTTOM_EDGE = 1
	};

	///////////////////////////////////////////////////////
	// Structure used to hold the control gravity table.
	///////////////////////////////////////////////////////

	typedef struct tagCTLGRAVITY
	{
		// Members.
		uint		iID;
		HWND		hWnd;
		Gravity		eLeft, eTop, eRight, eBottom;
		CRect		rcStart;

		// Constructors.
		tagCTLGRAVITY()
			: iID(0), hWnd(NULL), eLeft(LEFT_EDGE), eTop(TOP_EDGE)
			, eRight(LEFT_EDGE), eBottom(TOP_EDGE) { }

		tagCTLGRAVITY(uint id, Gravity l, Gravity t, Gravity r, Gravity b)
			: iID(id), hWnd(NULL), eLeft(l), eTop(t), eRight(r), eBottom(b) { }
	} CTLGRAVITY;

	//
	// Members.
	//
	uint		m_iRscID;		// Dialog resource ID.
	bool		m_bModal;		// Running modal?
	CTRL*		m_pCtrlTable;	// Table of controls.
	CTLGRAVITY*	m_pGravTable;	// Table of controls gravity.
	CSize		m_StartSize;	// Dialog initial size.
	CWnd*		m_pParentWnd;	// Parent window.
	CRect		m_rcOldGrip;	// Old resizing grip position.
	
	//
	// General message handlers.
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefaultWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	friend BOOL DIALOGPROC DlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual void OnInitDialog();
	virtual bool OnOk();
	virtual bool OnCancel();
	virtual void OnResize(int iFlag, const CSize& rNewSize);
	virtual void OnPaint(CDC& rDC);

	//
	// Control methods.
	//
	HWND CtrlHandle(int iCtrlID) const;
	void ControlTable(CTRL* pCtrlTable);
	void InitControls();
	void GravityTable(CTLGRAVITY* pGravTable);
	void InitGravityTable();

	//
	// Internal methods.
	//
	virtual void EndDialog(int nResult = IDCANCEL);

	//
	// Friends.
	//
	friend struct tagCTLGRAVITY;	// For access to Gravity enum.
};

/******************************************************************************
** 
** Macros used to ease the definition of the control table.
**
*******************************************************************************
*/

#define DEFINE_CTRL_TABLE	CTRL Ctrls[] = {

#define CTRL(id, wnd)		{ (id), (wnd) },

#define END_CTRL_TABLE		{  0,    NULL } }; \
							ControlTable(Ctrls);

/******************************************************************************
** 
** Macros used to ease the definition of the control gravity table.
**
*******************************************************************************
*/

#define DEFINE_GRAVITY_TABLE		CTLGRAVITY Gravs[] = {

#define CTRLGRAV(id, l, t, r, b)	tagCTLGRAVITY((id), (l), (t), (r), (b)),

#define END_GRAVITY_TABLE			tagCTLGRAVITY(0, LEFT_EDGE, TOP_EDGE, LEFT_EDGE, TOP_EDGE) }; \
									GravityTable(Gravs);

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HWND CDialog::CtrlHandle(int iCtrlID) const
{
	return ::GetDlgItem(m_hWnd, iCtrlID);
}

#endif //DIALOG_HPP
