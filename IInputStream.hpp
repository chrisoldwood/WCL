////////////////////////////////////////////////////////////////////////////////
//! \file   IInputStream.hpp
//! \brief  The IInputStream interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_IINPUTSTREAM_HPP
#define WCL_IINPUTSTREAM_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "IStreamBase.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The interface implemented by streams that support reading.

class IInputStream : public WCL::IStreamBase
{
public:
	//!	Read a number of bytes from the stream.
	virtual void Read(void* pBuffer, size_t iNumBytes) = 0;

	//! Query if the End of File has been reached.
	virtual bool IsEOF() = 0;

protected:
	//! Protected destructor.
	virtual ~IInputStream() {};
};

//namespace WCL
}

////////////////////////////////////////////////////////////////////////////////
// Stream extractors for the primitive types.

inline void operator>>(WCL::IInputStream& rStream, bool& rBuffer)
{
	rStream.Read(&rBuffer, sizeof(bool));
}

inline void operator>>(WCL::IInputStream& rStream, int8& rBuffer)
{
	rStream.Read(&rBuffer, sizeof(int8));
}

inline void operator>>(WCL::IInputStream& rStream, int16& rBuffer)
{
	rStream.Read(&rBuffer, sizeof(int16));
}

inline void operator>>(WCL::IInputStream& rStream, int32& rBuffer)
{
	rStream.Read(&rBuffer, sizeof(int32));
}

inline void operator>>(WCL::IInputStream& rStream, uint8&  rBuffer)
{
	rStream.Read(&rBuffer, sizeof(uint8));
}

inline void operator>>(WCL::IInputStream& rStream, uint16& rBuffer)
{
	rStream.Read(&rBuffer, sizeof(uint16));
}

inline void operator>>(WCL::IInputStream& rStream, uint32& rBuffer)
{
	rStream.Read(&rBuffer, sizeof(uint32));
}

#endif // WCL_IINPUTSTREAM_HPP
