/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CMDBMP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CCmdBitmap class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "CmdBmp.hpp"
#include "Brush.hpp"
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

CCmdBitmap::CCmdBitmap()
	: m_iCmdSize()
	, m_EnabledBmp()
	, m_DisabledBmp()
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

CCmdBitmap::~CCmdBitmap()
{
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Load the initial bitmap from the resource file and create the
**				enabled and disabled state bitmaps.
**
** Parameters:	iRscID		The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCmdBitmap::LoadRsc(uint iRscID)
{
	CBitmap	bmpCmds;
	CBitmap	bmpMask;
	CBitmap	bmpMask2;

    // Load the resource bitmap.
    bmpCmds.LoadRsc(iRscID);

	// Get dimensions.
	CSize BmpSize = bmpCmds.Size();
	m_iCmdSize = BmpSize.cy;

	// Create brushes.
	CBrush	FaceBrush(::GetSysColor(COLOR_BTNFACE));
	CBrush	LightBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
	CBrush	DarkBrush(::GetSysColor(COLOR_BTNSHADOW));

	// Setup DCs.
	CScreenDC	ScnDC;
	CMemDC		ButtonsDC(ScnDC);
	CMemDC		EnabledDC(ScnDC);
	CMemDC		DisabledDC(ScnDC);
	CMemDC		MaskDC(ScnDC);
	CMemDC		Mask2DC(ScnDC);

	// Allocate the final bitmaps.
	m_EnabledBmp.Create(BmpSize, ScnDC);
	m_DisabledBmp.Create(BmpSize, ScnDC);

	// Allocate the temp bitmaps.
	bmpMask.Create(BmpSize);
	bmpMask2.Create(BmpSize);

	// Select bitmaps into DCs.
	ButtonsDC.Select(bmpCmds);
	EnabledDC.Select(m_EnabledBmp);
	DisabledDC.Select(m_DisabledBmp);
	MaskDC.Select(bmpMask);
	Mask2DC.Select(bmpMask2);

	// Create button background.
	EnabledDC.Select(FaceBrush);
	EnabledDC.PatBlt(CRect(CPoint(0,0), BmpSize));

	DisabledDC.Select(FaceBrush);
	DisabledDC.PatBlt(CRect(CPoint(0,0), BmpSize));

	// Create general mask.
	ButtonsDC.BkColour(RGB(192,192,192));

	::BitBlt(MaskDC.Handle(), 0, 0, BmpSize.cx, BmpSize.cy,
				ButtonsDC.Handle(), 0, 0, SRCCOPY);

	// Create special white mask.
	ButtonsDC.BkColour(RGB(255,255,255));

	::BitBlt(Mask2DC.Handle(), 0, 0, BmpSize.cx, BmpSize.cy,
				ButtonsDC.Handle(), 0, 0, SRCCOPY);

	// Create enabled state
	::BitBlt(EnabledDC.Handle(), 0, 0, BmpSize.cx, BmpSize.cy,
				MaskDC.Handle(), 0, 0, SRCAND);

	MaskDC.PatBlt(CRect(CPoint(0,0), BmpSize), DSTINVERT);

	ButtonsDC.BkColour(RGB(255,255,255));

	::BitBlt(ButtonsDC.Handle(), 0, 0, BmpSize.cx, BmpSize.cy,
				MaskDC.Handle(), 0, 0, SRCAND);

	::BitBlt(EnabledDC.Handle(), 0, 0, BmpSize.cx, BmpSize.cy,
				ButtonsDC.Handle(), 0, 0, SRCPAINT);

	// Create disabled state.
	MaskDC.PatBlt(CRect(CPoint(0,0), BmpSize), DSTINVERT);

	::BitBlt(MaskDC.Handle(), 0, 0, BmpSize.cx, BmpSize.cy,
				Mask2DC.Handle(), 0, 0, SRCPAINT);

	DisabledDC.Select(LightBrush);

	::BitBlt(DisabledDC.Handle(), 1, 1, BmpSize.cx, BmpSize.cy,
				MaskDC.Handle(), 0, 0, 0x00B8074AL);

	DisabledDC.Select(DarkBrush);

	::BitBlt(DisabledDC.Handle(), 0, 0, BmpSize.cx, BmpSize.cy,
				MaskDC.Handle(), 0, 0, 0x00B8074AL);
}

/******************************************************************************
** Method:		DrawCmd()
**
** Description:	Draw the commands icon.
**
** Parameters:	iIndex		The command to draw.
**				rDC			The destination device.
**				rDst		The destination rect.
**				bEnabled	Enabled or disabled?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CCmdBitmap::DrawCmd(uint iIndex, CDC& rDC, const CRect& rDst, bool bEnabled) const
{
	// Calculate source rectangle.
	CRect	rcSrc(iIndex*m_iCmdSize, 0, (iIndex+1)*m_iCmdSize, m_iCmdSize);

	// Draw it.
	if (bEnabled)
		rDC.BitBlt(m_EnabledBmp,  rcSrc, rDst);
	else
		rDC.BitBlt(m_DisabledBmp, rcSrc, rDst);
}
