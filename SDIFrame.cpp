/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDIFRAME.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CSDIFrame class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
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

CSDIFrame::CSDIFrame(uint iIconID) : CFrameWnd(iIconID)
	, m_pView(NULL)
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

CSDIFrame::~CSDIFrame()
{
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	The window has just been created.
**
** Parameters:	rcClient	The client area.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSDIFrame::OnCreate(const CRect& rcClient)
{
	// Register for drag'n'drop support.
	::DragAcceptFiles(m_hWnd, TRUE);

	CFrameWnd::OnCreate(rcClient);
}

/******************************************************************************
** Method:		OnDestroy()
**
** Description:	The window is being destroyed.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSDIFrame::OnDestroy()
{
	// Unregister for drag'n'drop support.
	::DragAcceptFiles(m_hWnd, FALSE);

	CFrameWnd::OnDestroy();
}

/******************************************************************************
** Method:		OnResize()
**
** Description:	The window has been resized. This resizes the toolbar, status
**				bar and view to match the new settings.
**
** Parameters:	iFlag		The resize method.
**				rNewSize	The new window dimensions.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSDIFrame::OnResize(int iFlag, const CSize& rNewSize)
{
	// Only when our window has changed.
	if ( (iFlag == SIZE_RESTORED) || (iFlag == SIZE_MAXIMIZED) )
	{
		// Do toolbar and status bar first.
		CFrameWnd::OnResize(iFlag, rNewSize);
		
		// Resize view to fit client.
		if (m_pView != NULL)
			m_pView->Move(ClientRect());
	}
}

/******************************************************************************
** Method:		SetView()
**
** Description:	Set the frame windows' view and resize to fit.
**
** Parameters:	pView		The view window.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSDIFrame::View(CView* pView)
{
	m_pView = pView;

	// Setting the view?
	if (m_pView != NULL)
	{
		// Create the views' window?
		if (m_pView->Handle() == NULL)
			m_pView->Create(*this, IDC_VIEW, CRect(0,0,0,0));

		// Resize view to fit client area.
		m_pView->Move(ClientRect());
	}
}

/******************************************************************************
** Method:		UpdateTitle()
**
** Description:	Updates the windows title bar to show the current doc.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSDIFrame::UpdateTitle()
{
	// Get application object.
	CSDIApp& oApp = CSDIApp::This();

	// Get the application name.
	CString strTitle = oApp.m_strTitle;

	// Append doc title, if available.
	if (oApp.m_pDoc != NULL)
	{
		strTitle += " - [";
		strTitle += oApp.m_pDoc->Path();
		strTitle += "]";
	}

	Title(strTitle);
}

/******************************************************************************
** Method:		OnDropFile()
**
** Description:	The user has drag'n'dropped one or more files onto the window.
**
** Parameters:	nFile		The index of the dropped file.
**				pszPath		The files' path.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSDIFrame::OnDropFile(int nFile, const char* pszPath)
{
	ASSERT(nFile   >= 0);
	ASSERT(pszPath != NULL);

	// Only load the first file.
	if (nFile == 0)
	{
		// Call cmd controller to open file.
		static_cast<CSDICmds&>(CSDIApp::This().m_rCmdControl).OpenFile(pszPath);
	}
}
