/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PRINTERDC.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPrinterDC class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Default Constructor.
**
** Description:	Creates a device for the given printer.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPrinterDC::CPrinterDC(const CPrinter& rPrinter)
{
	// Try and create it.
	m_hDC = ::CreateDC(rPrinter.m_strDriver, rPrinter.m_strName, rPrinter.m_strPort, NULL);
	ASSERT(m_hDC);
	
	// Save current state.
	m_iState = SaveState();
}

/******************************************************************************
** Method:		Destructor
**
** Description:	Cleans up the DC before freeing.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPrinterDC::~CPrinterDC()
{
	// Restore DC to inital settings.
	RestoreState(m_iState);

	// Release it.
	::DeleteDC(m_hDC);
}

/******************************************************************************
** Method:		Type()
**
** Description:	Returns the actual type of the device. This is used when you
**				need to know the actual device type to perform different
**				drawing actions and you only have a Device.
**
** Parameters:	None.
**
** Returns:		The device enumerated type.
**
*******************************************************************************
*/

CDC::Device CPrinterDC::Type() const
{
	return Printer;
}

/******************************************************************************
** Method:		Start()
**
** Description:	Start a new document.
**
** Parameters:	pszTitle	The title of the new document.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPrinterDC::Start(const char* pszTitle)
{
	DOCINFO DocInfo;

	ASSERT(pszTitle);
	ASSERT(m_hDC);
	
	// Initialise.
	DocInfo.cbSize      = sizeof(DOCINFO);
	DocInfo.lpszDocName = pszTitle;
	DocInfo.lpszOutput  = NULL;
	
	int iError = StartDoc(m_hDC, &DocInfo);

	return (iError != SP_ERROR);
}

/******************************************************************************
** Method:		Abort()
**
** Description:	Abort printing the current document.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPrinterDC::Abort()
{
	ASSERT(m_hDC);

	AbortDoc(m_hDC);
}

/******************************************************************************
** Method:		End()
**
** Description:	Finish printing the document.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPrinterDC::End()
{
	ASSERT(m_hDC);

	int iError = EndDoc(m_hDC);

	return (iError >= 0);
}

/******************************************************************************
** Method:		StartPage()
**
** Description:	Start a new page of the document.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPrinterDC::StartPage()
{
	ASSERT(m_hDC);

	int iError = ::StartPage(m_hDC);

	return (iError >= 0);
}

/******************************************************************************
** Method:		EndPage()
**
** Description:	Finish printing the current page.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPrinterDC::EndPage()
{
	ASSERT(m_hDC);

	int iError = ::EndPage(m_hDC);

	return (iError >= 0);
}

/******************************************************************************
** Method:		PageArea()
**
** Description:	Gets the area for the page in pixels.
**
** Parameters:	None.
**
** Returns:		The page area.
**
*******************************************************************************
*/

CRect CPrinterDC::PageArea() const
{
	ASSERT(m_hDC);

	return CRect(0, 0, HorzRes(), VertRes());
}

/******************************************************************************
** Method:		PrintableArea()
**
** Description:	Gets the printable area for the page in pixels.
**
** Parameters:	None.
**
** Returns:		The printable area.
**
*******************************************************************************
*/

CRect CPrinterDC::PrintableArea() const
{
	ASSERT(m_hDC);

	CPoint	ptOffset(0, 0);
	CRect	rcPage = PageArea();

	// Get margin and adjust page.
	if (Escape(m_hDC, GETPRINTINGOFFSET, 0, NULL, &ptOffset) > 0)
	{
		rcPage.left    += ptOffset.x;
		rcPage.top     += ptOffset.y;
		rcPage.right   -= ptOffset.x;
		rcPage.bottom  -= ptOffset.y;
	}
	
	return rcPage;
}
