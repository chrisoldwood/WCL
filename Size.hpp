/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SIZE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CSize class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SIZE_HPP
#define SIZE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This is a class based version of the standard Windows SIZE structure.
**
*******************************************************************************
*/

class CSize : public tagSIZE
{
public:
	//
	// Constructors/Destructor.
	//
	CSize();
	CSize(int iWidth, int iHeight);
	
	void Set(int iWidth, int iHeight);

	//
	// Operators.
	//
	bool operator ==(const CSize& rRHS) const;
	bool operator !=(const CSize& rRHS) const;
};


/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CSize::CSize()
{
	Set(0, 0);
}

inline CSize::CSize(int iWidth, int iHeight)
{
	Set(iWidth, iHeight);
}

inline void CSize::Set(int iWidth, int iHeight)
{
	cx = iWidth;
	cy = iHeight;
}

inline bool CSize::operator ==(const CSize& rRHS) const
{
	return ( (cx == rRHS.cx) && (cy == rRHS.cy) );
}

inline bool CSize::operator !=(const CSize& rRHS) const
{
	return ( (cx != rRHS.cx) || (cy != rRHS.cy) );
}

#endif //SIZE_HPP
