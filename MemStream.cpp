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

CMemStream::CMemStream(CBuffer& oBuffer)
	: m_oBuffer(oBuffer)
	, m_pBuffer(NULL)
	, m_lAllocSize(oBuffer.Size())
	, m_lEOF(oBuffer.Size())
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
	// Set inital block size.
	m_lAllocSize = ALLOC_SIZE;

	// Allocate an inital block.
	m_oBuffer.Size(m_lAllocSize);

	// Get pointer to buffer.
	m_pBuffer = (byte*) m_oBuffer.Buffer();

	ASSERT(m_pBuffer != NULL);

	// Set to SOF.
	m_lEOF  = 0;
	m_lPos  = 0;
	m_nMode = GENERIC_WRITE;
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
	// Get pointer to buffer.
	m_pBuffer = (byte*) m_oBuffer.Buffer();

	ASSERT(m_pBuffer != NULL);

	// Set to SOF.
	m_lPos  = 0;
	m_nMode = GENERIC_READ;
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
	// Writing?
	if (m_nMode & GENERIC_WRITE)
	{
		// Shrink block to EOF.
		m_oBuffer.Size(m_lEOF);
	}

	// Reset members.
	m_pBuffer = NULL;
	m_nMode   = NULL;
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
	ASSERT(m_nMode & GENERIC_READ);

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
	ASSERT(m_nMode & GENERIC_WRITE);

	// Stream open?
	if (m_pBuffer == NULL)
		throw CMemStreamException(CMemStreamException::E_WRITE_FAILED);

	// Enough space in current block?
	if ((m_lPos + iNumBytes) > m_lAllocSize)
	{
		// Extend block by 1 page or iNumBytes, if larger.
		m_lAllocSize += max(ALLOC_SIZE, iNumBytes);

		m_pBuffer = NULL;

		m_oBuffer.Size(m_lAllocSize);
		
		m_pBuffer = (byte*) m_oBuffer.Buffer();

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
**				nFrom		The origin from where to seek.
**
** Returns:		The new stream pointer.
**
** Exceptions:	CMemStreamException on error.
**
*******************************************************************************
*/

ulong CMemStream::Seek(ulong lPos, uint nFrom)
{
	ASSERT(m_pBuffer != NULL);

	// Stream open?
	if (m_pBuffer == NULL)
		throw CMemStreamException(CMemStreamException::E_SEEK_FAILED);

	// Calculate new position.
	switch(nFrom)
	{
		case FILE_BEGIN:	m_lPos  = lPos;				break;
		case FILE_CURRENT:	m_lPos += lPos;				break;
		case FILE_END:		m_lPos  = m_lEOF - lPos;	break;
		default:			ASSERT(false);				break;
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
