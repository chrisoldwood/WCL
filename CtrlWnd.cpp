/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CTRLWND.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCtrlWnd class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Override any default settings for the window class and style.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CCtrlWnd::CCtrlWnd()
	: m_iID(0)
	, m_pParent(NULL)
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

CCtrlWnd::~CCtrlWnd()
{
}

/******************************************************************************
** Method:		GetCreateParams()
**
** Description:	Template method to get the window creation data.
**
** Parameters:	rParams		The create structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCtrlWnd::GetCreateParams(WNDCREATE& rParams)
{
	ASSERT(m_iID);
	ASSERT(m_pParent);

	// Get base class settings.
	CPopupWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.dwStyle = WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;
	rParams.rcPos   = m_rcPos;
	rParams.hParent = m_pParent->Handle();
	rParams.hMenu   = (HMENU)m_iID;
}

/******************************************************************************
** Method:		Create()
**
** Description:	Create the control window.
**
** Parameters:	rParent		The parent window.
**				iID			The control ID.
**				rcPos		The window position.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CCtrlWnd::Create(CMsgWnd& rParent, uint iID, const CRect& rcPos)
{
	// Save members.
	m_iID     = iID;
	m_pParent = &rParent;
	m_rcPos   = rcPos;

	// Create the window.
	return CPopupWnd::Create();
}

/******************************************************************************
** Method:		Create()
**
** Description:	Attach the object to an existing control.
**
** Parameters:	rParent		The parent window.
**				iID			The control ID.
**				hWnd		The control window handle.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CCtrlWnd::Create(CMsgWnd& rParent, uint iID, HWND hWnd)
{
	ASSERT(hWnd);
	ASSERT(iID);

	// Initialise members.
	m_hWnd    = hWnd;
	m_iID     = iID;
	m_pParent = &rParent;

	// Setup Window/Object mapping.
	CWnd::s_WndMap.Add(*this);

	// Change WndProc to our multi purpose one.
	m_lpfnOldWndProc = WindowProc(::PopupWndProc);

	// Initialise.
	OnCreate(ClientRect());

	return true;
}
