/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BUFFER.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CBuffer class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Buffer.hpp"
#include "IInputStream.hpp"
#include "IOutputStream.hpp"
#include <Core/AnsiWide.hpp>

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

CBuffer::CBuffer()
	: m_nSize(0)
	, m_pBuffer(NULL)
{
}

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

CBuffer::CBuffer(size_t nSize)
	: m_nSize(nSize)
	, m_pBuffer(malloc(nSize))
{
}

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

CBuffer::CBuffer(const void* pData, size_t nSize)
	: m_nSize(nSize)
	, m_pBuffer(malloc(nSize))
{
	Set(pData, nSize);
}

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

CBuffer::CBuffer(HGLOBAL hGlobal)
{
	ASSERT(hGlobal != NULL);

	// Allocate buffer.
	m_nSize   = ::GlobalSize(hGlobal);
	m_pBuffer = malloc(m_nSize);

	// Get pointer to memory buffer.
	void* pGlobal = ::GlobalLock(hGlobal);

	ASSERT( (m_pBuffer != NULL) && (pGlobal != NULL) );

	// Copy from global buffer.
	Set(pGlobal, m_nSize);

	// Cleanup.
	::GlobalUnlock(hGlobal);
}

/******************************************************************************
** Method:		Copy constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CBuffer::CBuffer(const CBuffer& oRHS)
	: m_nSize(oRHS.m_nSize)
	, m_pBuffer(malloc(m_nSize))
{
	Set(oRHS.m_pBuffer, oRHS.m_nSize);
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

CBuffer::~CBuffer()
{
	if (m_pBuffer != NULL)
		free(m_pBuffer);
}

/******************************************************************************
** Method:		Size()
**
** Description:	Set the size of the buffer.
**
** Parameters:	nSize	The new size in bytes.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBuffer::Size(size_t nSize)
{
	if (m_nSize != nSize)
	{
		m_nSize   = nSize;
		m_pBuffer = realloc(m_pBuffer, m_nSize);
	}
}

/******************************************************************************
** Method:		Get()
**
** Description:	Gets a number of bytes from the buffer.
**
** Parameters:	pData	The return buffer for the data.
**				nSize	The number of bytes to fetch.
**				nOffset	The offset into the source buffer.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBuffer::Get(void* pData, size_t nSize, size_t nOffset) const
{
	if (nSize == 0)
		return;

	ASSERT(m_pBuffer     != NULL);
	ASSERT(nOffset       <  m_nSize);
	ASSERT(nOffset+nSize <= m_nSize);

	const byte* pBuffer = static_cast<const byte*>(m_pBuffer);

	memcpy(pData, pBuffer+nOffset, nSize);
}

/******************************************************************************
** Method:		Set()
**
** Description:	Sets a number of bytes in the buffer.
**
** Parameters:	pData	The source buffer for the data.
**				nSize	The number of bytes to copy.
**				nOffset	The offset into the destination buffer.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBuffer::Set(const void* pData, size_t nSize, size_t nOffset)
{
	if (nSize == 0)
		return;

	ASSERT(m_pBuffer     != NULL);
	ASSERT(nOffset       <  m_nSize);
	ASSERT(nOffset+nSize <= m_nSize);

	byte* pBuffer = static_cast<byte*>(m_pBuffer);

	memcpy(pBuffer+nOffset, pData, nSize);
}

/******************************************************************************
** Method:		Assignment operator.
**
** Description:	Copy the other buffer.
**
** Parameters:	oRHS	The other buffer.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBuffer::operator=(const CBuffer& oRHS)
{
	ASSERT(this != &oRHS);

	Size(oRHS.m_nSize);
	Set(oRHS.m_pBuffer, oRHS.m_nSize);
}

/******************************************************************************
** Method:		Equivalence operator.
**
** Description:	Compares two buffers.
**
** Parameters:	oRHS	The other buffer.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CBuffer::operator==(const CBuffer& oRHS) const
{
	// Sizes differ?
	if (m_nSize != oRHS.m_nSize)
		return false;

	// Both empty?
	if (m_nSize == 0)
		return true;

	// Do bytewise compare.
	return (memcmp(m_pBuffer, oRHS.m_pBuffer, m_nSize) == 0);
}

/******************************************************************************
** Method:		ToGlobal()
**
** Description:	Creates a global memory object from the buffer.
**
** Parameters:	None.
**
** Returns:		The memory handle.
**
*******************************************************************************
*/

HGLOBAL CBuffer::ToGlobal() const
{
	// Allocate the handle and get access.
	HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT, m_nSize);
	void*   pGlobal = ::GlobalLock(hGlobal);

	ASSERT(pGlobal != NULL);

	// Copy to global buffer.
	Get(pGlobal, m_nSize);

	// Cleanup.
	::GlobalUnlock(hGlobal);

	return hGlobal;
}

////////////////////////////////////////////////////////////////////////////////
//! Convert the entire buffer to a string.

CString CBuffer::ToString(TextFormat eFormat) const
{
	if (m_pBuffer != NULL)
	{
		// Treat buffer as containing ANSI chars?
		if (eFormat == ANSI_TEXT)
		{
			size_t      nChars  = m_nSize;
			const char* pBuffer = static_cast<const char*>(m_pBuffer);

#ifdef ANSI_BUILD
			return CString(pBuffer, nChars);
#else
			return CString(Core::AnsiToWide(pBuffer, pBuffer+nChars).c_str());
#endif
		}
		else //(eFormat == UNICODE_TEXT)
		{
			ASSERT((m_nSize % 2) == 0);

			size_t         nChars  = m_nSize / 2;
			const wchar_t* pBuffer = static_cast<const wchar_t*>(m_pBuffer);

#ifdef ANSI_BUILD
			return CString(Core::WideToAnsi(pBuffer, pBuffer+nChars).c_str());
#else
			return CString(pBuffer, nChars);
#endif
		}
	}

	return TXT("");
}

////////////////////////////////////////////////////////////////////////////////
//! Fill the buffer with the contents of a string.

void CBuffer::FromString(const CString& str, TextFormat eFormat, bool bIncNull)
{
	size_t nChars = str.Length();

	// Allow for '\0'?
	if (bIncNull)
		++nChars;

	if (eFormat == ANSI_TEXT)
	{
		size_t nBytes = Core::NumBytes<char>(nChars);

		Size(nBytes);

#ifdef ANSI_BUILD
		Set(str.Buffer(), nBytes);
#else
		Set(T2A(str.c_str()), nBytes);
#endif
	}
	else // (eFormat == UNICODE_TEXT)
	{
		size_t nBytes = Core::NumBytes<wchar_t>(nChars);

		Size(nBytes);

#ifdef ANSI_BUILD
		Set(T2A(str.c_str()), nBytes);
#else
		Set(str.Buffer(), nBytes);
#endif
	}

}

/******************************************************************************
** Methods:		operator>>()
**				operator<<()
**
** Description:	Methods to read/write to/from a stream.
**
** Parameters:	rStream		The stream to read/write to/from.
**				rBuffer		The buffer to read/write to/from.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void operator >>(WCL::IInputStream& rStream, CBuffer& rBuffer)
{
	uint32 nSize;

	rStream.Read(&nSize, sizeof(uint32));

	rBuffer.Size(nSize);

	rStream.Read(rBuffer.Buffer(), nSize);
}

void operator <<(WCL::IOutputStream& rStream, const CBuffer& rBuffer)
{
	uint32 nSize = static_cast<uint32>(rBuffer.Size());

	rStream.Write(&nSize, sizeof(uint32));
	rStream.Write(rBuffer.Buffer(), nSize);
}
