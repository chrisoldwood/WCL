/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRCVTEXCEPTION.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CStrCvtException class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STRCVTEXCEPTION_HPP
#define STRCVTEXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/Exception.hpp>

/******************************************************************************
** 
** The exception class thrown by the CStrCvt functions.
**
*******************************************************************************
*/

class CStrCvtException : public Core::Exception
{
public:
	//
	// Exception codes.
	//
	enum ErrCode
	{
		E_INVALID_FORMAT = 10,		// String has an invalid format.
		E_INVALID_RANGE  = 11,		// String value too small/large for type.
	};

	//
	// Constructors/Destructor.
	//
	CStrCvtException(int eErrCode);
	virtual	~CStrCvtException() throw();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // STRCVTEXCEPTION_HPP
