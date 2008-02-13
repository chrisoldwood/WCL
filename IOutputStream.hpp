////////////////////////////////////////////////////////////////////////////////
//! \file   IOutputStream.hpp
//! \brief  The IOutputStream interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_IOUTPUTSTREAM_HPP
#define WCL_IOUTPUTSTREAM_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "IStreamBase.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The interface implemented by streams that support reading.

class IOutputStream : public WCL::IStreamBase
{
public:
	//! Write a number of bytes to the stream.
	virtual void Write(const void* pBuffer, uint iNumBytes) = 0;
	
protected:
	//! Protected destructor.
	virtual ~IOutputStream() = 0 {}; 
};

//namespace WCL
}

////////////////////////////////////////////////////////////////////////////////
// Stream inserters for the primitive types.

inline void operator<<(WCL::IOutputStream& rStream, bool rBuffer)
{
	rStream.Write(&rBuffer, sizeof(bool));
}

inline void operator<<(WCL::IOutputStream& rStream, int8 rBuffer)
{
	rStream.Write(&rBuffer, sizeof(int8));
}

inline void operator<<(WCL::IOutputStream& rStream, int16 rBuffer)
{
	rStream.Write(&rBuffer, sizeof(int16));
}

inline void operator<<(WCL::IOutputStream& rStream, int32 rBuffer)
{
	rStream.Write(&rBuffer, sizeof(int32));
}

inline void operator<<(WCL::IOutputStream& rStream, uint8 rBuffer)
{
	rStream.Write(&rBuffer, sizeof(uint8));
}

inline void operator<<(WCL::IOutputStream& rStream, uint16 rBuffer)
{
	rStream.Write(&rBuffer, sizeof(uint16));
}

inline void operator<<(WCL::IOutputStream& rStream, uint32 rBuffer)
{
	rStream.Write(&rBuffer, sizeof(uint32));
}

inline void operator<<(WCL::IOutputStream& rStream, const char* pBuffer)
{
	uint32 nChars = strlen(pBuffer)+1;

	rStream.Write(&nChars, sizeof(uint32));
	rStream.Write(pBuffer, Core::NumBytes<char>(nChars));
}

inline void operator<<(WCL::IOutputStream& rStream, const wchar_t* pBuffer)
{
	uint32 nChars = wcslen(pBuffer)+1;

	rStream.Write(&nChars, sizeof(uint32));
	rStream.Write(pBuffer, Core::NumBytes<wchar_t>(nChars));
}

#endif // WCL_IOUTPUTSTREAM_HPP
