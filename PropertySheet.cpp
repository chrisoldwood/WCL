/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROPERTYSHEET.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPropertySheet class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "PropertySheet.hpp"
#include "PropertyPage.hpp"
#include "Module.hpp"

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

bool CPropertySheet::RunModeless(CWnd& /*rParent*/)
{
/*	// Initalise members.
	m_bModal = false;

	ASSERT(rParent.Handle());
	ASSERT(CModule::This().Handle());
	ASSERT(m_iRscID);

	// Create it.
	HWND hWnd = CreateDialogParam(CModule::This().Handle(), MAKEINTRESOURCE(m_iRscID),
									rParent.Handle(), DlgProc, this);

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

	// Add the pages.
	for (size_t i = 0; i < m_vPages.size(); ++i)
	{
		PAGE_ENTRY& rPage = m_vPages[i];

		// Initialise the page.
		PROPSHEETPAGE oPage = { 0 };

		oPage.dwSize      = sizeof(oPage);
		oPage.dwFlags     = PSP_DEFAULT | PSP_PREMATURE | PSP_USETITLE;
		oPage.hInstance   = CModule::This().Handle();
		oPage.pszTemplate = MAKEINTRESOURCE(rPage.m_pPage->m_iRscID);
		oPage.hIcon       = NULL;
		oPage.pszTitle    = rPage.m_pszLabel;
		oPage.pfnDlgProc  = CPropertyPage::PropPageProc;
		oPage.lParam      = reinterpret_cast<LPARAM>(rPage.m_pPage);
		oPage.pfnCallback = NULL;
		oPage.pcRefParent = NULL;

		// Create it.
		m_vHandles[i] = ::CreatePropertySheetPage(&oPage);

		ASSERT(m_vHandles[i] != NULL);
	}

	// Initialise the header.
	PROPSHEETHEADER oHeader = { 0 };

	oHeader.dwSize      = sizeof(oHeader);
	oHeader.dwFlags     = PSH_DEFAULT | PSH_NOAPPLYNOW;
	oHeader.hwndParent  = rParent.Handle();
	oHeader.hInstance   = CModule::This().Handle();
	oHeader.hIcon       = NULL;
	oHeader.pszCaption  = m_strTitle;
	oHeader.nPages      = static_cast<int>(m_vPages.size());
	oHeader.nStartPage  = 0;
	oHeader.phpage      = (!m_vHandles.empty()) ? &m_vHandles.front() : nullptr;
	oHeader.pfnCallback = NULL;

	// Create it.
	WCL::DlgResult nResult = ::PropertySheet(&oHeader);

	ASSERT(nResult != -1);
    
    // Return 
	return static_cast<int>(nResult);
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

void CPropertySheet::PageTable(PAGE_ENTRY* pPageTable)
{
	ASSERT(m_vPages.empty());
	ASSERT(pPageTable != NULL);

	size_t nPages = 0;

	// Count the number of pages.
	for (PAGE_ENTRY* pPage = pPageTable; (pPage->m_pPage != NULL); ++pPage)
	    ++nPages;

	m_vPages.resize(nPages);

	std::copy(pPageTable, pPageTable+nPages, m_vPages.begin());
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

int CALLBACK PropSheetProc(HWND hWnd, UINT iMsg, LPARAM /*lParam*/)
{
	// Initialised?
	if (iMsg == PSCB_INITIALIZED)
	{
		ASSERT_FALSE();

		// Get object from property page info.
		CPropertySheet* pDialog = reinterpret_cast<CPropertySheet*>(NULL);

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
