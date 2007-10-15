/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DC.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDC class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef DC_HPP
#define DC_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Point.hpp"
#include "Rect.hpp"
#include "Pen.hpp"
#include "Brush.hpp"
#include "Font.hpp"
#include "Bitmap.hpp"

// Forward declaraations.
class CTransparentBmp;

/******************************************************************************
** 
** This is an abstract base class from which all DCs are derived. All the
** methods are common to all forms of devices.
**
*******************************************************************************
*/

class CDC
{
public:
	//
	// Constructors/Destructor.
	//
	CDC();
	virtual ~CDC();
	
	//
	// Member access.
	//
	HDC Handle() const;

	//
	// CDC types
	//
	enum Device
	{
		Screen,			// The current display driver.
		Printer,		// A printer.
		Metafile		// A metafile.
	};

	// RTTI (Overridden by derived classes.)
	virtual Device Type() const = 0;

	//
	// Attributes.
	//
	int HorzRes() const;
	int VertRes() const;
	CSize TextExtents(const char* pszText) const;
	CSize TextExtents(const CFont& oFont, const char* pszText) const;

	//
	// State.
	//
	int SaveState();
	bool RestoreState(int iState = -1);

	//
	// GDI object selection.
	//
	void Select(const CPen&    rPen);
	void Select(const CBrush&  rBrush);
	void Select(const CFont&   rFont);
	void Select(const CBitmap& rBitmap);

	//
	// Co-ordinate mapping.
	//
    int MapMode(int iMode);
	void MapMode(const CSize& rDeviceUnits, const CSize& rLogicalUnits);
	void ViewportOrigin(int iX, int iY);
	void ViewportOrigin(const CPoint& rptOrigin);
	void LPtoDP(CPoint* pPoints, int iNumPoints) const;
	void DPtoLP(CPoint* pPoints, int iNumPoints) const;
	
	//
	// Line drawing.
	//
	void Move(int iX, int iY);
	void Move(const CPoint& rPoint);
	void Line(int iX, int iY);
	void Line(const CPoint& rPoint);
	void Line(int iSX, int iSY, int iDX, int iDY);
	void Line(const CPoint& rSrcPoint, const CPoint& rDstPoint);

	//
	// 3D effects.
	//
	void HorzLine3D(int iSX, int iDX, int iY, bool bRaised);
	void VertLine3D(int iX, int iSY, int iDY, bool bRaised);
	void Border3D(const CRect& rRect, bool bRaised, bool bThick);

	//
	// Shape drawing.
	//
	void Rectangle(const CRect& rRect);
	void Ellipse(const CRect& rRect);
	void Arc(const CRect& rRect, const CPoint& ptStart, const CPoint& ptEnd);
	void Fill(const CRect& rRect, const CBrush& rBrush);

	//
	// Text drawing.
	//
    COLORREF TextColour(COLORREF crColour);
    COLORREF BkColour(COLORREF crColour);
	int BkMode(int iMode);
	void TextOut(int iX, int iY, const char* pszText);
	void TextOut(const CPoint& rptOrigin, const char* pszText);
	void DrawText(const CRect& rcRect, const char* pszText, int nFormat);
	
	//
	// Bit blitting.
	//
	void BitBlt(const CBitmap& rBitmap, const CRect& rcSrc, const CRect& rcDst, DWORD dwRop = SRCCOPY);
	void BitBlt(const CTransparentBmp& rBitmap, const CRect& rcSrc, const CRect& rcDst);
	void PatBlt(const CRect& rcDst, DWORD dwRop = PATCOPY);
	
protected:
	//
	// Members.
	//
	HDC		m_hDC;			// CDC context.
	bool	m_bRelease;		// Call ReleaseDC on destruction?
	int		m_iState;		// Initial DC state (From SaveDC).

#ifdef _DEBUG
	// To passify BoundsChecker.
	HBITMAP		m_hOrgBitmap;
	HBRUSH		m_hOrgBrush;
	HFONT		m_hOrgFont;
	HPALETTE	m_hOrgPalette;
	HPEN		m_hOrgPen;
#endif

	//
	// Internal methods.
	//
};


/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HDC CDC::Handle() const
{
	return m_hDC;
}

inline int CDC::HorzRes() const
{
	return ::GetDeviceCaps(m_hDC, HORZRES);
}

inline int CDC::VertRes() const
{
	return ::GetDeviceCaps(m_hDC, VERTRES);
}

inline int CDC::SaveState()
{
	return ::SaveDC(m_hDC);
}

inline bool CDC::RestoreState(int iState)
{
	return ::RestoreDC(m_hDC, iState);
}

inline void CDC::Select(const CPen& rPen)
{
	ASSERT(m_hDC);
	ASSERT(rPen.Handle());

	SelectPen(m_hDC, rPen.Handle());
}

inline void CDC::Select(const CBrush& rBrush)
{
	ASSERT(m_hDC);
	ASSERT(rBrush.Handle());

	SelectBrush(m_hDC, rBrush.Handle());
}

inline void CDC::Select(const CFont& rFont)
{
	ASSERT(m_hDC);
	ASSERT(rFont.Handle());

	SelectFont(m_hDC, rFont.Handle());
}

inline void CDC::Select(const CBitmap& rBitmap)
{
	ASSERT(m_hDC);
	ASSERT(rBitmap.Handle());

	SelectBitmap(m_hDC, rBitmap.Handle());
}

inline void CDC::Move(int iX, int iY)
{
	::MoveToEx(m_hDC, iX, iY, NULL);
}

inline void CDC::Move(const CPoint& rPoint)
{
	::MoveToEx(m_hDC, rPoint.x, rPoint.y, NULL);
}

inline void CDC::Line(int iX, int iY)
{
	::LineTo(m_hDC, iX, iY);
}

inline void CDC::Line(const CPoint& rPoint)
{
	::LineTo(m_hDC, rPoint.x, rPoint.y);
}

inline void CDC::Line(int iSX, int iSY, int iDX, int iDY)
{
	::MoveToEx(m_hDC, iSX, iSY, NULL);
	::LineTo(m_hDC, iDX, iDY);
}

inline void CDC::Line(const CPoint& rSrcPoint, const CPoint& rDstPoint)
{
	::MoveToEx(m_hDC, rSrcPoint.x, rSrcPoint.y, NULL);
	::LineTo(m_hDC, rDstPoint.x, rDstPoint.y);
}

inline int CDC::MapMode(int iMode)
{
	return ::SetMapMode(m_hDC, iMode);
}

inline void CDC::ViewportOrigin(int iX, int iY)
{
	::SetViewportOrgEx(m_hDC, iX, iY, NULL);
}

inline void CDC::ViewportOrigin(const CPoint& rptOrigin)
{
	::SetViewportOrgEx(m_hDC, rptOrigin.x, rptOrigin.y, NULL);
}

inline void CDC::LPtoDP(CPoint* pPoints, int iNumPoints) const
{
	::LPtoDP(m_hDC, (LPPOINT) pPoints, iNumPoints);
}

inline void CDC::DPtoLP(CPoint* pPoints, int iNumPoints) const
{
	::DPtoLP(m_hDC, (LPPOINT) pPoints, iNumPoints);
}

inline void CDC::Rectangle(const CRect& rRect)
{
	::Rectangle(m_hDC, rRect.left, rRect.top, rRect.right, rRect.bottom);
}

inline void CDC::Ellipse(const CRect& rRect)
{
	::Ellipse(m_hDC, rRect.left, rRect.top, rRect.right, rRect.bottom);
}

inline void CDC::Arc(const CRect& rRect, const CPoint& ptStart, const CPoint& ptEnd)
{
	::Arc(m_hDC, rRect.left, rRect.top, rRect.right, rRect.bottom,
			ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}

inline void CDC::Fill(const CRect& rRect, const CBrush& rBrush)
{
	::FillRect(m_hDC, (LPRECT) &rRect, rBrush.Handle());
}

inline int CDC::BkMode(int iMode)
{
	return ::SetBkMode(m_hDC, iMode);
}

inline COLORREF CDC::TextColour(COLORREF crColour)
{
	return ::SetTextColor(m_hDC, crColour);
}

inline COLORREF CDC::BkColour(COLORREF crColour)
{
	return ::SetBkColor(m_hDC, crColour);
}

inline void CDC::TextOut(int iX, int iY, const char* pszText)
{
	::TextOut(m_hDC, iX, iY, (LPCSTR)pszText, lstrlen((LPCSTR)pszText));
}

inline void CDC::TextOut(const CPoint& rptOrigin, const char* pszText)
{
	::TextOut(m_hDC, rptOrigin.x, rptOrigin.y, (LPCSTR)pszText, lstrlen((LPCSTR)pszText));
}

inline void CDC::DrawText(const CRect& rcRect, const char* pszText, int nFormat)
{
	::DrawText(m_hDC, pszText, -1, const_cast<CRect*>(&rcRect), nFormat);
}

inline void CDC::PatBlt(const CRect& rcDst, DWORD dwRop)
{
	::PatBlt(m_hDC, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), dwRop);
}

#endif //DC_HPP
