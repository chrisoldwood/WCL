/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BUFFER.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CBuffer class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BUFFER_HPP
#define BUFFER_HPP

/******************************************************************************
** 
** Class used to store a buffer of data.
**
*******************************************************************************
*/

class CBuffer
{
public:
	//
	// Constructors/Destructor.
	//
	CBuffer();
	CBuffer(uint nSize);
	CBuffer(const void* pData, uint nSize);
	CBuffer(HGLOBAL hGlobal);
	CBuffer(const CBuffer& oRHS);
	~CBuffer();
	
	//
	// Accessors.
	//
	uint        Size() const;
	const void* Buffer() const;
	void        Get(void* pData, uint nSize, uint nOffset = 0) const;

	//
	// Mutators.
	//
	void  Size(uint nSize);
	void* Buffer();
	void  Set(const void* pData, uint nSize, uint nOffset = 0);
	void  operator=(const CBuffer& oRHS);

	//
	// Conversion methods.
	//
	HGLOBAL ToGlobal() const;
	CString ToString() const;
	CString ToString(uint nChars) const;

protected:
	//
	// Members.
	//
	uint	m_nSize;
	void*	m_pBuffer;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline uint CBuffer::Size() const
{
	return m_nSize;
}

inline const void* CBuffer::Buffer() const
{
	return m_pBuffer;
}

inline void* CBuffer::Buffer()
{
	return m_pBuffer;
}

inline CString CBuffer::ToString() const
{
	return ToString(m_nSize);
}

inline CString CBuffer::ToString(uint nChars) const
{
	ASSERT(nChars <= m_nSize);

	return CString((char*)m_pBuffer, nChars);
}

#endif // BUFFER_HPP
