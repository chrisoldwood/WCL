/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXCEPTION.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CException class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

/******************************************************************************
** 
** This is the base class for all exception classes.
**
*******************************************************************************
*/

class CException
{
public:
	//
	// Constructors/Destructor.
	//
	CException();
	virtual ~CException();

	//
	// Access to exception details.
	//
	virtual int         ErrorCode() const;
	virtual const char* ErrorText() const;
	
protected:
	//
	// Members.
	//
	int		m_nErrorCode;
	CString	m_strErrorText;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CException::CException()
{
//	ASSERT(false);
}

inline CException::~CException()
{
}

inline int CException::ErrorCode() const
{
	return m_nErrorCode;
}

inline const char* CException::ErrorText() const
{
	return m_strErrorText;
}

#endif //EXCEPTION_HPP
