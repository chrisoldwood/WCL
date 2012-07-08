/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTREAM.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMemStream class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_MEMSTREAM_HPP
#define WCL_MEMSTREAM_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Stream.hpp"

// Forward declarations.
class CBuffer;

/******************************************************************************
**
** This is memory based stream.
**
*******************************************************************************
*/

class CMemStream : public CStream
{
public:
	//
	// Constructors/Destructor.
	//
	CMemStream(CBuffer& oBuffer);
	virtual	~CMemStream();

	//
	// Properties.
	//
	size_t Size() const;

	//
	// Open/Close operations.
	//
	void Create();
	void Open();
	void Close();

	//
	// Overriden generic operations.
	//
	virtual void  Read(void* pBuffer, size_t iNumBytes);
	virtual void  Write(const void* pBuffer, size_t iNumBytes);
	virtual WCL::StreamPos Seek(WCL::StreamPos lPos, SeekPos eFrom = BEGIN);
	virtual bool  IsEOF();
	virtual void  Throw(int eErrCode, DWORD dwLastError);

protected:
	//
	// Members.
	//
	CBuffer&	m_oBuffer;		// Memory block.
	byte*		m_pBuffer;		// Pointer to data.
	size_t		m_lAllocSize;	// Current allocated size.
	size_t		m_lEOF;			// Current end of stream.
	size_t		m_lPos;			// Current position in the stream.

private:
	// NotCopyable.
	CMemStream(const CMemStream&);
	CMemStream& operator=(const CMemStream&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline size_t CMemStream::Size() const
{
	return m_lEOF;
}

#endif // WCL_MEMSTREAM_HPP
