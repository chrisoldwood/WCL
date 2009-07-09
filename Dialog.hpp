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

#if _MSC_VER > 1000
#pragma once
#endif

#include "MsgWnd.hpp"
#include <vector>

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
	virtual ~CDialog();

	//
	// Creation methods.
	//
	bool RunModeless(CWnd& rParent);
	int  RunModal(CWnd& rParent);

protected:
	///////////////////////////////////////////////////////
	// Structure used to hold the control table.
	///////////////////////////////////////////////////////

	struct CTRL
	{
		uint		iID;
		CCtrlWnd*	pWnd;
	};

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

	struct CTLGRAVITY
	{
		// Members.
		uint		iID;
		HWND		hWnd;
		Gravity		eLeft, eTop, eRight, eBottom;
		CRect		rcStart;

		// Constructors.
		CTLGRAVITY()
			: iID(0), hWnd(NULL), eLeft(LEFT_EDGE), eTop(TOP_EDGE)
			, eRight(LEFT_EDGE), eBottom(TOP_EDGE) { }

		CTLGRAVITY(uint id, Gravity l, Gravity t, Gravity r, Gravity b)
			: iID(id), hWnd(NULL), eLeft(l), eTop(t), eRight(r), eBottom(b) { }
	};

	//! The collection of controls.
	typedef std::vector<CTRL> Controls;
	//! The collection of control gravity settings.
	typedef std::vector<CTLGRAVITY> Gravities;

	//
	// Members.
	//
	uint		m_iRscID;		// Dialog resource ID.
	bool		m_bModal;		// Running modal?
	Controls	m_vControls;	// Collection of child controls.
	Gravities	m_vGravities;	// Collection of control gravities.
	CSize		m_StartSize;	// Dialog initial size.
	CWnd*		m_pParentWnd;	// Parent window.
	bool		m_bNoSizeGrip;	// No size grip?
	CRect		m_rcOldGrip;	// Old resizing grip position.

	//
	// General message handlers.
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefaultWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	static WCL::DlgResult DIALOGPROC DlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual void OnInitDialog();
	virtual bool OnOk();
	virtual bool OnCancel();
	virtual void OnResize(int iFlag, const CSize& rNewSize);
	virtual void OnPaint(CDC& rDC);
	virtual void OnHitTest(const CPoint& ptCursor);

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

#define CTRLGRAV(id, l, t, r, b)	CTLGRAVITY((id), (l), (t), (r), (b)),

#define END_GRAVITY_TABLE			CTLGRAVITY(0, LEFT_EDGE, TOP_EDGE, LEFT_EDGE, TOP_EDGE) }; \
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
