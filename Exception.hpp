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
	// Exception codes.
	//
	enum ErrCode
	{
		E_GENERIC = 0,	// Generic exception.
	};

	//
	// Constructors/Destructor.
	//
	CException();
	CException(ErrCode eCode, const char* pszText, ...);
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
}

inline CException::CException(ErrCode eCode, const char* pszText, ...)
	: m_nErrorCode(eCode)
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
