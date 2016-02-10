/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FONT.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CFont class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Font.hpp"

/******************************************************************************
**
** The mapping of font name to stock font object ID.
**
*******************************************************************************
*/

struct FontMapEntry
{
	const tchar*	m_pszName;
	uint			m_nID;
};

static FontMapEntry g_aoFontMap[] = {
{ TXT("OEM_FIXED_FONT"),		10   },
{ TXT("ANSI_FIXED_FONT"),		11   },
{ TXT("ANSI_VAR_FONT"),			12   },
{ TXT("SYSTEM_FONT"),			13   },
{ TXT("DEVICE_DEFAULT_FONT"),	14   },
{ TXT("SYSTEM_FIXED_FONT"),		16   },
{ TXT("DEFAULT_GUI_FONT"),		17   },
{ NULL,							 0   },
};

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

CFont::CFont(int iID)
	: m_hFont()
	, m_bOwner()
{
	Create(iID);
}

CFont::CFont(const CLogFont& rLogFont)
	: m_hFont()
	, m_bOwner()
{
	Create(rLogFont);
}

CFont::CFont(HFONT hFont, bool bOwn)
	: m_hFont()
	, m_bOwner()
{
	Create(hFont, bOwn);
}

/******************************************************************************
** Method:		Copy constructor.
**
** Description:	Copy the source font. This ASSERTs if the source is the owner.
**
** Parameters:	rhs		The font to copy.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFont::CFont(const CFont& rhs)
	: m_hFont(rhs.m_hFont)
	, m_bOwner(false)
{
	ASSERT(rhs.m_bOwner == false);
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
	Release();
}

/******************************************************************************
** Method:		Assignment operator.
**
** Description:	Copy the source font. This ASSERTs if the source is the owner.
**
** Parameters:	rhs		The font to copy.
**
** Returns:		Self.
**
*******************************************************************************
*/

CFont& CFont::operator=(const CFont& rhs)
{
	// Ignore, if ourself.
	if (this != &rhs)
	{
		ASSERT(rhs.m_bOwner == false);

		// Free old resource first.
		Release();

		// Copy source.
		m_hFont  = rhs.m_hFont;
		m_bOwner = false;
	}

	return *this;
}

/******************************************************************************
** Method:		Create()
**
** Description:	Create a font from a stock font object.
**
** Parameters:	iID		The ID of the stock font.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFont::Create(int iID)
{
	Release();

	// Acquire font.
	m_hFont  = GetStockFont(iID);
	m_bOwner = false;

	return(m_hFont != NULL);
}

/******************************************************************************
** Method:		Create()
**
** Description:	Create the font from a LOGFONT structure.
**
** Parameters:	rLogFont	The LOGFONT definition.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFont::Create(const CLogFont& rLogFont)
{
	Release();

	// Create font.
	m_hFont  = ::CreateFontIndirect(&rLogFont);
	m_bOwner = true;

	return(m_hFont != NULL);
}

/******************************************************************************
** Method:		Create()
**
** Description:	Create the font by attaching a raw font handle.
**
** Parameters:	hFont	The font handle.
**				bOwn	Flag to determine ownership.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFont::Create(HFONT hFont, bool bOwn)
{
	ASSERT(hFont != NULL);

	Release();

	// Take ownership.
	m_hFont  = hFont;
	m_bOwner = bOwn;
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
	CLogFont oLogFont;

	// Show dialog.
	if (!oLogFont.Select(rParent))
		return false;

	// Create new font.
	Create(oLogFont);

	return true;
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

CString CFont::Format(CLogFont::FontFormat eFormat) const
{
	ASSERT(m_hFont != NULL);

	CLogFont oLogFont(m_hFont);

	return oLogFont.Format(eFormat);
}

/******************************************************************************
** Method:		Parse()
**
** Description:	Creates a font from the definition in the string. The string
**				can either be the name of one of the stock fonts (as defined
**				in <wingdi.h>) or a serialised CLogFont definition.
**
** Parameters:	pszFont		The font definition.
**				oFont		The returned font.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFont::Parse(const tchar* pszFont, CFont& oFont)
{
	ASSERT(pszFont != NULL);

	// Quick check for a LogFont definition.
	if (tstrchr(pszFont, TXT(',')) != NULL)
	{
		CLogFont oLogFont;

		// Parse font definition.
		if (!CLogFont::Parse(pszFont, oLogFont))
			return false;

		// Create it.
		if (!oFont.Create(oLogFont))
			return false;
	}
	// Stock font name.
	else
	{
		FontMapEntry* pEntry = g_aoFontMap;

		// Search the font mapping table...
		for (; pEntry->m_pszName != NULL; ++pEntry)
		{
			if (tstricmp(pEntry->m_pszName, pszFont) == 0)
				break;
		}

		// Invalid font name?
		if (pEntry->m_pszName == NULL)
			return false;

		// Create it.
		if (!oFont.Create(pEntry->m_nID))
			return false;
	}

	ASSERT(oFont.Handle() != NULL);

	return true;
}

/******************************************************************************
** Method:		Release()
**
** Description:	Releases the resources by destroying it, if we're the owner.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFont::Release()
{
	// Free resource, if the owner.
	if ( (m_hFont != NULL) && (m_bOwner) )
		::DeleteObject(m_hFont);

	// Reset state.
	m_hFont  = NULL;
	m_bOwner = false;
}
