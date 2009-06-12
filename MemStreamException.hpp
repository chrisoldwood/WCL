/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTREAMEXCEPTION.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMemStreamException class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMSTREAMEXCEPTION_HPP
#define MEMSTREAMEXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StreamException.hpp"

// Forward declarations.
class CMemStream;

/******************************************************************************
**
** This exception class is thrown by CMemStream.
**
*******************************************************************************
*/

class CMemStreamException : public CStreamException
{
public:
	//
	// Constructors/Destructor.
	//
	CMemStreamException(int eErrCode);
	virtual ~CMemStreamException() throw();

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMSTREAMEXCEPTION_HPP
