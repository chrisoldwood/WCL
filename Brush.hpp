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

/******************************************************************************
** 
** This class wraps a standard GDI brush.
**
*******************************************************************************
*/

class CBrush
{
public:
	//
	// Constructors/Destructor.
	//
	CBrush();
	CBrush(int iID);
	CBrush(COLORREF crClr);
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
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CBrush::CBrush(int iID)
{
	Create(iID);
}

inline CBrush::CBrush(COLORREF crClr)
{
	Create(crClr);
}

inline void CBrush::Create(int iID)
{
	m_hBrush = GetStockBrush(iID);
	m_bOwner = false;

	ASSERT(m_hBrush != NULL);
}

inline void CBrush::Create(COLORREF crClr)
{
	m_hBrush = ::CreateSolidBrush(crClr);
	m_bOwner = true;

	ASSERT(m_hBrush != NULL);
}

inline HBRUSH CBrush::Handle() const
{
	return m_hBrush;
}

#endif //BRUSH_HPP
