/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLIPBOARD.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CClipboard class definition.
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

CClipboard::CClipboard()
	: m_pBuffer(NULL)
	, m_pStream(NULL)
	, m_iFormat(0)
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

CClipboard::~CClipboard()
{
	Close();
}

/******************************************************************************
** Method:		Open()
**
** Description:	.
**
** Parameters:	nMode	The access mode.
**
** Returns:		Nothing.
**
** Exceptions:	CMemStreamException on error.
**
*******************************************************************************
*/

void CClipboard::Open(uint nMode, uint iFormat)
{
	ASSERT((nMode == GENERIC_READ) || (nMode == GENERIC_WRITE));

	// Check we can open the clipboard.
	if (::OpenClipboard(NULL) == FALSE)
		throw CMemStreamException(CStreamException::E_OPEN_FAILED);

	// Pasting from clipboard?
	if (nMode == GENERIC_READ)
	{
		// Get current clipboard data stream.
		HGLOBAL hMem = ::GetClipboardData(iFormat);
		if (hMem == NULL)
			throw CMemStreamException(CStreamException::E_OPEN_FAILED);

		// Attach the data to the internal memory stream.
		m_pBuffer = new CBuffer(hMem);
		m_pStream = new CMemStream(*m_pBuffer);

		m_pStream->Open();
	}
	// Copying to clipboard?
	else if (nMode == GENERIC_WRITE)
	{
		// Empty current contents.
		if (::EmptyClipboard() == FALSE)
			throw CMemStreamException(CStreamException::E_CREATE_FAILED);

		// Create the internal memory stream.
		m_pBuffer = new CBuffer();
		m_pStream = new CMemStream(*m_pBuffer);

		m_pStream->Create();
	}

	// Save settings for later.
	m_nMode   = nMode;
	m_iFormat = iFormat;
}

/******************************************************************************
** Method:		Close()
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
** Exceptions:	CMemStreamException on error.
**
*******************************************************************************
*/

void CClipboard::Close()
{
	// Stream created?
	if ( (m_pBuffer != NULL) && (m_pStream != NULL) )
	{
		// Close the memory stream.
		m_pStream->Close();

		// Need to write data to the clipboard?
		if (m_nMode == GENERIC_WRITE)
		{
			HGLOBAL hMem = m_pBuffer->ToGlobal();

			if (::SetClipboardData(m_iFormat, hMem) != hMem)
			{
				::CloseClipboard();
				throw CMemStreamException(CStreamException::E_CREATE_FAILED);
			}
		}
	}

	// Close the clipboard.
	::CloseClipboard();

	// Delete memory stream and buffer.
	delete m_pBuffer;
	delete m_pStream;

	// Reset members.
	m_pBuffer = NULL;
	m_pStream = NULL;
	m_nMode   = NULL;
	m_iFormat = 0;
}

/******************************************************************************
** Method:		CopyText()
**
** Description:	Helper method for copying text to the clipboard.
**
** Parameters:	hOwner		The clipboard owner.
**				pszText		The text to copy.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CClipboard::CopyText(HWND hOwner, const char* pszText)
{
	ASSERT(::IsWindow(hOwner));
	ASSERT(pszText != NULL);

	bool bCopied = false;

	// Open the clipboard.
	if (::OpenClipboard(hOwner))
	{
		// Clear existing contents.
		if (::EmptyClipboard())
		{
			int     nLen  = strlen(pszText);
			HGLOBAL hData = ::GlobalAlloc(GMEM_MOVEABLE, nLen+1);

			// Allocated block?
			if (hData != NULL)
			{
				char* pszData = (char*) ::GlobalLock(hData);

				// Locked block?
				if (pszData != NULL)
				{
					// Copy string to clipboard buffer.
					strcpy(pszData, pszText);

					::GlobalUnlock(hData);

					// Copy to clipbaord.
					if (::SetClipboardData(CF_TEXT, hData) != NULL)
						bCopied = true;
				}
			}
		}

		// Close it.
		::CloseClipboard();
	}

	return bCopied;
}

/******************************************************************************
** Method:		IsEmpty()
**
** Description:	Queries if the clipboard is empty.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CClipboard::IsEmpty()
{
	return (::CountClipboardFormats() == 0);
}

/******************************************************************************
** Method:		IsFormatAvail()
**
** Description:	Queries if the clipboard has data in the given format.
**
** Parameters:	nFormat		The format to query for.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CClipboard::IsFormatAvail(uint nFormat)
{
	return (::IsClipboardFormatAvailable(nFormat) != 0);
}

/******************************************************************************
** Method:		PasteText()
**
** Description:	Helper method for pasting text from the clipboard.
**
** Parameters:	strString	The return buffer.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CClipboard::PasteText(CString& strString)
{
	bool bPasted = false;

	// Open the clipboard.
	if (::OpenClipboard(NULL))
	{
		HGLOBAL hData = ::GetClipboardData(CF_TEXT);

		// Got data?
		if (hData != NULL)
		{
			const char* psz = (const char*) ::GlobalLock(hData);

			// Locked block?
			if (psz != NULL)
			{ 
				// Copy string to return buffer.
				strString = psz;
			
				::GlobalUnlock(hData); 

				bPasted = true;
			} 
		}

		// Close it.
		::CloseClipboard();
	}

	return bPasted;
}

/******************************************************************************
** Method:		RegisterFormat()
**
** Description:	Register the custom clipboard format.
**
** Parameters:	pszFormat		The format name.
**
** Returns:		A handle for the format.
**
*******************************************************************************
*/

uint CClipboard::RegisterFormat(const char* pszFormat)
{
	return ::RegisterClipboardFormat(pszFormat);
}

/******************************************************************************
** Method:		FormatName()
**
** Description:	Gets the name of a clipboard format from its handle.
**				NB: This handles both custom and re-defined formats.
**
** Parameters:	nFormat		The format handle.
**
** Returns:		The format name.
**
*******************************************************************************
*/

CString CClipboard::FormatName(uint nFormat)
{
	// Is predefined format?
	if (nFormat < 0xC000)	
	{
		switch (nFormat)
		{
			case CF_TEXT:			return "CF_TEXT";
			case CF_BITMAP:			return "CF_BITMAP";
			case CF_METAFILEPICT:	return "CF_METAFILEPICT";
			case CF_SYLK:			return "CF_SYLK";
			case CF_DIF:			return "CF_DIF";
			case CF_TIFF:			return "CF_TIFF";
			case CF_OEMTEXT:		return "CF_OEMTEXT";
			case CF_DIB:			return "CF_DIB";
			case CF_PALETTE:		return "CF_PALETTE";
			case CF_PENDATA:		return "CF_PENDATA";
			case CF_RIFF:			return "CF_RIFF";
			case CF_WAVE:			return "CF_WAVE";
			case CF_UNICODETEXT:	return "CF_UNICODETEXT";
			case CF_ENHMETAFILE:	return "CF_ENHMETAFILE";
			case CF_HDROP:			return "CF_HDROP";
			case CF_LOCALE:			return "CF_LOCALE";
			default:				return "";
		}
	}
	// Is custom format.
	else
	{
		char szName[MAX_PATH+1] = "\0";

		// Is custom format
		::GetClipboardFormatName(nFormat, szName, sizeof(szName));

		return szName;
	}
}
