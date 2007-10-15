/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROPERTYSHEET.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPropertySheet class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PROPERTYSHEET_HPP
#define PROPERTYSHEET_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Wnd.hpp"

// Forward declarations.
class CPropertyPage;

/******************************************************************************
** 
** This is the base class for all property style dialogs.
**
*******************************************************************************
*/

class CPropertySheet : public CWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CPropertySheet();
	virtual	~CPropertySheet();
	
	//
	// Creation methods (Overriden from CDialog).
	//
	virtual bool RunModeless(CWnd& rParent);
	virtual int  RunModal(CWnd& rParent);

protected:
	/////////////////////////////////////////////////////////////////
	// Structure to define an entry in the property page table.
	/////////////////////////////////////////////////////////////////

	typedef struct tagPAGE
	{
		CPropertyPage*	m_pPage;		// The page.
		const char*		m_pszLabel;		// The tab label.
	} PAGE;

	//
	// Members.
	//
	CString			m_strTitle;		// Title for the property sheet.
	int				m_nPages;		// Number of pages.
	PAGE*			m_pPageTable;	// Table of pages.
	HPROPSHEETPAGE*	m_phPages;		// Array of page handles.

	//
	// General message handlers.
	//
	friend int CALLBACK PropSheetProc(HWND hWnd, UINT iMsg, LPARAM lParam);

	//
	// Message processors.
	//
	virtual void OnInitDialog();

	//
	// Internal methods.
	//
	void PageTable(PAGE* pPageTable);
};

/******************************************************************************
** 
** Macros used to ease the definition of the control table.
**
*******************************************************************************
*/

#define DEFINE_PAGE_TABLE	PAGE Pages[] = {

#define PAGE(page, label)	{ (page), (label) },

#define END_PAGE_TABLE		{  NULL,   NULL } }; \
							PageTable(Pages);

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //PROPERTYSHEET_HPP
