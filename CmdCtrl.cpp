/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CMDCTRL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCmdControl class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "CmdCtrl.hpp"
#include "ICommandWnd.hpp"

#if (__GNUC__ >= 8) // GCC 8+
// error: cast between incompatible function types
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif

////////////////////////////////////////////////////////////////////////////////
//! Construction with the main command window.

CCmdControl::CCmdControl(WCL::ICommandWnd& commandWnd)
	: m_pCmdTable(nullptr)
	, m_bitmapId(0)
	, m_CmdBitmap()
	, m_commandWnd(commandWnd)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction with the main command window and bitmap resource ID.

CCmdControl::CCmdControl(WCL::ICommandWnd& commandWnd, uint bitmapId)
	: m_pCmdTable(nullptr)
	, m_bitmapId(bitmapId)
	, m_CmdBitmap()
	, m_commandWnd(commandWnd)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Initialise the UI. Load the commands bitmap, if required and then force an
//! update of all commands.

void CCmdControl::InitialiseUI()
{
	if (m_bitmapId != 0)
		m_CmdBitmap.LoadRsc(m_bitmapId);

	UpdateUI();
}

/******************************************************************************
** Method:		Execute()
**
** Description:	Executes the command.
**
** Parameters:	iCmdID		The ID of the command.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCmdControl::Execute(uint iCmdID)
{
	CMD* pCmd = m_pCmdTable;

	// Find command callback function.
	while ( (pCmd != nullptr) && (pCmd->m_eType != CmdNone)
		 && ( (iCmdID < pCmd->m_iFirstID) || (iCmdID > pCmd->m_iLastID) ) )
	    ++pCmd;

	// If found, Execute it.
	if ( (pCmd != nullptr) && (iCmdID >= pCmd->m_iFirstID) && (iCmdID <= pCmd->m_iLastID) )
	{
		// Handler for a single command?
		if (pCmd->m_eType == CmdSingle)
		{
			PFNCMDENTRYHANDLER lpfnHandler = pCmd->m_lpfnCmdHandler;
			(this->*lpfnHandler)();
		}
		// Handler for a range of commands?
		else if (pCmd->m_eType == CmdRange)
		{
			PFNCMDRANGEHANDLER lpfnHandler = reinterpret_cast<PFNCMDRANGEHANDLER>(pCmd->m_lpfnCmdHandler);
			(this->*lpfnHandler)(iCmdID);
		}
	}
}

/******************************************************************************
** Method:		UpdateUI()
**
** Description:	Runs through the list of update handlers and calls them to
**				refresh the UI.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCmdControl::UpdateUI()
{
	CMD* pCmd = m_pCmdTable;

	// Call all command UI handlers.
	while( (pCmd != nullptr) && (pCmd->m_eType != CmdNone) )
	{
		if (pCmd->m_lpfnUIHandler != nullptr)
			(this->*pCmd->m_lpfnUIHandler)();

	    ++pCmd;
	}

	m_commandWnd.OnCommandsUpdated();
}

/******************************************************************************
** Method:		DrawCmd()
**
** Description:	Draw the commands icon.
**
** Parameters:	iCmdID		The command to draw.
**				rDC			The destination device.
**				rDst		The destination rect.
**				bEnabled	Enabled or disabled?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCmdControl::DrawCmd(uint iCmdID, CDC& rDC, const CRect& rDst, bool bEnabled) const
{
	ASSERT(CmdBmpIndex(iCmdID) != -1);

	m_CmdBitmap.DrawCmd(CmdBmpIndex(iCmdID), rDC, rDst, bEnabled);
}

/******************************************************************************
** Method:		CmdBmpIndex()
**
** Description:	Get the commands' bitmap index.
**
** Parameters:	iCmdID		The command.
**
** Returns:		The index or -1 if there isn't one.
**
*******************************************************************************
*/

int CCmdControl::CmdBmpIndex(uint iCmdID) const
{
	CMD* pCmd = m_pCmdTable;

	// Find command.
	while ( (pCmd != nullptr) && (pCmd->m_eType != CmdNone)
		 && ( (iCmdID < pCmd->m_iFirstID) || (iCmdID > pCmd->m_iLastID) ) )
	    ++pCmd;

	// If found, return it.
	if ( (pCmd != nullptr) && (iCmdID >= pCmd->m_iFirstID) && (iCmdID <= pCmd->m_iLastID) )
		return pCmd->m_iBmpIndex;

	// Not found.
	return -1;
}

/******************************************************************************
** Method:		CmdHintID()
**
** Description:	Get the commands' hint resource ID.
**				By default the hint resurce ID is the same as the command ID.
**
** Parameters:	iCmdID		The command.
**
** Returns:		The hint resource ID.
**
*******************************************************************************
*/

int CCmdControl::CmdHintID(uint iCmdID) const
{
	return iCmdID;
}

/******************************************************************************
** Method:		CmdToolTipID()
**
** Description:	Get the commands' tool tip resource ID.
**				By default the tool tip resurce ID is the same as the command ID.
**
** Parameters:	iCmdID		The command.
**
** Returns:		The tool tip resource ID.
**
*******************************************************************************
*/

int CCmdControl::CmdToolTipID(uint iCmdID) const
{
	return iCmdID;
}

/******************************************************************************
** Method:		CmdHintStr()
**
** Description:	Get the commands' hint text.
**				If the string contains a newline, it assumes that text after
**				the newline is a tooltip and removes it.
**
** Parameters:	iCmdID		The command.
**
** Returns:		The hint text.
**
*******************************************************************************
*/

CString CCmdControl::CmdHintStr(uint iCmdID) const
{
	CString str(CmdHintID(iCmdID));
	size_t	nEOL = str.Find(TXT('\n'));

	// Hint only?
	if (nEOL == Core::npos)
		return str;

	// Strip tooltip.
	return str.Left(nEOL);
}

/******************************************************************************
** Method:		CmdToolTipStr()
**
** Description:	Get the commands' tool tip text.
**				If the string contains a newline, it assumes that text before
**				the newline is a hint and removes it.
**
** Parameters:	iCmdID		The command.
**
** Returns:		The tool tip text.
**
*******************************************************************************
*/

CString CCmdControl::CmdToolTipStr(uint iCmdID) const
{
	CString str(CmdHintID(iCmdID));
	size_t	nEOL = str.Find(TXT('\n'));

	// Hint only?
	if (nEOL == Core::npos)
		return TXT("");

	// Strip tooltip.
	return str.Right(str.Length() - nEOL - 1);
}
