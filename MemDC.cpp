/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMDC.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMemDC class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "MemDC.hpp"

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

#ifdef _DEBUG
	// Passify BoundsChecker.
	m_hOrgBitmap  = reinterpret_cast<HBITMAP> (::GetCurrentObject(m_hDC, OBJ_BITMAP));
	m_hOrgBrush   = reinterpret_cast<HBRUSH>  (::GetCurrentObject(m_hDC, OBJ_BRUSH ));
	m_hOrgFont    = reinterpret_cast<HFONT>   (::GetCurrentObject(m_hDC, OBJ_FONT  ));
	m_hOrgPalette = reinterpret_cast<HPALETTE>(::GetCurrentObject(m_hDC, OBJ_PAL   ));
	m_hOrgPen     = reinterpret_cast<HPEN>    (::GetCurrentObject(m_hDC, OBJ_PEN   ));
#endif
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
	
#ifdef _DEBUG
	// Passify BoundsChecker.
	::SelectObject (m_hDC, m_hOrgBitmap );
	::SelectObject (m_hDC, m_hOrgBrush  );
	::SelectObject (m_hDC, m_hOrgFont   );
	::SelectPalette(m_hDC, m_hOrgPalette, FALSE);
	::SelectObject (m_hDC, m_hOrgPen    );
#endif

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
