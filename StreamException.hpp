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
#ifndef STREAMEXCEPTION_HPP
#define STREAMEXCEPTION_HPP

/******************************************************************************
** 
** This is the base class for all exceptions thrown from streams.
**
*******************************************************************************
*/

class CStreamException : public CException
{
public:
	//
	// Constructors/Destructor.
	//
	CStreamException(int nCode);
	virtual ~CStreamException();

	//
	// Exception codes (0 - 9).
	//
	enum
	{
		E_OPEN_FAILED,		// Generic open failure.
		E_CREATE_FAILED,	// Generic create failure.
		E_READ_FAILED,		// Read failure.
		E_WRITE_FAILED,		// Write failure.
		E_SEEK_FAILED,		// Seek failure.
		E_FORMAT_INVALID,	// Invalid stream format.
		E_VERSION_INVALID,	// Invalid stream version.
	};
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CStreamException::CStreamException(int nCode)
	: CException(nCode)
{
}

inline CStreamException::~CStreamException()
{
}

#endif //STREAMEXCEPTION_HPP
