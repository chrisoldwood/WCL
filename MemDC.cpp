/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMDC.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMemDC class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	Creates a compatible device.
**
** Parameters:	rDC		The DC to copy.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMemDC::CMemDC(const CDC& rDC)
{
	m_hDC     = CreateCompatibleDC(rDC.Handle());
	m_iState  = SaveState();
	m_devType = rDC.Type();

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

CMemDC::~CMemDC()
{
	// Restore DC to inital settings.
	RestoreState(m_iState);
	
	// Free up DC.
	DeleteDC(m_hDC);
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

CDC::Device CMemDC::Type() const
{
	return m_devType;
}
