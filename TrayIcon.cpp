/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TRAYICON.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CTrayIcon class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
**
** Constants.
**
*******************************************************************************
*/

// Size of tray icon.
const int ICON_WIDTH  = 16;
const int ICON_HEIGHT = 16;

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

CTrayIcon::CTrayIcon()
	: m_hWnd(NULL)
	, m_nTrayID(NULL)
	, m_nMsgID(NULL)
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

CTrayIcon::~CTrayIcon()
{
	// If still visible, remove it.
	if (m_hWnd != NULL)
		Remove();
}

/******************************************************************************
** Method:		Add()
**
** Description:	Adds the icon and optionally the tool tip.
**
** Parameters:	oWnd		The window which will recieves events.
**				nTrayID		The unique ID.
**				nMsgID		The windows message for events.
**				nRscID		The icon resource ID.
**				pszToolTip	The tool tip for the icon.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTrayIcon::Add(const CWnd& oWnd, uint nTrayID, uint nMsgID, uint nRscID, const char* pszToolTip)
{
	ASSERT(m_hWnd        == NULL);
	ASSERT(m_nTrayID     == NULL);
	ASSERT(m_nMsgID      == NULL);
	ASSERT(oWnd.Handle() != NULL);
	ASSERT(nTrayID       != NULL);

	// Save parameters.
	m_hWnd    = oWnd.Handle();
	m_nTrayID = nTrayID;
	m_nMsgID  = nMsgID;

	CIcon oIcon;

	// Load the icon resource.
	oIcon.LoadRsc(nRscID, ICON_WIDTH, ICON_HEIGHT);

	uint nFlags = NIF_ICON;

	// Work out which other fields to set.
	if (m_nMsgID != NULL)
		nFlags |= NIF_MESSAGE;

	if (pszToolTip != NULL)
		nFlags |= NIF_TIP;

	NOTIFYICONDATA oData = { 0 };

	// Fill in the message structure.
	oData.cbSize           = sizeof(oData);
	oData.hWnd             = m_hWnd;
	oData.uID              = m_nTrayID;
	oData.uFlags           = nFlags;
	oData.uCallbackMessage = m_nMsgID;
	oData.hIcon            = oIcon.Handle();

	if (pszToolTip != NULL)
		strcpy(oData.szTip, pszToolTip);

	// Send message.
	::Shell_NotifyIcon(NIM_ADD, &oData);
}

/******************************************************************************
** Method:		Modify()
**
** Description:	Modifies the icon and optionally the tool tip.
**
** Parameters:	nRscID		The icon resource ID.
**				pszToolTip	The tool tip for the icon.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTrayIcon::Modify(uint nRscID, const  char* pszToolTip)
{
	ASSERT(m_hWnd    != NULL);
	ASSERT(m_nTrayID != NULL);

	CIcon oIcon;

	// Load the icon resource.
	oIcon.LoadRsc(nRscID, ICON_WIDTH, ICON_HEIGHT);

	uint nFlags = NIF_ICON;

	// Work out which other fields to set.
	if (m_nMsgID != NULL)
		nFlags |= NIF_MESSAGE;

	if (pszToolTip != NULL)
		nFlags |= NIF_TIP;

	NOTIFYICONDATA oData = { 0 };

	// Fill in the message structure.
	oData.cbSize           = sizeof(oData);
	oData.hWnd             = m_hWnd;
	oData.uID              = m_nTrayID;
	oData.uFlags           = nFlags;
	oData.uCallbackMessage = m_nMsgID;
	oData.hIcon            = oIcon.Handle();

	if (pszToolTip != NULL)
		strcpy(oData.szTip, pszToolTip);

	// Send message.
	::Shell_NotifyIcon(NIM_MODIFY, &oData);
}

/******************************************************************************
** Method:		Remove()
**
** Description:	Removes the icon.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTrayIcon::Remove()
{
	ASSERT(m_hWnd    != NULL);
	ASSERT(m_nTrayID != NULL);

	NOTIFYICONDATA oData = { 0 };

	// Fill in the message structure.
	oData.cbSize = sizeof(oData);
	oData.hWnd   = m_hWnd;
	oData.uID    = m_nTrayID;

	// Send message.
	::Shell_NotifyIcon(NIM_DELETE, &oData);

	// Reset members.
	m_hWnd    = NULL;
	m_nTrayID = NULL;
	m_nMsgID  = NULL;
}
