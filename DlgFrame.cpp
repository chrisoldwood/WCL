/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DLGFRAME.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDlgFrame class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

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

void CDlgFrame::OnCreate(const CRect& rcClient)
{
	CSize ToolBar;
	CSize StatusBar;
	CSize Border;	
	CSize Menu;
	CSize Caption;

	// Get the current frame position.
	CRect Pos = WindowRect();
    
	// Get the size of the dialog.
	CSize DlgSize = m_rDialog.WindowRect().Size();
	
	// Get the toolbar and status bar dimensions.
	if (m_pToolBar)
		ToolBar = m_pToolBar->ClientRect().Size();
    
	if (m_pStatusBar)
		StatusBar = m_pStatusBar->ClientRect().Size();

	// Get frame border, menu and caption dimensions.
	Caption.cy = GetSystemMetrics(SM_CYCAPTION);
	Menu.cy    = GetSystemMetrics(SM_CYMENU);
	Border.cx  = GetSystemMetrics(m_bFixedSize ? SM_CXFIXEDFRAME : SM_CXSIZEFRAME);
	Border.cy  = GetSystemMetrics(m_bFixedSize ? SM_CYFIXEDFRAME : SM_CYSIZEFRAME);

	// Calculate the new frame dimensions.
	CSize NewSize;

	NewSize.cx = DlgSize.cx + (2 * Border.cx);
	NewSize.cy = DlgSize.cy + ToolBar.cy + StatusBar.cy 
				  + Caption.cy + Menu.cy + (2 * Border.cy);

	// Resize the frame.
	Move(CRect(Pos.TopLeft(), NewSize));
	
	// Toolbar?
	if (m_pToolBar)
	{
		// Move dialog below toolbar.
		m_rDialog.Move(CRect(CPoint(0, ToolBar.cy), DlgSize));
	}
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
	if (!m_bFixedSize)
		m_rDialog.Move(ClientRect());
}
