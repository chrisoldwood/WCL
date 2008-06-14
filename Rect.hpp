/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		RECT.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CRect class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef RECT_HPP
#define RECT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Point.hpp"
#include "Size.hpp"

/******************************************************************************
** 
** This is a class based version of the standard Windows RECT structure.
**
*******************************************************************************
*/

class CRect : public tagRECT
{
public:
	//
	// Constructors/Destructor.
	//
	CRect();
	CRect(int iLeft, int iTop, int iRight, int iBottom);
	CRect(const CPoint& TopLeft, const CPoint& BottomRight);
	CRect(const CPoint& TopLeft, const CSize& Size);
	CRect(LPCRECT lprcRect);
	CRect(const RECT& rcRect);
	
	//
	// Member access.
	//
	CPoint TopLeft() const;
	CPoint BottomRight() const;
	CPoint BottomLeft() const;
	CPoint TopRight() const;
	CPoint Centre() const;

	//
	// Sizing & Position methods.
	//
	void Set(int iLeft, int iTop, int iRight, int iBottom);
	void Inflate(int iSize);
	void Offset(int iX, int iY);
	void Size(int nWidth, int nHeight);
	void Size(const CSize& Size);

	//
	// Attributes.
	//
	bool  Empty() const;
	int   Width() const;
	int   Height() const;
	CSize Size() const;
};


/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CRect::CRect()
{
	Set(0, 0, 0, 0);
}

inline CRect::CRect(int iLeft, int iTop, int iRight, int iBottom)
{
	Set(iLeft, iTop, iRight, iBottom);
}

inline CRect::CRect(const CPoint& TopLeft, const CPoint& BottomRight)
{
	Set(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y);
}

inline CRect::CRect(const CPoint& TopLeft, const CSize& Size)
{
	Set(TopLeft.x, TopLeft.y, TopLeft.x + Size.cx, TopLeft.y + Size.cy);
}

inline CRect::CRect(LPCRECT lprcRect)
{
	Set(lprcRect->left, lprcRect->top, lprcRect->right, lprcRect->bottom);
}

inline CRect::CRect(const RECT& rcRect)
{
	Set(rcRect.left, rcRect.top, rcRect.right, rcRect.bottom);
}

inline CPoint CRect::TopLeft() const
{
	return CPoint(left, top);
}

inline CPoint CRect::BottomRight() const
{
	return CPoint(right, bottom);
}

inline CPoint CRect::BottomLeft() const
{
	return CPoint(left, bottom);
}

inline CPoint CRect::TopRight() const
{
	return CPoint(right, top);
}

inline CPoint CRect::Centre() const
{
	return CPoint(left + (Width() / 2), top + (Height() / 2));
}

inline void CRect::Set(int iLeft, int iTop, int iRight, int iBottom)
{
	left   = iLeft;
	top    = iTop;
	right  = iRight;
	bottom = iBottom;
}

inline void CRect::Inflate(int iSize)
{
	left   -= iSize;
	top    -= iSize;
	right  += iSize;
	bottom += iSize;
}

inline void CRect::Offset(int iX, int iY)
{
	left   += iX;
	top    += iY;
	right  += iX;
	bottom += iY;
}

inline void CRect::Size(int nWidth, int nHeight)
{
	right  = left + nWidth;
	bottom = top  + nHeight;
}

inline void CRect::Size(const CSize& dmSize)
{
	Size(dmSize.cx, dmSize.cy);
}

inline bool CRect::Empty() const
{
	return IsRectEmpty(this);
}

inline int CRect::Width() const
{
	return (right - left);
}

inline int CRect::Height() const
{
	return (bottom - top);
}

inline CSize CRect::Size() const
{
	return CSize(Width(), Height());
}

////////////////////////////////////////////////////////////////////////////////
//! Global equals operator for a pair of rectangles.

inline bool operator==(const CRect& LHS, const CRect& RHS)
{
	return (   (LHS.left   == RHS.left)
			&& (LHS.top    == RHS.top)
			&& (LHS.right  == RHS.right)
			&& (LHS.bottom == RHS.bottom) );
}

////////////////////////////////////////////////////////////////////////////////
//! Global not equals operator for a pair of rectangles.

inline bool operator!=(const CRect& LHS, const CRect& RHS)
{
	return !operator==(LHS, RHS);
}

#endif //RECT_HPP
