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

#include "CmdBmp.hpp"

/******************************************************************************
** 
** The base class from which the application command controller is derived. It
** is used to execute commands and update the UI.
**
*******************************************************************************
*/

class CCmdControl
{
public:
	//
	// Constructors/Destructor.
	//
	CCmdControl();
	~CCmdControl();

	//
	// Member access.
	//
	CCmdBitmap& CmdBitmap();

	//
	// Command methods.
	//
	virtual void Execute(uint iCmdID);
	virtual void UpdateUI();
	virtual void DrawCmd(uint iCmdID, CDC& rDC, const CRect& rDst, bool bEnabled) const;

	//
	// Command property methods.
	//
	virtual int CmdBmpIndex(uint iCmdID) const;
	virtual int CmdHintID(uint iCmdID) const;
	virtual int CmdToolTipID(uint iCmdID) const;
	virtual CString CmdHintStr(uint iCmdID) const;
	virtual CString CmdToolTipStr(uint iCmdID) const;

protected:
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
	
	typedef struct tagCMD
	{
		CmdType			m_eType;			// Comamnd handler type.
		uint			m_iFirstID;			// First command in range.
		uint			m_iLastID;			// Last command in range.
		PFNCMDHANDLER	m_lpfnCmdHandler;	// The exec command handler.
		PFNUIHANDLER	m_lpfnUIHandler;	// The UI command handler.
		int				m_iBmpIndex;		// The index of the command bitmap.
	} CMD;

	//
	// Members.
	//
	CMD*		m_pCmdTable;
	CCmdBitmap	m_CmdBitmap;
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

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CCmdBitmap& CCmdControl::CmdBitmap()
{
	return m_CmdBitmap;
}

#endif //CMDCTRL_HPP
