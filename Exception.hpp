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

	//
	// Make abstract.
	//
	CException(int nCode);
	CException(int nCode, const char* pszText, ...);
	virtual ~CException();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CException::CException(int nCode)
	: m_nErrorCode(nCode)
{
}

inline CException::CException(int nCode, const char* pszText, ...)
	: m_nErrorCode(nCode)
{
	// Setup arguments.
	va_list	args;
	va_start(args, pszText);
	
	// Format message.
	m_strErrorText.FormatEx(pszText, args);
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
