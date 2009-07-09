/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FILEEXCEPTION.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CFileException class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FILEEXCEPTION_HPP
#define FILEEXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StreamException.hpp"

// Forward declarations.
class CFile;
class CPath;

/******************************************************************************
** 
** This exception class is thrown by CFile.
**
*******************************************************************************
*/

class CFileException : public CStreamException
{
public:
	//
	// Exception codes (File specific).
	// (0 - 9) defined by CStreamException
	//
	enum ErrCode
	{
		E_READ_ONLY    = 10,	// File is read-only.
		E_PATH_INVALID,			// Path is invalid.
	};

	//
	// Constructors/Destructor.
	//
	CFileException(int eErrCode, const CPath& rPath, DWORD dwLastError);
	virtual	~CFileException() throw();
	
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

#endif //FILEEXCEPTION_HPP
