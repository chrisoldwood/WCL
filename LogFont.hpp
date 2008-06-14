/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LOGFONT.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CLogFont class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef LOGFONT_HPP
#define LOGFONT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

// Forward declarations
class CWnd;

/******************************************************************************
** 
** A thin wrapper around the LOGFONT structure.
**
*******************************************************************************
*/

class CLogFont : public LOGFONT
{
public:
	//
	// Constructors/Destructor.
	//
	CLogFont();
	CLogFont(HFONT hFont);
	~CLogFont();

	//! Construction from a face name and height in pixels.
	CLogFont(const tchar* pszFace, long nHeight);
	
	//
	// Methods.
	//
	bool Select(const CWnd& rParent);

	//
	// Serialisation formats.
	//
	enum FontFormat
	{
		FMT_MINIMAL	= 2,	// Facename + Height.
		FMT_SHORT	= 6,	// + Weight + Italic + Underline + Strikeout
		FMT_FULL	= 14	// All fields.
	};

	CString Format(FontFormat eFormat) const;
	static bool Parse(const tchar* pszFont, CLogFont& oLogFont);

protected:
	//
	// Internal methods.
	//

	//! Common construction.
	void Initialise();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //LOGFONT_HPP
