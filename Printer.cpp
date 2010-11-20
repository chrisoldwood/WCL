/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PRINTER.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPrinter class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Printer.hpp"
#include "Wnd.hpp"

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
	: m_strName()
	, m_strDriver()
	, m_strPort()
{
	const size_t MAX_LEN = 1024;
	tchar szPrinter[MAX_LEN+1] = { 0 };

	// Get the defualt printer.
	GetProfileString(TXT("Windows"), TXT("Device"), TXT(""), szPrinter, MAX_LEN);

	// Is a default?
	if ( (szPrinter[0] != TXT('\0')) && (tstrcmp(szPrinter, TXT(",,,")) != 0) )
	{
		// Extract details.
		m_strName   = tstrtok(szPrinter, TXT(","));
		m_strDriver = tstrtok(NULL,      TXT(","));
		m_strPort   = tstrtok(NULL,      TXT(","));
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
		const tchar* lpszDevNames  = static_cast<const tchar*>(GlobalLock(PrtDlg.hDevNames));
		const DEVNAMES* lpDevNames = reinterpret_cast<const DEVNAMES*>(lpszDevNames);

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
