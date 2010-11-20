/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DLGFRAME.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDlgFrame class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "DlgFrame.hpp"
#include "MainDlg.hpp"
#include "ToolBar.hpp"
#include "StatusBar.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Override any default settings for the window class and style.
**
** Parameters:	iIconID		The frame window icon.
**				rDialog		The dialog that fills the client area.
**				bFixedSize	Flag to say whether the frame fits the dialog, or
**							the dialog fits the frame.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDlgFrame::CDlgFrame(uint iIconID, CMainDlg& rDialog, bool bFixedSize)
	: CFrameWnd(iIconID)
	, m_rDialog(rDialog)
	, m_bFixedSize(bFixedSize)
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

CDlgFrame::~CDlgFrame()
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

void CDlgFrame::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CFrameWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.dwStyle = WS_OVERLAPPED | WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	// Give frame a border if resizable.
	if (!m_bFixedSize)
		rParams.dwStyle |= WS_THICKFRAME | WS_MAXIMIZEBOX;
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Resize the main window to fit the dialog.
**
** Parameters:	rcClient	The client area.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDlgFrame::OnCreate(const CRect& /*rcClient*/)
{
	CSize toolBarSize;
	CSize statusBarSize;
	CSize borderSize;
	CSize menuSize;
	CSize captionSize;

	// Get the current frame position.
	CRect Pos = WindowRect();

	// Get the size of the dialog.
	CSize DlgSize = m_rDialog.WindowRect().Size();

	// Get the tool bar dimensions, if one.
	if (m_pToolBar)
		toolBarSize = m_pToolBar->ClientRect().Size();

	// Get the status bar dimensions, if one.
	if (m_pStatusBar)
		statusBarSize = m_pStatusBar->ClientRect().Size();

	// Get the menu dimensions, if one.
	if (m_pMenu)
		menuSize.cy = GetSystemMetrics(SM_CYMENU);

	// Get frame border and caption dimensions.
	captionSize.cy = GetSystemMetrics(SM_CYCAPTION);
	borderSize.cx  = GetSystemMetrics(m_bFixedSize ? SM_CXFIXEDFRAME : SM_CXSIZEFRAME);
	borderSize.cy  = GetSystemMetrics(m_bFixedSize ? SM_CYFIXEDFRAME : SM_CYSIZEFRAME);

	// Calculate the new frame dimensions.
	CSize NewSize;

	NewSize.cx = DlgSize.cx + (2 * borderSize.cx);
	NewSize.cy = DlgSize.cy + toolBarSize.cy + statusBarSize.cy
				  + captionSize.cy + menuSize.cy + (2 * borderSize.cy);

	// Resize the frame.
	Move(CRect(Pos.TopLeft(), NewSize));

	// Toolbar?
	if (m_pToolBar)
	{
		// Move dialog below toolbar.
		m_rDialog.Move(CRect(CPoint(0, toolBarSize.cy), DlgSize));
	}
}

/******************************************************************************
** Method:		OnDestroy()
**
** Description:	The window is being destroyed - destroy the main dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDlgFrame::OnDestroy()
{
	if (m_rDialog.Handle() != NULL)
		m_rDialog.Destroy();

	CFrameWnd::OnDestroy();
}

/******************************************************************************
** Method:		OnResize()
**
** Description:	Window has been resized. Resize the dialog to fit the window.
**
** Parameters:	iFlag		The resize method.
**				rNewSize	The new window dimensions.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDlgFrame::OnResize(int iFlag, const CSize& NewSize)
{
	// Resize toolbar etc. first.
	CFrameWnd::OnResize(iFlag, NewSize);

	// Resize dialog to fit client?
	if ( (!m_bFixedSize) && (m_rDialog.Handle() != NULL) )
		m_rDialog.Move(ClientRect());
}

/******************************************************************************
** Method:		OnFocus()
**
** Description:	Divert the focus to the active view window.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDlgFrame::OnFocus()
{
	m_rDialog.Focus();
}
