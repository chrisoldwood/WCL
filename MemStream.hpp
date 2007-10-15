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
	ulong Size() const;

	//
	// Open/Close operations.
	//
	void Create();
	void Open();
	void Close();

	//
	// Overriden generic operations.
	//
	virtual void  Read(void* pBuffer, uint iNumBytes);
	virtual void  Write(const void* pBuffer, uint iNumBytes);
	virtual ulong Seek(ulong lPos, uint nFrom = FILE_BEGIN);
	virtual bool  IsEOF();
	virtual void  Throw(int eErrCode);

protected:
	//
	// Members.
	//
	CBuffer&	m_oBuffer;		// Memory block.
	byte*		m_pBuffer;		// Pointer to data.
	ulong		m_lAllocSize;	// Current allocated size.
	ulong		m_lEOF;			// Current end of stream.
	ulong		m_lPos;			// Current position in the stream.

	// Default allocation size in bytes (1K).
	enum { ALLOC_SIZE = 1024 };
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline ulong CMemStream::Size() const
{
	return m_lEOF;
}

#endif // WCL_MEMSTREAM_HPP
