/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CMDCTRL.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CCmdControl class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CMDCTRL_HPP
#define CMDCTRL_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "ICmdController.hpp"
#include "CmdBmp.hpp"

// Forward declarations.
namespace WCL
{
class ICommandWnd;
}

////////////////////////////////////////////////////////////////////////////////
//! The base class from which the application command controller is derived. It
//! is used to execute commands and update the UI.
//!
//! \note This is the original controller that requires derivation because of
//! the way that the command table is defined and the way the class member
//! functions are downcast (pre-template era VC++). As a consequence the derived
//! class needs to ensure that its member layout matches this base class.

class CCmdControl : public WCL::ICmdController /*, private NotCopyable*/
{
public:
	//! Construction with the main command window.
	CCmdControl(WCL::ICommandWnd& commandWnd);

	//! Construction with the main command window and bitmap resource ID.
	CCmdControl(WCL::ICommandWnd& commandWnd, uint bitmapId);

	//! Initialise the UI.
	void InitialiseUI();

	//
	// ICmdController methods.
	//

	//! Execute a command.
	virtual void Execute(uint iCmdID);

	//! Refresh the entire UI.
	virtual void UpdateUI();

	//! Draw the icon for a command.
	virtual void DrawCmd(uint iCmdID, CDC& rDC, const CRect& rDst, bool bEnabled) const;

	//! Get the hint string for a command.
	virtual CString CmdHintStr(uint iCmdID) const;

	//! Get the tool tip for a command.
	virtual CString CmdToolTipStr(uint iCmdID) const;

protected:
	//! Make abstract.
	virtual ~CCmdControl() {};

	///////////////////////////////////////////////////////
	// Structure to define an entry in the command table.
	///////////////////////////////////////////////////////

	// Command handler types.
	enum CmdType
	{
		CmdNone   = 0,
		CmdSingle = 1,
		CmdRange  = 2
	};

	// Types for command handlers.
	typedef void (CCmdControl::*PFNCMDHANDLER)();
	typedef void (CCmdControl::*PFNCMDENTRYHANDLER)();
	typedef void (CCmdControl::*PFNCMDRANGEHANDLER)(uint iCmdID);
	typedef void (CCmdControl::*PFNUIHANDLER)();

	struct CMD
	{
		CmdType			m_eType;			// Comamnd handler type.
		uint			m_iFirstID;			// First command in range.
		uint			m_iLastID;			// Last command in range.
		PFNCMDHANDLER	m_lpfnCmdHandler;	// The exec command handler.
		PFNUIHANDLER	m_lpfnUIHandler;	// The UI command handler.
		int				m_iBmpIndex;		// The index of the command bitmap.
	};

	//
	// Members.
	//
	CMD*		m_pCmdTable;
	uint		m_bitmapId;		//!< The resource ID of the commands bitmap.
	CCmdBitmap	m_CmdBitmap;
	WCL::ICommandWnd&	m_commandWnd;	//!< The application command window.

	//
	// Command property methods.
	//
	virtual int CmdBmpIndex(uint iCmdID) const;
	virtual int CmdHintID(uint iCmdID) const;
	virtual int CmdToolTipID(uint iCmdID) const;

private:
	// NotCopyable.
	CCmdControl(const CCmdControl&);
	CCmdControl& operator=(const CCmdControl&);
};

/******************************************************************************
**
** Macros used to ease the definition of the command table.
**
*******************************************************************************
*/

#define DEFINE_CMD_TABLE					static CMD Cmds[] = {

#define CMD_ENTRY(cmd, cmdfn, uifn, idx)	CmdSingle, (cmd),  (cmd),  (PFNCMDHANDLER) (cmdfn), (PFNUIHANDLER) (uifn), (idx),

#define CMD_RANGE(cmd1, cmd2, cmdfn, uifn, idx) \
											CmdRange,  (cmd1), (cmd2), (PFNCMDHANDLER) (cmdfn), (PFNUIHANDLER) (uifn), (idx),

#define END_CMD_TABLE						CmdNone,     0,      0,    (PFNCMDHANDLER)   0,     (PFNUIHANDLER)   0,      -1 }; \
											m_pCmdTable = Cmds;

#endif //CMDCTRL_HPP
