/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FONT.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CFont class definition.
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

CFont::CFont()
	: m_hFont(NULL)
	, m_bOwner(false)
{
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

CFont::~CFont()
{
	// Delete if valid and we own it.
	if ( (m_hFont) && (m_bOwner) )
		::DeleteObject(m_hFont);
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

bool CFont::Select(const CWnd& rParent)
{
	CHOOSEFONT cf = { 0 };
	CLogFont   lf;

	// Initialise structure.
	cf.lStructSize    = sizeof(cf);
	cf.hwndOwner      = rParent.Handle();
	cf.hDC            = NULL;
	cf.lpLogFont      = &lf;
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
	if (ChooseFont(&cf) == 0)
		return false;

	// Delete previously held font.
	if ( (m_hFont != NULL) && (m_bOwner) )
		::DeleteObject(m_hFont);

	// Create new font from LOGFONT structure.
	m_hFont  = ::CreateFontIndirect(&lf);
	m_bOwner = true;

	ASSERT(m_hFont != NULL);

	return true;
}
