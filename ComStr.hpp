////////////////////////////////////////////////////////////////////////////////
//! \file   ComStr.hpp
//! \brief  The ComStr class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_COMSTR_HPP
#define WCL_COMSTR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

// Forward declarations.
class ComStr;

BSTR* AttachTo(ComStr& bstr);

////////////////////////////////////////////////////////////////////////////////
//! An RAII class for managing COM strings, aka a BSTR.

class ComStr : private Core::NotCopyable
{
public:
	//! Default constructor.
	ComStr();

	//! Construction by taking ownership of an exsiting string.
	explicit ComStr(BSTR bstr);

	//! Construction from an ANSI string.
	explicit ComStr(const char* psz);

	//! Construction from a UNICODE string.
	explicit ComStr(const wchar_t* psz);

	//! Destructor.
	~ComStr();
	
	//
	// Methods.
	//

	//! Access the underlying value.
	BSTR Get() const;

	//! Free the string.
	void Release();
	
	//! Take ownership of an external string.
	void Attach(BSTR bstr);

	//! Take external ownership of the string.
	BSTR Detach();

private:
	//
	// Members.
	//
	BSTR	m_bstr;		//! The underlying COM string.

	//! Allow attachment via an output parameter.
	friend BSTR* AttachTo(ComStr& bstr);
};

////////////////////////////////////////////////////////////////////////////////
//! Access the underlying value.

inline BSTR ComStr::Get() const
{
	return m_bstr;
}

////////////////////////////////////////////////////////////////////////////////
//! Helper function to gain access to the internal member so that it can be
//! passed as an output parameter, without overloading the & operator.

inline BSTR* AttachTo(ComStr& bstr)
{
	return &bstr.m_bstr;
}

//namespace WCL
}

#endif // WCL_COMSTR_HPP
