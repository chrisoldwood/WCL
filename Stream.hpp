/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STREAM.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CStream class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STREAM_HPP
#define STREAM_HPP

// For Read and Write access.
#define GENERIC_READWRITE	(GENERIC_READ | GENERIC_WRITE)

/******************************************************************************
** 
** This is the abstract class from which all I/O based classes are derived.
**
*******************************************************************************
*/

class CStream
{
public:
	//
	// Constructors/Destructor.
	//
	CStream();
	virtual ~CStream();

	//
	// Generic operations.
	// (Must be overriden)
	//
	virtual void  Read(void* pBuffer, uint iNumBytes) = 0;
	virtual void  Write(const void* pBuffer, uint iNumBytes) = 0;
	virtual ulong Seek(ulong lPos, uint nFrom = FILE_BEGIN) = 0;
	virtual bool  IsEOF() = 0;
	virtual void  Throw(int eErrCode) = 0;

	//
	// Type specific operations.
	//
	virtual void operator >>(bool&      rBuffer);
	virtual void operator >>(int8&      rBuffer);
	virtual void operator >>(int16&     rBuffer);
	virtual void operator >>(int32&     rBuffer);
	virtual void operator >>(uint8&     rBuffer);
	virtual void operator >>(uint16&    rBuffer);
	virtual void operator >>(uint32&    rBuffer);
	virtual void operator >>(CString&   rBuffer);
	virtual void operator >>(CDate&     rBuffer);
	virtual void operator >>(CTime&     rBuffer);
	virtual void operator >>(CDateTime& rBuffer);
	virtual void operator >>(CBuffer&   rBuffer);

	virtual void operator <<(const bool&      rBuffer);
	virtual void operator <<(const int8&      rBuffer);
	virtual void operator <<(const int16&     rBuffer);
	virtual void operator <<(const int32&     rBuffer);
	virtual void operator <<(const uint8&     rBuffer);
	virtual void operator <<(const uint16&    rBuffer);
	virtual void operator <<(const uint32&    rBuffer);
	virtual void operator <<(const CString&   rBuffer);
	virtual void operator <<(const char*      pBuffer);
	virtual void operator <<(const CDate&     rBuffer);
	virtual void operator <<(const CTime&     rBuffer);
	virtual void operator <<(const CDateTime& rBuffer);
	virtual void operator <<(const CBuffer&   rBuffer);
	
	//
	// Text specific operations.
	//
	CString ReadLine();
	void    WriteLine(const char* pszLine);

	//
	// Stream format and version.
	//
	uint32 Format () const;
	uint32 Version() const;

	void Format (uint32 nFormat);
	void Version(uint32 nVersion);

protected:
	//
	// Members.
	//
	uint	m_nMode;		// Open mode.
	uint32	m_nFormat;		// Stream format;
	uint32	m_nVersion;		// Stream version.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CStream::operator >>(bool& rBuffer)
{
	Read(&rBuffer, sizeof(bool));
}

inline void CStream::operator >>(int8& rBuffer)
{
	Read(&rBuffer, sizeof(int8));
}

inline void CStream::operator >>(int16& rBuffer)
{
	Read(&rBuffer, sizeof(int16));
}

inline void CStream::operator >>(int32& rBuffer)
{
	Read(&rBuffer, sizeof(int32));
}

inline void CStream::operator >>(uint8&  rBuffer)
{
	Read(&rBuffer, sizeof(uint8));
}

inline void CStream::operator >>(uint16& rBuffer)
{
	Read(&rBuffer, sizeof(uint16));
}

inline void CStream::operator >>(uint32& rBuffer)
{
	Read(&rBuffer, sizeof(uint32));
}

inline void CStream::operator >>(CString& rBuffer)
{
	rBuffer << *this;
}

inline void CStream::operator >>(CDate& rBuffer)
{
	rBuffer << *this;
}

inline void CStream::operator >>(CTime& rBuffer)
{
	rBuffer << *this;
}

inline void CStream::operator >>(CDateTime& rBuffer)
{
	rBuffer << *this;
}

inline void CStream::operator >>(CBuffer& rBuffer)
{
	uint32 nSize;

	Read(&nSize, sizeof(uint32));

	rBuffer.Size(nSize);

	Read(rBuffer.Buffer(), nSize);
}

inline void CStream::operator <<(const bool&  rBuffer)
{
	Write((void*) &rBuffer, sizeof(bool));
}

inline void CStream::operator <<(const int8&  rBuffer)
{
	Write((void*) &rBuffer, sizeof(int8));
}

inline void CStream::operator <<(const int16& rBuffer)
{
	Write((void*) &rBuffer, sizeof(int16));
}

inline void CStream::operator <<(const int32& rBuffer)
{
	Write((void*) &rBuffer, sizeof(int32));
}

inline void CStream::operator <<(const uint8&  rBuffer)
{
	Write((void*) &rBuffer, sizeof(uint8));
}

inline void CStream::operator <<(const uint16& rBuffer)
{
	Write((void*) &rBuffer, sizeof(uint16));
}

inline void CStream::operator <<(const uint32& rBuffer)
{
	Write((void*) &rBuffer, sizeof(uint32));
}

inline void CStream::operator <<(const CString& rBuffer)
{
	rBuffer >> *this;
}

inline void CStream::operator <<(const char* pBuffer)
{
	uint32 nLen = strlen(pBuffer)+1;

	Write(&nLen, sizeof(uint32));

	if (nLen)
		Write(pBuffer, nLen);
}

inline void CStream::operator <<(const CDate& rBuffer)
{
	rBuffer >> *this;
}

inline void CStream::operator <<(const CTime& rBuffer)
{
	rBuffer >> *this;
}

inline void CStream::operator <<(const CDateTime& rBuffer)
{
	rBuffer >> *this;
}

inline void CStream::operator <<(const CBuffer& rBuffer)
{
	uint32 nSize = rBuffer.Size();

	Write(&nSize, sizeof(uint32));
	Write(rBuffer.Buffer(), nSize);
}

inline uint32 CStream::Format() const
{
	return m_nFormat;
}

inline uint32 CStream::Version() const
{
	return m_nVersion;
}

inline void CStream::Format(uint32 nFormat)
{
	m_nFormat = nFormat;
}

inline void CStream::Version(uint32 nVersion)
{
	m_nVersion = nVersion;
}

#endif //STREAM_HPP
