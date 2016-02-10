/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TOOLTIP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CToolTip class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ToolTip.hpp"

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

CToolTip::CToolTip()
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

CToolTip::~CToolTip()
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

void CToolTip::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = TOOLTIPS_CLASS;
	rParams.dwStyle      = WS_POPUP | TTS_NOPREFIX /*| TTS_ALWAYSTIP*/;
	rParams.hMenu        = NULL;
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Finish initialising the control.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CToolTip::OnCreate(const CRect&)
{
	::SetWindowPos(m_hWnd, HWND_TOPMOST,0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

/******************************************************************************
** Method:		AddTool()
**
** Description:	Adds a tool to the control. See TOOLINFO for details.
**
** Parameters:	nFlags		The tool flags.
**				oParent		The parent window.
**				nID			The handle of the child or logical ID of the tool.
**				prcRect		The tool area, if not a child window.
**				pszText		The tip text or LPSTR_CALLBACK if dynamic.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CToolTip::AddTool(uint nFlags, CWnd& oParent, uint nID, const CRect* prcRect, const tchar* pszText)
{
	ASSERT( ((nFlags & TTF_IDISHWND) && (prcRect == NULL)) || (!(nFlags & TTF_IDISHWND) && (prcRect != NULL)) );

	TOOLINFO oInfo;

	// Initialise structure.
	memset(&oInfo, 0, sizeof(oInfo));
	oInfo.cbSize = sizeof(oInfo);

	// Set members.
    oInfo.uFlags   = nFlags;
    oInfo.hwnd     = oParent.Handle();
    oInfo.uId      = nID;

	if (prcRect != nullptr)
		oInfo.rect = *prcRect;

    oInfo.lpszText = const_cast<tchar*>(pszText);

	// Add it.
	SendMessage(TTM_ADDTOOL, 0, reinterpret_cast<LPARAM>(&oInfo));
}
