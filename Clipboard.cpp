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
		m_MemStream.AttachHandle(hMem);
		m_MemStream.Open();
	}
	// Copying to clipboard?
	else if (nMode == GENERIC_WRITE)
	{
		// Empty current contents.
		if (::EmptyClipboard() == FALSE)
			throw CMemStreamException(CStreamException::E_CREATE_FAILED);

		// Create the internal memory stream.
		m_MemStream.Create();
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
	// Close the memory stream.
	m_MemStream.Close();

	// Need to write data to the clipboard?
	if (m_nMode == GENERIC_WRITE)
	{
		HGLOBAL hMem = m_MemStream.DetachHandle();

		if (::SetClipboardData(m_iFormat, hMem) != hMem)
		{
			::CloseClipboard();
			throw CMemStreamException(CStreamException::E_CREATE_FAILED);
		}
	}

	// Close the clipboard.
	::CloseClipboard();

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
