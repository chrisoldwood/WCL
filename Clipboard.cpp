/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLIPBOARD.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CClipboard class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Clipboard.hpp"
#include "MemStreamException.hpp"
#include "Buffer.hpp"

/******************************************************************************
**
** Class members.
**
*******************************************************************************
*/

CClipboard::FmtEntry CClipboard::s_oStdFormats[] =
{
	{ CF_TEXT,			TXT("CF_TEXT")         },
	{ CF_BITMAP,		TXT("CF_BITMAP")       },
	{ CF_METAFILEPICT,	TXT("CF_METAFILEPICT") },
	{ CF_SYLK,			TXT("CF_SYLK")         },
	{ CF_DIF,			TXT("CF_DIF")          },
	{ CF_TIFF,			TXT("CF_TIFF")         },
	{ CF_OEMTEXT,		TXT("CF_OEMTEXT")      },
	{ CF_DIB,			TXT("CF_DIB")          },
	{ CF_PALETTE,		TXT("CF_PALETTE")      },
	{ CF_PENDATA,		TXT("CF_PENDATA")      },
	{ CF_RIFF,			TXT("CF_RIFF")         },
	{ CF_WAVE,			TXT("CF_WAVE")         },
	{ CF_UNICODETEXT,	TXT("CF_UNICODETEXT")  },
	{ CF_ENHMETAFILE,	TXT("CF_ENHMETAFILE")  },
	{ CF_HDROP,			TXT("CF_HDROP")        },
	{ CF_LOCALE,		TXT("CF_LOCALE")       },
	{ CF_DIBV5,			TXT("CF_DIBV5")        },
	{ 0,				NULL                   }
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

CClipboard::CClipboard()
	: m_iFormat(0)
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
		m_pBuffer = BufferPtr(new CBuffer(hMem));
		m_pStream = MemStreamPtr(new CMemStream(*m_pBuffer));

		m_pStream->Open();
	}
	// Copying to clipboard?
	else if (nMode == GENERIC_WRITE)
	{
		// Empty current contents.
		if (::EmptyClipboard() == FALSE)
			throw CMemStreamException(CStreamException::E_CREATE_FAILED);

		// Create the internal memory stream.
		m_pBuffer = BufferPtr(new CBuffer());
		m_pStream = MemStreamPtr(new CMemStream(*m_pBuffer));

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
	if ( (m_pBuffer.get() != nullptr) && (m_pStream.get() != nullptr) )
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
	m_pBuffer.reset();
	m_pStream.reset();

	// Reset members.
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

bool CClipboard::CopyText(HWND hOwner, const tchar* pszText)
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
			size_t  nChars = tstrlen(pszText);
			HGLOBAL hData = ::GlobalAlloc(GMEM_MOVEABLE, Core::numBytes<tchar>(nChars+1));

			// Allocated block?
			if (hData != NULL)
			{
				tchar* pszData = static_cast<tchar*>(::GlobalLock(hData));

				// Locked block?
				if (pszData != NULL)
				{
					// Copy string to clipboard buffer.
					tstrcpy(pszData, pszText);

					::GlobalUnlock(hData);

					// Copy to clipbaord.
					if (::SetClipboardData(CF_TCHAR_TEXT, hData) != NULL)
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
		HGLOBAL hData = ::GetClipboardData(CF_TCHAR_TEXT);

		// Got data?
		if (hData != NULL)
		{
			const tchar* psz = static_cast<const tchar*>(::GlobalLock(hData));

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
** Method:		IsStdFormat()
**
** Description:	Queries if the format is a standard one.
**
** Parameters:	nFormat		The format handle.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CClipboard::IsStdFormat(uint nFormat)
{
	return (nFormat < 0xC000);
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

uint CClipboard::RegisterFormat(const tchar* pszFormat)
{
	return ::RegisterClipboardFormat(pszFormat);
}

/******************************************************************************
** Method:		FormatName()
**
** Description:	Gets the name of a clipboard format from its handle.
**				NB: This handles both custom and pre-defined formats.
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
	if (IsStdFormat(nFormat))
	{
		// Search lookup table.
		for (FmtEntry* pEntry = s_oStdFormats; (pEntry->m_nFormat != 0); ++pEntry)
		{
			if (nFormat == pEntry->m_nFormat)
				return pEntry->m_pszFormat;
		}

		ASSERT_FALSE();

		return TXT("CF_UNKNOWN");
	}
	// Is custom format.
	else
	{
		tchar szName[MAX_PATH+1] = TXT("\0");

		// Is custom format
		::GetClipboardFormatName(nFormat, szName, sizeof(szName));

		return szName;
	}
}

/******************************************************************************
** Method:		FormatHandle()
**
** Description:	Gets the handle of a standard clipboard format from its name.
**
** Parameters:	pszFormat	The format name.
**
** Returns:		The format handle or NULL.
**
*******************************************************************************
*/

uint CClipboard::FormatHandle(const tchar* pszFormat)
{
	ASSERT(pszFormat != NULL);

	// Search standard formats lookup table first.
	for (FmtEntry* pEntry = s_oStdFormats; (pEntry->m_nFormat != 0); ++pEntry)
	{
		if (tstricmp(pszFormat, pEntry->m_pszFormat) == 0)
			return pEntry->m_nFormat;
	}

	return NULL;
}
