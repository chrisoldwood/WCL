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
#ifndef MEMSTREAM_HPP
#define MEMSTREAM_HPP

/******************************************************************************
** 
** This class is used as a memory based file.
**
*******************************************************************************
*/

class CMemStream : public CStream
{
public:
	//
	// Constructors/Destructor.
	//
	CMemStream();
	~CMemStream();
	
	//
	// Accessors & mutators.
	//
	void    AttachHandle(HGLOBAL hMem, bool bOwn = true);
	HGLOBAL DetachHandle();

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
	virtual ulong Seek(ulong lPos, Origin eOrigin);
	virtual bool  IsEOF();
	virtual void  Throw(int eErrCode);

protected:
	//
	// Members.
	//
	HGLOBAL	m_hMem;			// Handle to memory block.
	bool	m_bOwner;		// Owner of memory block?
	byte*	m_pBuffer;		// Pointer to buffer.
	ulong	m_lAllocSize;	// Current allocated size.
	ulong	m_lEOF;			// Current end of stream.
	ulong	m_lPos;			// Current position in the stream.

	// Default allocation size in bytes (1K).
	enum { ALLOC_SIZE = 1024 };

	//
	// Internal methods.
	//
	void FreeBlock();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMSTREAM_HPP
