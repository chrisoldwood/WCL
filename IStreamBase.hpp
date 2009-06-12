////////////////////////////////////////////////////////////////////////////////
//! \file   IStreamBase.hpp
//! \brief  The IStreamBase interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_ISTREAMBASE_HPP
#define WCL_ISTREAMBASE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The base interface for the IInputStream and IOutputStream interfaces. This
//! interface allows a format and version number to be associated with the
//! stream so that lower-level code can handle schema changes.

class IStreamBase
{
public:
	//
	// Types.
	//

	//! The relative file position to seek from.
	enum SeekPos
	{
		BEGIN	= FILE_BEGIN,
		CURRENT	= FILE_CURRENT,
		END		= FILE_END,
	};

	//
	// Properties.
	//

	//! Get the stream contents format.
	virtual uint32 Format() const = 0;

	//! Set the stream contents format.
	virtual void SetFormat(uint32 nFormat) = 0;

	//! Get the stream contents version.
	virtual uint32 Version() const = 0;

	//! Set the stream contents version.
	virtual void SetVersion(uint32 nVersion) = 0;

	//
	// Methods.
	//

	//! Move the stream pointer.
	virtual StreamPos Seek(StreamPos lPos, SeekPos eFrom = BEGIN) = 0;

	//! Throw a stream specific exception with the specified error code.
	virtual void Throw(int eErrCode, DWORD dwLastError) = 0;

protected:
	//! Protected destructor.
	virtual ~IStreamBase() {};
};

//namespace WCL
}

#endif // WCL_ISTREAMBASE_HPP
