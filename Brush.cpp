/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BRUSH.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CBrush class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Brush.hpp"

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

CBrush::CBrush()
	: m_hBrush(NULL)
	, m_bOwner(false)
{
}

CBrush::CBrush(int iID)
	: m_hBrush()
	, m_bOwner()
{
	Create(iID);
}

CBrush::CBrush(COLORREF crClr)
	: m_hBrush()
	, m_bOwner()
{
	Create(crClr);
}

CBrush::CBrush(HBRUSH hBrush, bool bOwn)
	: m_hBrush()
	, m_bOwner()
{
	m_hBrush = hBrush;
	m_bOwner = bOwn;

	ASSERT(m_hBrush != NULL);
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

CBrush::~CBrush()
{
	// Delete if valid and we own it.
	if ( (m_hBrush) && (m_bOwner) )
		::DeleteObject(m_hBrush);
}

void CBrush::Create(int iID)
{
	m_hBrush = GetStockBrush(iID);
	m_bOwner = false;

	ASSERT(m_hBrush != NULL);
}

void CBrush::Create(COLORREF crClr)
{
	m_hBrush = ::CreateSolidBrush(crClr);
	m_bOwner = true;

	ASSERT(m_hBrush != NULL);
}
