/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROPERTYDLG.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPropertyDlg class definition.
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

CPropertyDlg::CPropertyDlg(uint nRscID, int nTabCtrlID)
	: CDialog(nRscID)
	, m_nPages(0)
	, m_pPageTable(NULL)
{
	DEFINE_CTRL_TABLE
		CTRL(nTabCtrlID, &m_oTabCtrl)
	END_CTRL_TABLE

	DEFINE_GRAVITY_TABLE
		CTRLGRAV(nTabCtrlID, LEFT_EDGE,  TOP_EDGE,    RIGHT_EDGE, BOTTOM_EDGE)
		CTRLGRAV(IDOK,       RIGHT_EDGE, BOTTOM_EDGE, RIGHT_EDGE, BOTTOM_EDGE)
		CTRLGRAV(IDCANCEL,   RIGHT_EDGE, BOTTOM_EDGE, RIGHT_EDGE, BOTTOM_EDGE)
	END_GRAVITY_TABLE

	DEFINE_CTRLMSG_TABLE
		NFY_CTRLMSG(nTabCtrlID, TCN_SELCHANGING, OnSelChanging)
		NFY_CTRLMSG(nTabCtrlID, TCN_SELCHANGE,   OnSelChange)
	END_CTRLMSG_TABLE
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

CPropertyDlg::~CPropertyDlg()
{
	// Free control table.
	if (m_pPageTable)
		delete[] m_pPageTable;
}

/******************************************************************************
** Method:		PageTable()
**
** Description:	Set up the page table.
**
** Parameters:	pPageTable	The page table.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPropertyDlg::PageTable(PAGEDLG* pPageTable)
{
	ASSERT(m_pPageTable == NULL);
	ASSERT(pPageTable != NULL);

	PAGEDLG* pPage = pPageTable;

	// Count the number of pages.
	while (pPage->m_pPageDlg != NULL)
	{
		m_nPages++;
	    pPage++;
	}

	// Allocate memory for the copy.
	m_pPageTable = new PAGEDLG[m_nPages];
	ASSERT(m_pPageTable);
	
	pPage = pPageTable;

	// Copy the table.
	for (int i = 0; i < m_nPages; i++)
	{
		m_pPageTable[i].m_pPageDlg = pPage->m_pPageDlg;
		m_pPageTable[i].m_pszLabel = pPage->m_pszLabel;
	    pPage++;
	}
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Create the pages.
**
** Parameters:	rcClient	The client area of the dialog.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPropertyDlg::OnCreate(const CRect& rcClient)
{
	ASSERT(m_pPageTable != NULL);

	// Load all pages.
	for (int i = 0; i < m_nPages; i++)
	{
		ASSERT(m_pPageTable[i].m_pPageDlg != NULL);
		ASSERT(m_pPageTable[i].m_pszLabel != NULL);

		CPropertyPageDlg* pPageDlg = m_pPageTable[i].m_pPageDlg;

		pPageDlg->RunModeless(*this);
		m_oTabCtrl.AddTab(m_pPageTable[i].m_pszLabel, -1);
	}

	CSize dmMax;

	// Find the biggest page dimensions.
	for (i = 0; i < m_nPages; i++)
	{
		CSize dmDlg = m_pPageTable[i].m_pPageDlg->WindowRect().Size();

		dmMax.cx = max(dmDlg.cx, dmMax.cx);
		dmMax.cy = max(dmDlg.cy, dmMax.cy);
	}

	// Get the dialog and tab dimensions.
	CRect rcDlg = WindowRect();
	CSize dmTab = m_oTabCtrl.DisplayRect().Size();

	// Calculate the dialog growth.
	rcDlg.right  += (dmMax.cx - dmTab.cx);
	rcDlg.bottom += (dmMax.cy - dmTab.cy);

	// Resize the dialog.
	Move(rcDlg);

	// Show the first page.
	m_oTabCtrl.CurSel(0);
	OnSelChange(*((NMHDR*)NULL));

	// Forward to base class.
	CDialog::OnCreate(rcClient);
}

/******************************************************************************
** Method:		OnOk()
**
** Description:	Calls OnOk() on all the pages.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPropertyDlg::OnOk()
{
	for (int i = 0; i < m_nPages; i++)
	{
		if (!m_pPageTable[i].m_pPageDlg->OnOk())
			return false;
	}

	return true;
}

/******************************************************************************
** Methods:		OnSelChanging()
**
** Description:	Hide the window associated with the currently selected tab.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

LRESULT CPropertyDlg::OnSelChanging(NMHDR&)
{
	int nCurTab = m_oTabCtrl.CurSel();
	if (nCurTab == -1)
		return 0;

	// Hide current window.
	m_pPageTable[nCurTab].m_pPageDlg->WindowPos(HWND_BOTTOM, false);

	return 0;
}

/******************************************************************************
** Methods:		OnSelChange()
**
** Description:	Show the window associated with the newly selected tab.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

LRESULT CPropertyDlg::OnSelChange(NMHDR& rMsgHdr)
{
	int nCurTab = m_oTabCtrl.CurSel();
	if (nCurTab == -1)
		return 0;

	CPropertyPageDlg* pPageDlg = m_pPageTable[nCurTab].m_pPageDlg;

	// Resize and bring the window to the front.
	pPageDlg->WindowPos(HWND_TOP, m_oTabCtrl.DisplayRect(), true);
	pPageDlg->Focus();

	return 0;
}
