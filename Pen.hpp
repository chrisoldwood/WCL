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
	CPen(int iStyle, int iWidth, COLORREF crClr);
	~CPen();
	
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
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CPen::CPen(int iStyle, int iWidth, COLORREF crClr)
{
	Create(iStyle, iWidth, crClr);
}

inline void CPen::Create(int iStyle, int iWidth, COLORREF crClr)
{
	m_hPen = ::CreatePen(iStyle, iWidth, crClr);
	ASSERT(m_hPen);
}

inline HPEN CPen::Handle() const
{
	return m_hPen;
}

#endif //PEN_HPP
