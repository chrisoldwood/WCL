/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LOGFONT.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CLogFont class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "LogFont.hpp"
#include "Wnd.hpp"
#include "StrCvt.hpp"
#include "StrArray.hpp"
#include "StrTok.hpp"
#include "StrCvtException.hpp"

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) // GCC 4.2+
// missing initializer for member 'X'
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) // GCC 4.2+
// Caused by the DEBUG_USE_ONLY macro.
#pragma GCC diagnostic ignored "-Wunused-value"
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CLogFont::CLogFont()
{
	Initialise();
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	Extract details from an existing font.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CLogFont::CLogFont(HFONT hFont)
{
	ASSERT(hFont != NULL);

	::GetObject(hFont, sizeof(LOGFONT), this);
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a face name and height in pixels.

CLogFont::CLogFont(const tchar* pszFace, long nHeight)
{
	ASSERT(pszFace != nullptr);

	// Set defaults.
	Initialise();

	// Set face name and point size.
	lfHeight = nHeight;
	tstrncpy(lfFaceName, pszFace, LF_FACESIZE-1);
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CLogFont::~CLogFont()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Common construction.

void CLogFont::Initialise()
{
	memset(static_cast<LOGFONT*>(this), 0, sizeof(LOGFONT));

//	lfHeight         = 0;
//	lfWidth          = 0;
//	lfEscapement     = 0;
//	lfOrientation    = 0;
	lfWeight         = FW_DONTCARE;
	lfItalic         = FALSE;
	lfUnderline      = FALSE;
	lfStrikeOut      = FALSE;
	lfCharSet        = DEFAULT_CHARSET;
	lfOutPrecision   = OUT_DEFAULT_PRECIS;
	lfClipPrecision  = CLIP_DEFAULT_PRECIS;
	lfQuality        = DEFAULT_QUALITY;
	lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
//	lfFaceName[0]    = TXT('\0');
}

/******************************************************************************
** Method:		Select()
**
** Description:	Select a font for the screen using the common dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

bool CLogFont::Select(const CWnd& rParent)
{
	CHOOSEFONT cf = { 0 };

	// Initialise structure.
	cf.lStructSize    = sizeof(cf);
	cf.hwndOwner      = rParent.Handle();
	cf.hDC            = NULL;
	cf.lpLogFont      = this;
	cf.iPointSize     = 0;
	cf.Flags          = CF_FORCEFONTEXIST | CF_SCREENFONTS | CF_NOSCRIPTSEL;
	cf.rgbColors      = 0;
	cf.lCustData      = 0;
	cf.lpfnHook       = nullptr;
	cf.lpTemplateName = nullptr;
	cf.hInstance      = NULL;
	cf.lpszStyle      = nullptr;
	cf.nFontType      = 0;
	cf.nSizeMin       = 0;
	cf.nSizeMax       = 0;

	// Show dialog.
	return (ChooseFont(&cf) != 0);
}

/******************************************************************************
** Method:		Format()
**
** Description:	Serialises the font definition to a string.
**
** Parameters:	eFormat		The list of fields to serialise.
**
** Returns:		The font definition.
**
*******************************************************************************
*/

CString CLogFont::Format(FontFormat eFormat) const
{
	CString strFont;

	int nFields = eFormat;

	// Always contains FaceName & Height.
	if (nFields >= FMT_MINIMAL)
	{
		strFont += CString::Fmt(TXT("%s,%ld"), lfFaceName, lfHeight);
	}

	// Includes Weight, Italic, Underline & Strikeout?
	if (nFields >= FMT_SHORT)
	{
		strFont += CString::Fmt(TXT(",%lu,%u,%u,%u"), lfWeight, lfItalic, lfUnderline, lfStrikeOut);
	}

	// Includes all fields?
	if (nFields >= FMT_FULL)
	{
		strFont += CString::Fmt(TXT(",%ld,%ld,%ld,%u,%u,%u,%u,%u"), lfWidth, lfEscapement, lfOrientation,
								lfCharSet, lfOutPrecision, lfClipPrecision, lfQuality, lfPitchAndFamily);
	}

	return strFont;
}

/******************************************************************************
** Method:		Parse()
**
** Description:	Fills in a LOGFONT from the definition in the string.
**				The string definition can contain a variable number of fields
**				separated by a comma. This allows both simple and full font
**				parameters to be stored.
**
** Parameters:	pszFont		The font definition.
**				oLogFont	The returned structure.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CLogFont::Parse(const tchar* pszFont, CLogFont& oLogFont)
{
	ASSERT(pszFont != nullptr);

	try
	{
		CStrArray astrFields;

		// Split the font defintions into separate fields.
		size_t nFields = CStrTok::Split(pszFont, TXT(","), astrFields);

		ASSERT((nFields == FMT_MINIMAL) || (nFields == FMT_SHORT) || (nFields == FMT_FULL));

		// Always contains FaceName & Height.
		if (nFields >= FMT_MINIMAL)
		{
			memset(oLogFont.lfFaceName, 0, LF_FACESIZE);
			tstrncpy(oLogFont.lfFaceName, astrFields[0], LF_FACESIZE-1);
			oLogFont.lfHeight = CStrCvt::ParseInt(astrFields[1]);
		}

		// Includes Weight, Italic, Underline & Strikeout?
		if (nFields >= FMT_SHORT)
		{
			oLogFont.lfWeight    = CStrCvt::ParseUInt(astrFields[2]);
			oLogFont.lfItalic    = static_cast<BYTE>(CStrCvt::ParseUInt(astrFields[3]));
			oLogFont.lfUnderline = static_cast<BYTE>(CStrCvt::ParseUInt(astrFields[4]));
			oLogFont.lfStrikeOut = static_cast<BYTE>(CStrCvt::ParseUInt(astrFields[5]));
		}

		// Includes all fields?
		if (nFields >= FMT_FULL)
		{
			oLogFont.lfWidth          = CStrCvt::ParseInt(astrFields[6]);
			oLogFont.lfEscapement     = CStrCvt::ParseInt(astrFields[7]);
			oLogFont.lfOrientation    = CStrCvt::ParseInt(astrFields[8]);
			oLogFont.lfCharSet        = static_cast<BYTE>(CStrCvt::ParseUInt(astrFields[9]));
			oLogFont.lfOutPrecision   = static_cast<BYTE>(CStrCvt::ParseUInt(astrFields[10]));
			oLogFont.lfClipPrecision  = static_cast<BYTE>(CStrCvt::ParseUInt(astrFields[11]));
			oLogFont.lfQuality        = static_cast<BYTE>(CStrCvt::ParseUInt(astrFields[12]));
			oLogFont.lfPitchAndFamily = static_cast<BYTE>(CStrCvt::ParseUInt(astrFields[13]));
		}
	}
	catch (const CStrCvtException& e)
	{
		DEBUG_USE_ONLY(e);
		TRACE1(TXT("CLogFont::Parse() failed - %s"), e.twhat());
		return false;
	}

	return true;
}
