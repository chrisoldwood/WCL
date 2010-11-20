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
#ifndef WCL_BUFFER_HPP
#define WCL_BUFFER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

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
	CBuffer(size_t nSize);
	CBuffer(const void* pData, size_t nSize);
	explicit CBuffer(HGLOBAL hGlobal);
	CBuffer(const CBuffer& oRHS);
	~CBuffer();

	//
	// Accessors.
	//
	size_t      Size() const;
	const void* Buffer() const;
	void        Get(void* pData, size_t nSize, size_t nOffset = 0) const;

	//
	// Mutators.
	//
	void  Size(size_t nSize);
	void* Buffer();
	void  Set(const void* pData, size_t nSize, size_t nOffset = 0);

	//
	// Operators.
	//
	CBuffer& operator=(const CBuffer& oRHS);
	bool operator==(const CBuffer& oRHS) const;
	bool operator!=(const CBuffer& oRHS) const;

 	//
	// Conversion methods.
	//
	HGLOBAL ToGlobal() const;

	//! Convert the entire buffer to a string.
	CString ToString(TextFormat eFormat) const;

	//! Fill the buffer with the contents of a string.
	void FromString(const CString& str, TextFormat eFormat, bool bIncNull = true);

protected:
	//
	// Members.
	//
	size_t	m_nSize;
	void*	m_pBuffer;

	//
	// Persistance.
	//
	friend void operator >>(WCL::IInputStream&  rStream, CBuffer& rBuffer);
	friend void operator <<(WCL::IOutputStream& rStream, const CBuffer& rBuffer);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline size_t CBuffer::Size() const
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

inline bool CBuffer::operator!=(const CBuffer& oRHS) const
{
	return !operator==(oRHS);
}

#endif // WCL_BUFFER_HPP
