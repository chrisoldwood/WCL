/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		VIEW.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CView class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "View.hpp"
#include "DC.hpp"

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

CView::CView(CDoc& rDoc)
	: m_Doc(rDoc)
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

CView::~CView()
{
}

/******************************************************************************
** Method:		GetClassParams()
**
** Description:	Template method to get the window class data.
**
** Parameters:	rParams		The class structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CView::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	rParams.lpszClassName = TXT("View");
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

void CView::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName  = TXT("View");
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the border.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CView::OnPaint(CDC& rDC)
{
	rDC.Border3D(ClientRect(), false, true);
}
