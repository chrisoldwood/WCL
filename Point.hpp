/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		POINT.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPoint class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef POINT_HPP
#define POINT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

// Forward declarations
class CRect;

/******************************************************************************
** 
** This is a class based version of the Windows standard POINT structure.
**
*******************************************************************************
*/

class CPoint : public tagPOINT
{
public:
	//
	// Constructors/Destructor.
	//
	CPoint();
	CPoint(const POINT& pt);
	CPoint(int iX, int iY);
	
	//
	// Methods.
	//
	void Set(int iX, int iY);
	bool IsIn(const CRect& rcRect) const;
};


/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CPoint::CPoint()
{
	Set(0, 0);
}

inline CPoint::CPoint(const POINT& pt)
{
	Set(pt.x, pt.y);
}

inline CPoint::CPoint(int iX, int iY)
{
	Set(iX, iY);
}

inline void CPoint::Set(int iX, int iY)
{
	x = iX;
	y = iY;
}

inline bool CPoint::IsIn(const CRect& rcRect) const
{
	return PtInRect((LPRECT)&rcRect, *this);
}

#endif //POINT_HPP
