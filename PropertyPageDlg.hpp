/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROPERTYPAGEDLG.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPropertyPageDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PROPERTYPAGEDLG_HPP
#define PROPERTYPAGEDLG_HPP

/******************************************************************************
** 
** This is the base class for all property page dialogs.
**
*******************************************************************************
*/

class CPropertyPageDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CPropertyPageDlg(uint nRscID);
	~CPropertyPageDlg();
	
protected:
	//
	// Members.
	//


	//
	// Friends.
	//
	friend class CPropertyDlg;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //PROPERTYPAGEDLG_HPP
