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
	CSDIApp* pApp = CSDIApp::This();
	ASSERT(pApp != NULL);

	// Get the application name.
	CString strTitle = pApp->m_strTitle;

	// Append doc title, if available.
	if (pApp->m_pDoc != NULL)
	{
		strTitle += " - [";
		strTitle += pApp->m_pDoc->Path();
		strTitle += "]";
	}

	Title(strTitle);
}
