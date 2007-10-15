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
	CBuffer(uint nSize);
	CBuffer(const void* pData, uint nSize);
	explicit CBuffer(HGLOBAL hGlobal);
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

	//
	// Operators.
	//
	void operator=(const CBuffer& oRHS);
	bool operator==(const CBuffer& oRHS) const;
	bool operator!=(const CBuffer& oRHS) const;

 	//
	// Conversion methods.
	//
	HGLOBAL ToGlobal() const;
	CString ToString() const;
	CString ToString(uint nChars) const;

	void FromString(const char* pszString, bool bIncNull = true);

protected:
	//
	// Members.
	//
	uint	m_nSize;
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

inline bool CBuffer::operator!=(const CBuffer& oRHS) const
{
	return !operator==(oRHS);
}

inline CString CBuffer::ToString() const
{
	return ToString(m_nSize);
}

inline CString CBuffer::ToString(uint nChars) const
{
	ASSERT(nChars <= m_nSize);

	if (m_pBuffer == NULL)
		return "";

	return CString((char*)m_pBuffer, nChars);
}

#endif // WCL_BUFFER_HPP
