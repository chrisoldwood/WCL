/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PRINTER.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPrinter class definition.
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
** Description:	Get the details of the default printer.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPrinter::CPrinter()
{
	char szDefault[256];
	
	// Get the defualt printer.
	GetProfileString("Windows", "Device", "", szDefault, sizeof(szDefault));
	
	// Is a default?
	if ( (szDefault[0] != '\0') && (strcmp(szDefault, ",,,") != 0) )
	{
		// Extract details.
		m_strName   = strtok(szDefault, ",");
		m_strDriver = strtok(NULL,      ",");
		m_strPort   = strtok(NULL,      ",");
	}
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

CPrinter::~CPrinter()
{
}

/******************************************************************************
** Method:		Select()
**
** Description:	Ask the user to select a printer using the common dialog.
**
** Parameters:	rParent		The dialogs parent.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPrinter::Select(const CWnd& rParent)
{
	PRINTDLG PrtDlg;
	
	// Initialise structure.
	memset(&PrtDlg, 0, sizeof(PRINTDLG));
	
	PrtDlg.lStructSize = sizeof(PRINTDLG);
	PrtDlg.hwndOwner   = rParent.Handle();
	PrtDlg.Flags       = PD_PRINTSETUP;
	
	// Call up the dialog.
	bool bOkay = PrintDlg(&PrtDlg);
	
	// User pressed OK?
	if (bOkay)
	{
		ASSERT(PrtDlg.hDevNames);
		
		// Get a pointer to the description.
		LPCSTR 		lpszDevNames = (LPCSTR) GlobalLock(PrtDlg.hDevNames);
		LPDEVNAMES	lpDevNames   = (LPDEVNAMES) lpszDevNames;
		
		// Copy description.
		m_strName   = lpszDevNames + lpDevNames->wDeviceOffset;
		m_strDriver = lpszDevNames + lpDevNames->wDriverOffset;
		m_strPort   = lpszDevNames + lpDevNames->wOutputOffset;
		
		// Unlock the decription.
		GlobalUnlock(PrtDlg.hDevNames);
	}
	
	// Free Devmode?
	if (PrtDlg.hDevMode)
		GlobalFree(PrtDlg.hDevMode);

	// Free Devnames?
	if (PrtDlg.hDevNames)
		GlobalFree(PrtDlg.hDevNames);
		
	return bOkay;
}
