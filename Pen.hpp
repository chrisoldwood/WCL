/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PEN.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPen class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PEN_HPP
#define PEN_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This class wraps a standard GDI pen.
**
*******************************************************************************
*/

class CPen
{
public:
	//
	// Constructors/Destructor.
	//
	CPen();
	CPen(int iID);
	CPen(int iStyle, int iWidth, COLORREF crClr);
	~CPen();
	
	void Create(int iID);
	void Create(int iStyle, int iWidth, COLORREF crClr);

	//
	// Member access.
	//
	HPEN Handle() const;

protected:
	//
	// Members.
	//
	HPEN	m_hPen;
	bool	m_bOwner;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CPen::CPen(int iID)
{
	Create(iID);
}

inline CPen::CPen(int iStyle, int iWidth, COLORREF crClr)
{
	Create(iStyle, iWidth, crClr);
}

inline void CPen::Create(int iID)
{
	m_hPen   = GetStockPen(iID);
	m_bOwner = false;

	ASSERT(m_hPen != NULL);
}

inline void CPen::Create(int iStyle, int iWidth, COLORREF crClr)
{
	m_hPen   = ::CreatePen(iStyle, iWidth, crClr);
	m_bOwner = true;

	ASSERT(m_hPen != NULL);
}

inline HPEN CPen::Handle() const
{
	return m_hPen;
}

#endif //PEN_HPP
