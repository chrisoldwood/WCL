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

#if _MSC_VER > 1000
#pragma once
#endif

#include "CtrlWnd.hpp"
#include "IMsgFilter.hpp"
#include "ToolTip.hpp"

// Forward declarations.
namespace WCL
{
class IMsgThread;
class ICmdController;
}

// A space between controls.
#define IDC_SEPARATOR	(static_cast<uint>(-1))

/******************************************************************************
**
** A child window used as a container for buttons and other controls.
**
*******************************************************************************
*/

class CToolBar : public CCtrlWnd, public IMsgFilter
{
public:
	//
	// Constructors/Destructor.
	//
	CToolBar(WCL::IMsgThread& thread, WCL::ICmdController& controller);
	virtual	~CToolBar();

	//
	// Message filtering.
	//
	virtual bool ProcessMsg(MSG& rMsg);

protected:
	///////////////////////////////////////////////////////
	// Structure used to hold the control table.
	///////////////////////////////////////////////////////

	struct CTRL
	{
		CCtrlWnd*	pWnd;
		uint		nID;
	};

	//
	// Members.
	//
	CTRL*		m_pCtrlTable;		// Table of controls.
	CToolTip	m_oToolTip;			// Tool tips control.
	WCL::IMsgThread&		m_thread;		//!< The toolbar thread.
	WCL::ICmdController&	m_controller;	//!< Command controller.

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
	virtual LRESULT OnCtrlMsg(NMHDR& rMsgHdr);

	//
	// Tooltip/Hint support.
	//
	virtual void OnShowHint(const CWnd* pWnd) const;

private:
	// NotCopyable.
	CToolBar(const CToolBar&);
	CToolBar& operator=(const CToolBar&);
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

#define END_TOOLBAR			NULL,  0 }; \
							m_pCtrlTable = Ctrls;

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //TOOLBAR_HPP
