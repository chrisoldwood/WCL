/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROPERTYSHEET.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPropertySheet class definition.
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

CPropertySheet::CPropertySheet()
	: m_nPages(0)
	, m_pPageTable(NULL)
	, m_phPages(NULL)
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

CPropertySheet::~CPropertySheet()
{
	// Free page table.
	if (m_pPageTable)
		delete[] m_pPageTable;

	// Free page handle array.
	if (m_phPages)
		delete[] m_phPages;
}

/******************************************************************************
** Method:		RunModless()
**
** Description:	Create the property sheet as a modeless dialog.
**
** Parameters:	rParent		The dialogs' parent window.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPropertySheet::RunModeless(CWnd& rParent)
{
/*	// Initalise members.
	m_bModal = false;

	ASSERT(rParent.Handle());
	ASSERT(CModule::This().Handle());
	ASSERT(m_iRscID);

	// Create it.
	HWND hWnd = CreateDialogParam(CModule::This().Handle(), MAKEINTRESOURCE(m_iRscID),
									rParent.Handle(), (DLGPROC)DlgProc, (LPARAM)this);

	ASSERT(hWnd);

	// Okay?
	return (hWnd != NULL);
*/
	return false;
}

/******************************************************************************
** Method:		RunModal()
**
** Description:	Create the property sheet as a modal dialog.
**
** Parameters:	rParent		The dialogs' parent window.
**
** Returns:		> 0		If okay.
**				-1		On error.
**
*******************************************************************************
*/

int CPropertySheet::RunModal(CWnd& rParent)
{
	ASSERT(rParent.Handle()         != NULL);
	ASSERT(CModule::This().Handle() != NULL);

	// Create the page handle array.
	m_phPages = new HPROPSHEETPAGE[m_nPages];

	// Add the pages.
	for (int i = 0; i < m_nPages; i++)
	{
		// Initialise the page.
		PROPSHEETPAGE oPage;

		memset(&oPage, 0, sizeof(oPage));

		oPage.dwSize      = sizeof(oPage);
		oPage.dwFlags     = PSP_DEFAULT | PSP_PREMATURE | PSP_USETITLE;
		oPage.hInstance   = CModule::This().Handle();
		oPage.pszTemplate = MAKEINTRESOURCE(m_pPageTable[i].m_pPage->m_iRscID);
		oPage.hIcon       = NULL;
		oPage.pszTitle    = m_pPageTable[i].m_pszLabel;
		oPage.pfnDlgProc  = PropPageProc;
		oPage.lParam      = (LPARAM) m_pPageTable[i].m_pPage;
		oPage.pfnCallback = NULL;
		oPage.pcRefParent = NULL;

		// Create it.
		m_phPages[i] = ::CreatePropertySheetPage(&oPage);

		ASSERT(m_phPages[i] != NULL);
	}

	// Initialise the header.
	PROPSHEETHEADER oHeader;

	memset(&oHeader, 0, sizeof(oHeader));

	oHeader.dwSize      = sizeof(oHeader);
	oHeader.dwFlags     = PSH_DEFAULT | PSH_NOAPPLYNOW;
	oHeader.hwndParent  = rParent.Handle();
	oHeader.hInstance   = CModule::This().Handle();
	oHeader.hIcon       = NULL;
	oHeader.pszCaption  = m_strTitle;
	oHeader.nPages      = m_nPages;
	oHeader.nStartPage  = 0;
	oHeader.phpage      = m_phPages;
	oHeader.pfnCallback = NULL;

	// Create it.
	int nResult = ::PropertySheet(&oHeader);

	ASSERT(nResult != -1);
    
    // Return 
	return nResult;
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

void CPropertySheet::PageTable(PAGE* pPageTable)
{
	ASSERT(m_pPageTable == NULL);
	ASSERT(pPageTable != NULL);

	PAGE* pPage = pPageTable;

	// Count the number of pages.
	while (pPage->m_pPage != NULL)
	{
		m_nPages++;
	    pPage++;
	}

	// Allocate memory for the copy.
	m_pPageTable = new PAGE[m_nPages];
	ASSERT(m_pPageTable);
	
	pPage = pPageTable;

	// Copy the table.
	for (int i = 0; i < m_nPages; i++)
	{
		ASSERT(pPage->m_pPage    != NULL);
		ASSERT(pPage->m_pszLabel != NULL);

		m_pPageTable[i].m_pPage    = pPage->m_pPage;
		m_pPageTable[i].m_pszLabel = pPage->m_pszLabel;

	    pPage++;
	}
}

/******************************************************************************
** Function:	PropSheetProc()
**
** Description:	This is the callback procedure for a property sheet.
**				
** Parameters:	Standard window procedure parameters.
**
** Returns:		0.
**
*******************************************************************************
*/

int CALLBACK PropSheetProc(HWND hWnd, UINT iMsg, LPARAM lParam)
{
	// Initialised?
	if (iMsg == PSCB_INITIALIZED)
	{
		// Get object from property page info.
		CPropertySheet* pDialog = (CPropertySheet*) NULL;

		// Save handle.
		pDialog->m_hWnd = hWnd;

		// Setup Window mapping.
		CWnd::s_WndMap.Add(*pDialog);

		// Now call initialise method.
		pDialog->OnInitDialog();
	}

	return 0;
}

/******************************************************************************
** Method:		OnInitDialog()
**
** Description:	The property sheet has been created.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPropertySheet::OnInitDialog()
{
}
