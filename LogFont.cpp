/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LOGFONT.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CLogFont class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
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
	// Initialise base structure to defaults.
	lfHeight         = 0;
	lfWidth          = 0;
	lfEscapement     = 0;
	lfOrientation    = 0;
	lfWeight         = FW_DONTCARE;
	lfItalic         = FALSE;
	lfUnderline      = FALSE;
	lfStrikeOut      = FALSE;
	lfCharSet        = ANSI_CHARSET;
	lfOutPrecision   = OUT_DEFAULT_PRECIS;
	lfClipPrecision  = CLIP_DEFAULT_PRECIS;
	lfQuality        = DEFAULT_QUALITY;
	lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	lfFaceName[0]    = '\0';
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
