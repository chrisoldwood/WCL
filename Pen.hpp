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

class CPen /*: private NotCopyable*/
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

	CORE_NOT_COPYABLE(CPen);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HPEN CPen::Handle() const
{
	return m_hPen;
}

#endif //PEN_HPP
