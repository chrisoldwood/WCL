////////////////////////////////////////////////////////////////////////////////
//! \file   Exception.hpp
//! \brief  The Exception class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_EXCEPTION_HPP
#define WCL_EXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! The base class for all WCL exceptions.

class CException : public std::exception
{
public:
	//! Retrieve the error message.
	virtual const char* ErrorText() const;

	//! Retrieve the error message.
	virtual const char* what() const;

protected:
	//! Default constructor.
	CException();

	//! Destructor.
	virtual ~CException();

	//
	// Members.
	//
	CString	m_strErrorText;		//!< The error message.
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

inline CException::CException()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

inline CException::~CException()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Retrieve the error message.
//! \deprecated This should be removed and what() used instead.

inline const char* CException::ErrorText() const
{
	return m_strErrorText;
}

////////////////////////////////////////////////////////////////////////////////
//! Retrieve the error message. This method is overriden from the base class.

inline const char* CException::what() const
{
	return m_strErrorText;
}

#endif // WCL_EXCEPTION_HPP
