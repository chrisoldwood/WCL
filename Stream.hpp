////////////////////////////////////////////////////////////////////////////////
//! \file   CStream.hpp
//! \brief  The CStream class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_STREAM_HPP
#define WCL_STREAM_HPP

#include "IStreamBase.hpp"
#include "IInputStream.hpp"
#include "IOutputStream.hpp"

////////////////////////////////////////////////////////////////////////////////
//! The legacy abstract base class used for bidirectional I/O.

class CStream : public WCL::IInputStream, public WCL::IOutputStream
{
public:
	//! Constructor.
	CStream();

	//! Destructor.
	virtual ~CStream();

	//
	// Text stream specific operations.
	//

	//! Read a line of text.
	CString ReadLine();

	//! Write a line of text.
	void WriteLine(const char* pszLine);

	//
	// Default implementation of IStreamBase.
	//

	//! Get the stream contents format.
	virtual uint32 Format() const;

	//! Set the stream contents format.
	virtual void SetFormat(uint32 nFormat);

	//! Get the stream contents version.
	virtual uint32 Version() const;

	//! Set the stream contents version.
	virtual void SetVersion(uint32 nVersion);
	
protected:
	//
	// Members.
	//
	uint	m_nMode;		//!< The read/write mode.
	uint32	m_nFormat;		//!< The stream contents format.
	uint32	m_nVersion;		//!< The stream contents version.
};

#endif // WCL_STREAM_HPP
