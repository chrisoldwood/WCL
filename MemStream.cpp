/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTREAM.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMemStream class definition.
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

CMemStream::CMemStream()
	: m_hMem(NULL)
	, m_bOwner(false)
	, m_pBuffer(NULL)
	, m_lAllocSize(0)
	, m_lEOF(0)
	, m_lPos(0)
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

CMemStream::~CMemStream()
{
	FreeBlock();
}

/******************************************************************************
** Method:		FreeBlock().
**
** Description:	Free the current block.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMemStream::FreeBlock()
{
	// Valid block AND owner?
	if ( (m_hMem != NULL) && (m_bOwner) )
		::GlobalFree(m_hMem);

	// Reset members.
	m_hMem       = NULL;
	m_bOwner     = false;
	m_pBuffer    = NULL;
	m_lAllocSize = 0;
	m_lEOF       = 0;
	m_lPos       = 0;
}

/******************************************************************************
** Method:		AttachHandle()
**
** Description:	Give a handle to the stream to use. Also tell the stream to
**				take ownership or not.
**
** Parameters:	hMem	The memory handle.
**				bOwn	Flag to determine ownership.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMemStream::AttachHandle(HGLOBAL hMem, bool bOwn)
{
	ASSERT(hMem != NULL);

	// Free any exisiting block.
	FreeBlock();

	m_hMem   = hMem;
	m_bOwner = bOwn;

	// Get memory block size.
	m_lAllocSize = m_lEOF = ::GlobalSize(m_hMem);
}

/******************************************************************************
** Method:		DetachHandle()
**
** Description:	Take ownership of the memory block away from the stream.
**
** Parameters:	None.
**
** Returns:		The memory handle.
**
*******************************************************************************
*/

HGLOBAL CMemStream::DetachHandle()
{
	HGLOBAL hMem = m_hMem;

	// Reset members.
	m_hMem       = NULL;
	m_bOwner     = false;
	m_pBuffer    = NULL;
	m_lAllocSize = 0;
	m_lEOF       = 0;
	m_lPos       = 0;

	return hMem;
}

/******************************************************************************
** Method:		Create()
**
** Description:	Create a new stream for writing to.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
** Exceptions:	CMemStreamException on error.
**
*******************************************************************************
*/

void CMemStream::Create()
{
	// Free the existing block.
	FreeBlock();

	// Set inital block size.
	m_lAllocSize = ALLOC_SIZE;

	// Allocate an inital block.
	m_hMem = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT, m_lAllocSize);
	if (m_hMem == NULL)
		throw CMemStreamException(CMemStreamException::E_CREATE_FAILED);

	// Get pointer to buffer.
	m_pBuffer = (byte*) ::GlobalLock(m_hMem);
	ASSERT(m_pBuffer != NULL);

	// Set to SOF.
	m_lEOF = 0;
	m_lPos = 0;

	m_bOwner = true;
	m_eMode  = WriteOnly;
}

/******************************************************************************
** Method:		Open()
**
** Description:	Open the current memory block for reading.
**
** Parameters:	hMem	The memory block to open.
**
** Returns:		Nothing.
**
** Exceptions:	CMemStreamException on error.
**
*******************************************************************************
*/

void CMemStream::Open()
{
	ASSERT(m_hMem != NULL);

	// Valid handle?
	if (m_hMem == NULL)
		throw CMemStreamException(CMemStreamException::E_OPEN_FAILED);

	// Get pointer to buffer.
	m_pBuffer = (byte*) ::GlobalLock(m_hMem);
	ASSERT(m_pBuffer != NULL);

	// Set to SOF.
	m_lPos  = 0;
	m_eMode = ReadOnly;
}

/******************************************************************************
** Method:		Close()
**
** Description:	Close the file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMemStream::Close()
{
	// Stream open?
	if (m_pBuffer != NULL)
		::GlobalUnlock(m_hMem);

	// Writing?
	if (m_eMode == WriteOnly)
	{
		// Shrink block to EOF.
		m_hMem = ::GlobalReAlloc(m_hMem, m_lEOF, GMEM_ZEROINIT);
		
		// Realloc failed?
		if (m_hMem == NULL)
			throw CMemStreamException(CMemStreamException::E_WRITE_FAILED);
	}

	// Reset members.
	m_pBuffer = NULL;
	m_eMode   = None;
}

/******************************************************************************
** Method:		Read()
**
** Description:	Core method for reading a number of bytes from the stream.
**
** Parameters:	pBuffer		The buffer to read to.
**				iNumBytes	The number of bytes to read.
**
** Returns:		Nothing.
**
** Exceptions:	CMemStreamException on error.
**
*******************************************************************************
*/

