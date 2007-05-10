/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAINDLG.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMainDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MAINDLG_HPP
#define MAINDLG_HPP

/******************************************************************************
** 
** This is the base class for the main dialog in a dialog based app.
**
*******************************************************************************
*/

class CMainDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CMainDlg(uint iRscID);
	virtual	~CMainDlg();
	
protected:
	//
	// Members.
	//
	
	//
	// Message processors.
	//
	virtual	void OnPaint(CDC& rDC);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MAINDLG_HPP
