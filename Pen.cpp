/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PEN.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPen class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Pen.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPen::CPen()
	: m_hPen(NULL)
	, m_bOwner(false)
{
}

CPen::CPen(int iID)
	: m_hPen()
	, m_bOwner()
{
	Create(iID);
}

CPen::CPen(int iStyle, int iWidth, COLORREF crClr)
	: m_hPen()
	, m_bOwner()
{
	Create(iStyle, iWidth, crClr);
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPen::~CPen()
{
	// Delete if valid and we own it.
	if ( (m_hPen) && (m_bOwner) )
		::DeleteObject(m_hPen);
}

void CPen::Create(int iID)
{
	m_hPen   = GetStockPen(iID);
	m_bOwner = false;

	ASSERT(m_hPen != NULL);
}

void CPen::Create(int iStyle, int iWidth, COLORREF crClr)
{
	m_hPen   = ::CreatePen(iStyle, iWidth, crClr);
	m_bOwner = true;

	ASSERT(m_hPen != NULL);
}
