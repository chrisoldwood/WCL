/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROPERTYDLG.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPropertyDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PROPERTYDLG_HPP
#define PROPERTYDLG_HPP

/******************************************************************************
** 
** This is the base class for all property style dialogs.
**
*******************************************************************************
*/

class CPropertyDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CPropertyDlg(uint nRscID, int nTabCtrlID);
	~CPropertyDlg();
	
protected:
	/////////////////////////////////////////////////////////////////
	// Structure to define an entry in the property page table.
	/////////////////////////////////////////////////////////////////

	typedef struct tagPAGEDLG
	{
		CPropertyPageDlg*	m_pPageDlg;		// The page.
		const char*			m_pszLabel;		// The tab label.
	} PAGEDLG;

	//
	// Members.
	//
	int			m_nPages;		// Number of pages.
	PAGEDLG*	m_pPageTable;	// Table of pages.
	CTabCtrl	m_oTabCtrl;		// The tab control page host.

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual bool OnOk();
	     LRESULT OnSelChanging(NMHDR& rMsgHdr);
	     LRESULT OnSelChange(NMHDR& rMsgHdr);

	//
	// Internal methods.
	//
	void PageTable(PAGEDLG* pPageTable);
};

/******************************************************************************
** 
** Macros used to ease the definition of the control table.
**
*******************************************************************************
*/

#define DEFINE_PAGE_TABLE	PAGEDLG Pages[] = {

#define PAGE(page, label)	{ (page), (label) },

#define END_PAGE_TABLE		{  NULL,   NULL } }; \
							PageTable(Pages);

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //PROPERTYDLG_HPP
