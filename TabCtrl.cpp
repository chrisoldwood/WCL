/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TABCTRL.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CTabCtrl class definition.
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

CTabCtrl::CTabCtrl()
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

CTabCtrl::~CTabCtrl()
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

void CTabCtrl::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = WC_TABCONTROL;
	rParams.dwExStyle   |= WS_EX_CLIENTEDGE;
	rParams.dwStyle     |= WS_BORDER | TCS_TABS | TCS_SINGLELINE | TCS_RIGHTJUSTIFY;
}

/******************************************************************************
** Method:		AddTab()
**
** Description:	Appends a Tab to the control.
**
** Parameters:	pszName		The tabs' name.
**				lData		Tab custom data.
**
** Returns:		The index of the new tab.
**
*******************************************************************************
*/

int CTabCtrl::AddTab(const char* pszName, LPARAM lData)
{
	int i = NumTabs();

	TCITEM tcItem;

	// Initialise item.
	memset(&tcItem, 0, sizeof(tcItem));
	tcItem.mask    = TCIF_TEXT | TCIF_PARAM;
	tcItem.pszText = const_cast<char*>(pszName);
	tcItem.lParam  = lData;

	TabCtrl_InsertItem(m_hWnd, i, &tcItem);

	return i;
}

/******************************************************************************
** Method:		ItemData()
**
** Description:	Gets the custom data associated with the Tab.
**
** Parameters:	nTab	The tab to query.
**
** Returns:		The custom data.
**
*******************************************************************************
*/

LPARAM CTabCtrl::ItemData(int nTab) const
{
	TCITEM tcItem;

	// Initialise item.
	memset(&tcItem, 0, sizeof(tcItem));
	tcItem.mask = TCIF_PARAM;

	TabCtrl_GetItem(m_hWnd, nTab, &tcItem);

	return tcItem.lParam;
}

/******************************************************************************
** Method:		DisplayRect()
**
** Description:	Gets the display area of the control relative to the parent.
**
** Parameters:	None.
**
** Returns:		The display rectangle.
**
*******************************************************************************
*/

CRect CTabCtrl::DisplayRect() const
{
	// Get our position relative to our parent.
	CRect rcClient = m_pParent->ChildRect(*this);

	// Adjust rectangle.
	TabCtrl_AdjustRect(m_hWnd, FALSE, &rcClient);

	return rcClient;
}

/******************************************************************************
** Method:		OnReflectedCtrlMsg()
**
** Description:	Handle child messages reflected back from the parent.
**
** Parameters:	rMsgHdr		The message.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTabCtrl::OnReflectedCtrlMsg(NMHDR& rMsgHdr)
{
	// Decode message.
	switch(rMsgHdr.code)
	{
		// Selection changing.
		case TCN_SELCHANGING:
			OnSelChanging();
			break;

		// Selection changed.
		case TCN_SELCHANGE:
			OnSelChange();
			break;

		// Unknown.
		default:
			break;
	}
}

/******************************************************************************
** Methods:		OnSelChange()
**
** Description:	Default implementation of reflected message handlers.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTabCtrl::OnSelChanging()
{
}

void CTabCtrl::OnSelChange()
{
}
