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
	virtual ~CMemStreamException();
	
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
