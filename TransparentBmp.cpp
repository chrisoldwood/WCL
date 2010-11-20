/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TRANSPARENTBMP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CTransparentBmp class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "TransparentBmp.hpp"
#include "ScreenDC.hpp"
#include "MemDC.hpp"

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

CTransparentBmp::CTransparentBmp()
	: m_bmpMask()
	, m_bmpImage()
	, m_Size()
	, m_clrTransparent(RGB(0,0,0))
{
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

CTransparentBmp::~CTransparentBmp()
{
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads a bitmap from the resource file and creates the mask.
**
** Parameters:	iRscID				The resource ID.
**				clrTransparent		The colour to make transparent.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTransparentBmp::LoadRsc(uint iRscID, COLORREF clrTransparent)
{
	ASSERT(m_bmpMask.Handle()  == NULL);
	ASSERT(m_bmpImage.Handle() == NULL);

	// Load the bitmap and get its size..
	m_bmpImage.LoadRsc(iRscID);
	m_Size = m_bmpImage.Size();

	// Setup DCs.
	CScreenDC	ScnDC;
	CMemDC		MaskDC(ScnDC);
	CMemDC		ImageDC(ScnDC);

	// Allocate the mask bitmap.
	m_bmpMask.Create(m_Size);

	// Select bitmaps into DCs.
	MaskDC.Select(m_bmpMask);
	ImageDC.Select(m_bmpImage);

	// Create the mask.
	ImageDC.BkColour(clrTransparent);
	::BitBlt(MaskDC.Handle(), 0, 0, m_Size.cx, m_Size.cy, ImageDC.Handle(), 0, 0, SRCCOPY);

	// Invert the mask.
	MaskDC.PatBlt(CRect(CPoint(0,0), m_Size), DSTINVERT);

	// Convert the background to black.
	ImageDC.BkColour(RGB(255,255,255));
	::BitBlt(ImageDC.Handle(), 0, 0, m_Size.cx, m_Size.cy, MaskDC.Handle(), 0, 0, SRCAND);

	// Restore the mask.
	MaskDC.PatBlt(CRect(CPoint(0,0), m_Size), DSTINVERT);
}
