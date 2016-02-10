/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TRAYICON.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CTrayIcon class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "TrayIcon.hpp"
#include "Icon.hpp"

#if __GNUC__
// missing initializer for member 'X'
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
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

// Maximum length of tooltip (inc. nul terminator).
#if (_WIN32_IE < 0x0500)
const size_t MAX_TIP_LEN = 64;
#else
const size_t MAX_TIP_LEN = 128;
#endif

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
	, m_nTrayID(0)
	, m_nMsgID(WM_NULL)
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

void CTrayIcon::Add(const CWnd& oWnd, uint nTrayID, uint nMsgID, uint nRscID, const tchar* pszToolTip)
{
	ASSERT(m_hWnd        == NULL);
	ASSERT(m_nTrayID     == 0);
	ASSERT(m_nMsgID      == 0);
	ASSERT(oWnd.Handle() != NULL);
	ASSERT(nTrayID       != 0);
	ASSERT((pszToolTip == nullptr) || (tstrlen(pszToolTip) < MAX_TIP_LEN));

	// Save parameters.
	m_hWnd    = oWnd.Handle();
	m_nTrayID = nTrayID;
	m_nMsgID  = nMsgID;

	// Load the icon resource.
	CIcon oIcon(nRscID, ICON_WIDTH, ICON_HEIGHT);

	uint nFlags = NIF_ICON;

	// Work out which other fields to set.
	if (m_nMsgID != 0)
		nFlags |= NIF_MESSAGE;

	if (pszToolTip != nullptr)
		nFlags |= NIF_TIP;

	NOTIFYICONDATA oData = { 0 };

	// Fill in the message structure.
	oData.cbSize           = sizeof(oData);
	oData.hWnd             = m_hWnd;
	oData.uID              = m_nTrayID;
	oData.uFlags           = nFlags;
	oData.uCallbackMessage = m_nMsgID;
	oData.hIcon            = oIcon.Handle();

	if (pszToolTip != nullptr)
		tstrncpy(oData.szTip, pszToolTip, MAX_TIP_LEN-1);

	// Send message.
	::Shell_NotifyIcon(NIM_ADD, &oData);
}

/******************************************************************************
** Method:		Modify()
**
** Description:	Modifies the icon and/or the tool tip.
**
** Parameters:	nRscID		The icon resource ID. (NULL to skip)
**				pszToolTip	The tool tip for the icon. (nullptr to skip)
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTrayIcon::Modify(uint nRscID, const tchar* pszToolTip)
{
	ASSERT(m_hWnd    != NULL);
	ASSERT(m_nTrayID != 0);
	ASSERT(nRscID != 0 || pszToolTip != nullptr);
	ASSERT((pszToolTip == nullptr) || (tstrlen(pszToolTip) < MAX_TIP_LEN));

	uint nFlags = 0;

	// Work out which fields we're setting.
	if (nRscID != 0)
		nFlags |= NIF_ICON;

	if (pszToolTip != nullptr)
		nFlags |= NIF_TIP;

	NOTIFYICONDATA oData = { 0 };

	// Fill in the message structure.
	oData.cbSize           = sizeof(oData);
	oData.hWnd             = m_hWnd;
	oData.uID              = m_nTrayID;
	oData.uFlags           = nFlags;
	oData.uCallbackMessage = m_nMsgID;

	if (nRscID != 0)
	{
		CIcon oIcon(nRscID, ICON_WIDTH, ICON_HEIGHT);

		oData.hIcon = oIcon.Handle();
	}

	if (pszToolTip != nullptr)
		tstrncpy(oData.szTip, pszToolTip, MAX_TIP_LEN-1);

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
	ASSERT(m_nTrayID != 0);

	NOTIFYICONDATA oData = { 0 };

	// Fill in the message structure.
	oData.cbSize = sizeof(oData);
	oData.hWnd   = m_hWnd;
	oData.uID    = m_nTrayID;

	// Send message.
	::Shell_NotifyIcon(NIM_DELETE, &oData);

	// Reset members.
	m_hWnd    = NULL;
	m_nTrayID = 0;
	m_nMsgID  = WM_NULL;
}
