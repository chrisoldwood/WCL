/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SCREENDC.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CScreenDC class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SCREENDC_HPP
#define SCREENDC_HPP

// Forward declaration.
class CWnd;

/******************************************************************************
** 
** This is a Device derived class that is appropriate for drawing to the
** display such as painting windows.
**
*******************************************************************************
*/

class CScreenDC : public CDC
{
public:
	//
	// Constructors/Destructor.
	//
	CScreenDC();
	CScreenDC(const CWnd& rWnd);
	CScreenDC(PAINTSTRUCT& psPaint);
	CScreenDC(HDC hDC);
	~CScreenDC();
	
	// RTTI
	virtual	Device Type() const;
	
protected:
	//
	// Members.
	//
	HWND	m_hWnd;		// Window handle of windows' device context.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //SCREENDC_HPP
