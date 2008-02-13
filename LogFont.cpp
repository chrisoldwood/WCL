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

/******************************************************************************
**
** Constants
**
*******************************************************************************
*/

const size_t MAX_FACE_LEN = 32;

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
	// Initialise base structure to defaults.
	lfHeight         = 0;
	lfWidth          = 0;
	lfEscapement     = 0;
	lfOrientation    = 0;
	lfWeight         = FW_DONTCARE;
	lfItalic         = FALSE;
	lfUnderline      = FALSE;
	lfStrikeOut      = FALSE;
	lfCharSet        = DEFAULT_CHARSET;
	lfOutPrecision   = OUT_DEFAULT_PRECIS;
	lfClipPrecision  = CLIP_DEFAULT_PRECIS;
	lfQuality        = DEFAULT_QUALITY;
	lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	lfFaceName[0]    = TXT('\0');
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
	cf.lpfnHook       = NULL;
	cf.lpTemplateName = NULL;
	cf.hInstance      = NULL;
	cf.lpszStyle      = NULL;
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
		strFont += CString::Fmt(TXT("%s,%d"), lfFaceName, lfHeight);
	}

	// Includes Weight, Italic, Underline & Strikeout?
	if (nFields >= FMT_SHORT)
	{
		strFont += CString::Fmt(TXT(",%u,%u,%u,%u"), lfWeight, lfItalic, lfUnderline, lfStrikeOut);
	}

	// Includes all fields?
	if (nFields >= FMT_FULL)
	{
		strFont += CString::Fmt(TXT(",%d,%d,%d,%u,%u,%u,%u,%u"), lfWidth, lfEscapement, lfOrientation,
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
	ASSERT(pszFont != NULL);

	try
	{
		CStrArray astrFields;

		// Split the font defintions into separate fields.
		uint nFields = CStrTok::Split(pszFont, TXT(","), astrFields);

		ASSERT((nFields == FMT_MINIMAL) || (nFields == FMT_SHORT) || (nFields == FMT_FULL));

		// Always contains FaceName & Height.
		if (nFields >= FMT_MINIMAL)
		{
			memset(oLogFont.lfFaceName, 0, MAX_FACE_LEN);
			tstrncpy(oLogFont.lfFaceName, astrFields[0], MAX_FACE_LEN-1);
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
		TRACE1(TXT("CLogFont::Parse() failed - %s"), e.ErrorText());
		return false;
	}

	return true;
}
