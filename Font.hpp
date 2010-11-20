/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FONT.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CFont class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FONT_HPP
#define FONT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "LogFont.hpp"

/******************************************************************************
**
** This class wraps a standard GDI font.
**
*******************************************************************************
*/

class CFont
{
public:
	//
	// Constructors/Destructor.
	//
	CFont();
	CFont(int iID);
	CFont(const CLogFont& rLogFont);
	CFont(HFONT hFont, bool bOwn = false);
	CFont(const CFont& rhs);
	~CFont();

	CFont& operator=(const CFont& rhs);

	//
	// Properties.
	//
	HFONT Handle() const;

	//
	// Methods.
	//
	bool Create(int iID);
	bool Create(const CLogFont& rLogFont);
	void Create(HFONT hFont, bool bOwn = false);

	bool Select(const CWnd& rParent);

	CString Format(CLogFont::FontFormat eFormat) const;
	static bool Parse(const tchar* pszFont, CFont& oFont);

protected:
	//
	// Members.
	//
	HFONT	m_hFont;
	bool	m_bOwner;

	//
	// Internal methods.
	//
	void Release();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HFONT CFont::Handle() const
{
	return m_hFont;
}

#endif //FONT_HPP
