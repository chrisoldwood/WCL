/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SCREENDC.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CScreenDC class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Default Constructor.
**
** Description:	Creates a device for the display.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CScreenDC::CScreenDC()
{
	m_hWnd     = NULL;
	m_hDC      = GetDC(m_hWnd);
	m_iState   = SaveState();
	m_bRelease = true;
	
	ASSERT(m_hDC);
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	Creates a device for a window.
**
** Parameters:	rWnd		The window.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CScreenDC::CScreenDC(const CWnd& rWnd)
{
	m_hWnd     = rWnd.Handle();
	m_hDC      = GetDC(m_hWnd);
	m_iState   = SaveState();
	m_bRelease = true;

	ASSERT(m_hDC);
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	Creates a device from a PAINTSTRUCT. This is used in reponse
**				to a WM_PAINT message. BeginPaint ia called in the message
**				handler before constructing this. EndPaint is also called
**				in the message handler after use.
**
** Parameters:	psPaint		The filled in WM_PAINT paint structure.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CScreenDC::CScreenDC(PAINTSTRUCT& psPaint)
{
	m_hWnd     = NULL;
	m_hDC      = psPaint.hdc;
	m_iState   = SaveState();
	m_bRelease = false;

	ASSERT(m_hDC);
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	Creates a device from another HDC.
**
** Parameters:	hDC		The existing DC.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CScreenDC::CScreenDC(HDC hDC)
{
	m_hWnd     = NULL;
	m_hDC      = hDC;
	m_iState   = SaveState();
	m_bRelease = false;

	ASSERT(m_hDC);
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

CScreenDC::~CScreenDC()
{
	// Restore DC to inital settings.
	RestoreState(m_iState);
	
	// Free up DC.
	if (m_bRelease)
		::ReleaseDC(m_hWnd, m_hDC);
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

CDC::Device CScreenDC::Type() const
{
	return Screen;
}
