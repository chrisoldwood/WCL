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
	
protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/


#endif //PRINTERDC_HPP
