/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDIDOC.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CSDIDoc class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SDIDOC_HPP
#define SDIDOC_HPP

/******************************************************************************
** 
** This is the base class for documents used with a SDI app.
**
*******************************************************************************
*/

class CSDIDoc : public CDoc
{
public:
	//
	// Constructors/Destructor.
	//
	CSDIDoc();
	~CSDIDoc();
	
	//
	// Members.
	//
	CView*	m_pView;	// The documents' view.

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

#endif //SDIDOC_HPP
