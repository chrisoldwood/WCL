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
** Parameters:	eMode	The access mode.
**
** Returns:		Nothing.
**
** Exceptions:	CMemStreamException on error.
**
*******************************************************************************
*/

void CClipboard::Open(Mode eMode, uint iFormat)
{
	ASSERT( (eMode == ReadOnly) || (eMode == WriteOnly) );

	// Check we can open the clipboard.
	if (::OpenClipboard(NULL) == FALSE)
		throw CMemStreamException(CStreamException::E_OPEN_FAILED);

	// Pasting from clipboard?
	if (eMode == ReadOnly)
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
	else if (eMode == WriteOnly)
	{
		// Empty current contents.
		if (::EmptyClipboard() == FALSE)
			throw CMemStreamException(CStreamException::E_CREATE_FAILED);

		// Create the internal memory stream.
		m_MemStream.Create();
	}

	// Save settings for later.
	m_eMode   = eMode;
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
	if (m_eMode == WriteOnly)
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
	m_eMode   = None;
	m_iFormat = 0;
}