void CMemStream::Read(void* pBuffer, uint iNumBytes)
{
	ASSERT(m_pBuffer != NULL);
	ASSERT( (m_eMode == ReadOnly) || (m_eMode == ReadWrite) );

	// Stream open?
	if (m_pBuffer == NULL)
		throw CMemStreamException(CMemStreamException::E_READ_FAILED);

	// Enough bytes left to read?
	if ((m_lPos + iNumBytes) > m_lEOF)
		throw CMemStreamException(CMemStreamException::E_READ_FAILED);

	// Read bytes into the input buffer.
	memcpy(pBuffer, m_pBuffer + m_lPos, iNumBytes);
	m_lPos += iNumBytes;
}

/******************************************************************************
** Method:		Write()
**
** Description:	Core method for writing a number of bytes to the stream.
**
** Parameters:	pBuffer		The buffer to write from.
**				iNumBytes	The number of bytes to write.
**
** Returns:		Nothing.
**
** Exceptions:	CMemStreamException on error.
**
*******************************************************************************
*/

void CMemStream::Write(const void* pBuffer, uint iNumBytes)
{
	ASSERT(m_pBuffer != NULL);
	ASSERT( (m_eMode == WriteOnly) || (m_eMode == ReadWrite) );
	ASSERT(m_bOwner == true);

	// Stream open?
	if (m_pBuffer == NULL)
		throw CMemStreamException(CMemStreamException::E_WRITE_FAILED);

	// Enough space in current block?
	if ((m_lPos + iNumBytes) > m_lAllocSize)
	{
		// Unlock buffer first.
		m_pBuffer = NULL;
		::GlobalUnlock(m_hMem);

		// Extend block by 1 page or iNumBytes, if larger.
		m_lAllocSize += max(ALLOC_SIZE, iNumBytes);
		m_hMem = ::GlobalReAlloc(m_hMem, m_lAllocSize, GMEM_ZEROINIT);
		
		// Realloc failed?
		if (m_hMem == NULL)
			throw CMemStreamException(CMemStreamException::E_WRITE_FAILED);

		m_pBuffer = (byte*) ::GlobalLock(m_hMem);
		ASSERT(m_pBuffer != NULL);
	}

	// Write bytes to the output buffer.
	memcpy(m_pBuffer + m_lPos, pBuffer, iNumBytes);
	m_lPos += iNumBytes;

	// Update EOF, if changed.
	m_lEOF = max(m_lPos, m_lEOF);
}

/******************************************************************************
** Method:		Seek()
**
** Description:	Core method for changing the stream pointer.
**
** Parameters:	lPos		The new position.
**				eOrigin		The origin from where to seek.
**
** Returns:		The new stream pointer.
**
** Exceptions:	CMemStreamException on error.
**
*******************************************************************************
*/

ulong CMemStream::Seek(ulong lPos, Origin eOrigin)
{
	ASSERT(m_pBuffer != NULL);

	// Stream open?
	if (m_pBuffer == NULL)
		throw CMemStreamException(CMemStreamException::E_SEEK_FAILED);

	// Calculate new position.
	switch(eOrigin)
	{
		case Start:		m_lPos  = lPos;				break;
		case Current:	m_lPos += lPos;				break;
		case End:		m_lPos  = m_lEOF - lPos;	break;
		default:		ASSERT(false);				break;
	}
		   
	// Seeked to invalid position?
	if (m_lPos > m_lEOF)
		throw CMemStreamException(CMemStreamException::E_SEEK_FAILED);

	return m_lPos;
}

/******************************************************************************
** Method:		IsEOF()
**
** Description:	Used to detect when the end of the stream has been reached.
**
** Parameters:	None.
**
** Returns:		true or false
**
*******************************************************************************
*/

bool CMemStream::IsEOF()
{
	ASSERT(m_pBuffer != NULL);

	return (m_lPos >= m_lEOF);
}

/******************************************************************************
** Method:		Throw()
**
** Description:	Throws an exception of the correct type for the derived stream.
**
** Parameters:	eErrCode	A CStreamException error code.
**
** Returns:		Nothing.
**
** Exceptions:	CMemStreamException always.
**
*******************************************************************************
*/

void CMemStream::Throw(int eErrCode)
{
	throw CMemStreamException(eErrCode);
}
