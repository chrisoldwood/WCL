/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PRINTER.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPrinter class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PRINTER_HPP
#define PRINTER_HPP

/******************************************************************************
** 
** A wrapper class used to hold the parameters required to create a printer DC.
**
*******************************************************************************
*/

class CPrinter
{
public:
	//
	// Constructors/Destructor.
	//
	CPrinter();
	~CPrinter();
	
	bool Select(const CWnd& rParent);

	//
	// Members.
	//
	CString	m_strName;		// The human-readable name.
	CString	m_strDriver;	// The printer driver.
	CString	m_strPort;		// The output port.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //PRINTER_HPP
