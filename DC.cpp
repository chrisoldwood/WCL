/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DC.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDC class methods.
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
** Description:	Initialise the members.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDC::CDC()
{
	m_hDC      = NULL;
	m_bRelease = false;
	m_iState   = 0;
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

CDC::~CDC()
{
}

/******************************************************************************
** Method:		Border3D()
**
** Description:	Draw a 3D style recessed border.
**
** Parameters:	rcRect		The bounding rectangle.
**				bRaised		Flag to determine if raised or etched.
**				bThick		Flag to detrmine if thin or thick broder.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDC::Border3D(const CRect& rcRect, bool bRaised, bool bThick)
{
	const CPen* pOuterTopPen = NULL;
	const CPen* pInnerTopPen = NULL;
	const CPen* pOuterBotPen = NULL;
	const CPen* pInnerBotPen = NULL;
	CRect rcBorder           = rcRect;

	// Get application object.
	CApp& oApp = CApp::This();

	// Get the pens.
	if (bRaised)
	{
		pOuterTopPen = &oApp.LightestPen();
		pOuterBotPen = &oApp.DarkestPen();

		if (bThick)
		{
			pInnerTopPen = &oApp.LightPen();
			pInnerBotPen = &oApp.DarkPen();
		}
	}
	// Recessed.
	else
	{
		pOuterTopPen = &oApp.DarkPen();
		pOuterBotPen = &oApp.LightestPen();

		if (bThick)
		{
			pInnerTopPen = &oApp.DarkestPen();
			pInnerBotPen = &oApp.LightPen();
		}
	}

	if (bThick)
	{
		// Draw inside top edge.
		Select(*pInnerTopPen);
		Move(rcBorder.left+1,  rcBorder.bottom-2);
		Line(rcBorder.left+1,  rcBorder.top+1);
		Line(rcBorder.right-2, rcBorder.top+1);

		// Draw inside bottom edge.
		Select(*pInnerBotPen);
		Move(rcBorder.right-2, rcBorder.top+1);
		Line(rcBorder.right-2, rcBorder.bottom-2);
		Line(rcBorder.left+1,  rcBorder.bottom-2);
	}

	// Draw outside top edge.
	Select(*pOuterTopPen);
	Move(rcBorder.left,    rcBorder.bottom-1);
	Line(rcBorder.left,    rcBorder.top);
	Line(rcBorder.right-1, rcBorder.top);

	// Draw outside bottom edge.
	Select(*pOuterBotPen);
	Move(rcBorder.right-1, rcBorder.top);
	Line(rcBorder.right-1, rcBorder.bottom-1);
	Line(rcBorder.left,    rcBorder.bottom-1);
}

/******************************************************************************
** Method:		HorzLine3D()
**
** Description:	Draw a 3D style horizontal line.
**
** Parameters:	iSX, iDX	The horizontal end points.
**				iY			The vertical position.
**				bRaised		Flag to determine if raised or etched.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDC::HorzLine3D(int iSX, int iDX, int iY, bool bRaised)
{
	// Get application object.
	CApp& oApp = CApp::This();

	// Get the pens.
	const CPen* pTopPen = (bRaised) ? &oApp.LightestPen() : &oApp.DarkPen();
	const CPen* pBotPen = (bRaised) ? &oApp.DarkPen()     : &oApp.LightestPen();

	// Draw the lines.
	Select(*pTopPen);
	Line(iSX, iY, iDX, iY);

	Select(*pBotPen);
	Line(iSX, iY+1, iDX, iY+1);
}

/******************************************************************************
** Method:		VertLine3D()
**
** Description:	Draw a 3D style vertical line.
**
** Parameters:	iX			The horizontal position.
**				iSY, iDY	The vertical end points.
**				bRaised		Flag to determine if raised or etched.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDC::VertLine3D(int iX, int iSY, int iDY, bool bRaised)
{
	// Get application object.
	CApp& oApp = CApp::This();

	// Get the pens.
	const CPen* pTopPen = (bRaised) ? &oApp.LightestPen() : &oApp.DarkPen();
	const CPen* pBotPen = (bRaised) ? &oApp.DarkPen()     : &oApp.LightestPen();

	// Draw the lines.
	Select(*pTopPen);
	Line(iX, iSY, iX, iDY);

	Select(*pBotPen);
	Line(iX+1, iSY, iX+1, iDY);
}

/******************************************************************************
** Method:		TextExtents()
**
** Description:	Get the extents for a piece of text. This uses the currently
**				selected font.
**
** Parameters:	oFont		The font to use for the calculation.
**				pszText		The text, NULL terminated.
**
** Returns:		The dimensions.
**
*******************************************************************************
*/

CSize CDC::TextExtents(const char* pszText) const
{
	CSize Size;

	GetTextExtentPoint(m_hDC, pszText, lstrlen(pszText), &Size);
	
	return Size;
}

CSize CDC::TextExtents(const CFont& oFont, const char* pszText) const
{
	// NB: Only changes HDC, not 'this'.
	const_cast<CDC*>(this)->Select(oFont);

	return TextExtents(pszText);
}

/******************************************************************************
** Method:		MapMode()
**
** Description:	Set the mapping mode to an arbitrary scale. The mapping is made
**				as X device units = X logical units and similarly for the Y
**				axis.
**
** Parameters:	rDeviceUnits	These two parameters specify the ratios between
**				rLogicalUnits	pixels and logical units for both X & Y axis.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDC::MapMode(const CSize& rDeviceUnits, const CSize& rLogicalUnits)
{
	MapMode(MM_ANISOTROPIC);
	SetWindowExtEx(m_hDC,   rLogicalUnits.cx, rLogicalUnits.cy, NULL);
	SetViewportExtEx(m_hDC, rDeviceUnits.cx,  rDeviceUnits.cy, NULL);
}

/******************************************************************************
** Method:		BitBlt()
**
** Description:	BitBlt the bitmap at the position given.
**
** Parameters:	rBitmap		The bitmap to blt.
**				rcSrc		The source bitmap region.
**				rcDst		The destination device region.
**				dwRop		The ROP code to use.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDC::BitBlt(const CBitmap& rBitmap, const CRect& rcSrc, const CRect& rcDst,
				DWORD dwRop)
{
	CMemDC	SrcDC(*this);

	// Select bitmap into source dc.
	SrcDC.Select(rBitmap);
	
	// Blit it...
	::StretchBlt(m_hDC, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(),
				SrcDC.Handle(), rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(),
				dwRop);
}

/******************************************************************************
** Method:		BitBlt()
**
** Description:	BitBlt the transparent bitmap at the position given.
**
** Parameters:	rBitmap		The transparent bitmap to blt.
**				rcSrc		The source bitmap region.
**				rcDst		The destination device region.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDC::BitBlt(const CTransparentBmp& rBitmap, const CRect& rcSrc, const CRect& rcDst)
{
	// Use the mask to cut out a hole.
	BitBlt(rBitmap.Mask(),  rcSrc, rcDst, SRCAND);

	// 'OR' in the image data.
	BitBlt(rBitmap.Image(), rcSrc, rcDst, SRCPAINT);
}
