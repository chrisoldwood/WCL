/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STREAMEXCEPTION.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CStreamException class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_STREAMEXCEPTION_HPP
#define WCL_STREAMEXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/Exception.hpp>

/******************************************************************************
**
** This is the base class for all exceptions thrown from streams.
**
*******************************************************************************
*/

class CStreamException : public Core::Exception
{
public:
	virtual ~CStreamException() CORE_NO_THROW {}

	//
	// Exception codes (0 - 9).
	//
	enum
	{
		E_INVALID_FILE,		//!< The file does not exist.
		E_INVALID_FOLDER,	//!< The folder does not exist.
		E_OPEN_FAILED,		// Generic open failure.
		E_CREATE_FAILED,	// Generic create failure.
		E_READ_FAILED,		// Read failure.
		E_WRITE_FAILED,		// Write failure.
		E_SEEK_FAILED,		// Seek failure.
		E_FORMAT_INVALID,	// Invalid stream format.
		E_VERSION_INVALID,	// Invalid stream version.
	};
};

#endif // WCL_STREAMEXCEPTION_HPP
