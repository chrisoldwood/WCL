/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PRINTERDC.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPrinterDC class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PRINTERDC_HPP
#define PRINTERDC_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "DC.hpp"

// Forward declarations.
class CPrinter;

/******************************************************************************
** 
** This is a CDC derived class that is used for printing. 
**
*******************************************************************************
*/

class CPrinterDC : public CDC
{
public:
	//
	// Constructors/Destructor.
	//
	CPrinterDC(const CPrinter& rPrinter);
	~CPrinterDC();

	// RTTI
	virtual	Device Type() const;

	//
	// Commands.
	//
	bool Start(const char* pszTitle);
	void Abort();
	bool End();
	bool StartPage();
	bool EndPage();

	//
	// Attributes.
	//
	CRect PageArea() const;
	CRect PrintableArea() const;
	int   PageNum() const;
	
protected:
	//
	// Members.
	//
	int	m_nPage;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/


inline int CPrinterDC::PageNum() const
{
	return m_nPage;
}

#endif //PRINTERDC_HPP
