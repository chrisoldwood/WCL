/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BRUSH.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CBrush class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BRUSH_HPP
#define BRUSH_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
**
** This class wraps a standard GDI brush.
**
*******************************************************************************
*/

class CBrush /*: private NotCopyable*/
{
public:
	//
	// Constructors/Destructor.
	//
	CBrush();
	CBrush(int iID);
	CBrush(COLORREF crClr);
	CBrush(HBRUSH hBrush, bool bOwn = false);
	~CBrush();

	void Create(int iID);
	void Create(COLORREF crClr);

	//
	// Member access.
	//
	HBRUSH Handle() const;

protected:
	//
	// Members.
	//
	HBRUSH	m_hBrush;
	bool	m_bOwner;

private:
	// NotCopyable.
	CBrush(const CBrush&);
	CBrush& operator=(const CBrush&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HBRUSH CBrush::Handle() const
{
	return m_hBrush;
}

#endif //BRUSH_HPP
