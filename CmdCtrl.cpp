/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CMDCTRL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCmdControl class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CCmdControl::CCmdControl()
	: m_pCmdTable(NULL)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CCmdControl::~CCmdControl()
{
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
	while ( (pCmd != NULL) && (pCmd->m_eType != CmdNone)
		 && ( (iCmdID < pCmd->m_iFirstID) || (iCmdID > pCmd->m_iLastID) ) )
	    pCmd++;

	// If found, Execute it.
	if ( (pCmd != NULL) && (iCmdID >= pCmd->m_iFirstID) && (iCmdID <= pCmd->m_iLastID) )
	{
		// Handler for a single command?
		if (pCmd->m_eType == CmdSingle)
		{
			PFNCMDENTRYHANDLER lpfnHandler = (PFNCMDENTRYHANDLER) pCmd->m_lpfnCmdHandler;
			(this->*lpfnHandler)();
		}
		// Handler for a range of commands?
		else if (pCmd->m_eType == CmdRange)
		{
			PFNCMDRANGEHANDLER lpfnHandler = (PFNCMDRANGEHANDLER) pCmd->m_lpfnCmdHandler;
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
	while( (pCmd != NULL) && (pCmd->m_eType != CmdNone) )
	{
		if (pCmd->m_lpfnUIHandler != NULL)
			(this->*pCmd->m_lpfnUIHandler)();

	    pCmd++;
	}

	// Force a redraw of the menu bar.
	CApp::This()->m_rMainWnd.DrawMenuBar();
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
	CMD* pCmd = m_pCmdTable;
	
	// Find command callback function.
	while ( (pCmd != NULL) && (pCmd->m_eType != CmdNone)
		 && ( (iCmdID < pCmd->m_iFirstID) || (iCmdID > pCmd->m_iLastID) ) )
	    pCmd++;

	// If found, draw it.
	if ( (pCmd != NULL) && (iCmdID >= pCmd->m_iFirstID) && (iCmdID <= pCmd->m_iLastID) && (pCmd->m_iBmpIndex != -1) )
		m_CmdBitmap.DrawCmd(pCmd->m_iBmpIndex, rDC, rDst, bEnabled);
}
