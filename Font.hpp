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
	~CFont();

	void Create(int iID);
	void Create(const CLogFont& rLogFont);
	void Create(HFONT hFont, bool bOwn = false);

	//
	// Member access.
	//
	HFONT Handle() const;

protected:
	//
	// Members.
	//
	HFONT	m_hFont;
	bool	m_bOwner;
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

inline CFont::CFont(int iID)
{
	Create(iID);
}

inline CFont::CFont(const CLogFont& rLogFont)
{
	Create(rLogFont);
}

inline CFont::CFont(HFONT hFont, bool bOwn)
{
	Create(hFont, bOwn);
}

inline void CFont::Create(int iID)
{
	m_hFont  = GetStockFont(iID);
	m_bOwner = false;

	ASSERT(m_hFont != NULL);
}

inline void CFont::Create(const CLogFont& rLogFont)
{
	m_hFont  = ::CreateFontIndirect(&rLogFont);
	m_bOwner = true;

	ASSERT(m_hFont != NULL);
}

inline void CFont::Create(HFONT hFont, bool bOwn)
{
	m_hFont  = hFont;
	m_bOwner = bOwn;

	ASSERT(m_hFont != NULL);
}

#endif //FONT_HPP
