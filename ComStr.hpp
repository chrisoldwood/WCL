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

#include <Core/BadLogicException.hpp>

namespace WCL
{

// Forward declarations.
class ComStr;

BSTR* AttachTo(ComStr& bstr);

////////////////////////////////////////////////////////////////////////////////
//! An RAII class for managing COM strings, aka a BSTR.

class ComStr /*: private Core::NotCopyable*/
{
public:
	//! Default constructor.
	ComStr();

	//! Construction by taking ownership of an existing string.
	explicit ComStr(BSTR bstr);

	//! Construction from an ANSI string.
	explicit ComStr(const char* psz);

	//! Construction from a UNICODE string.
	explicit ComStr(const wchar_t* psz);

	//! Construction from a std string.
	explicit ComStr(const tstring& str);

	//! Destructor.
	~ComStr();

	//
	// Methods.
	//

	//! Access the underlying value.
	BSTR Get() const;

	//! Query if we own a string.
	bool Empty() const;

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

	// NotCopyable.
	ComStr(const ComStr&);
	ComStr& operator=(const ComStr&);
};

////////////////////////////////////////////////////////////////////////////////
//! Access the underlying value.

inline BSTR ComStr::Get() const
{
	return m_bstr;
}

////////////////////////////////////////////////////////////////////////////////
//! Query if we own a string.

inline bool ComStr::Empty() const
{
	return (m_bstr == nullptr);
}

////////////////////////////////////////////////////////////////////////////////
//! Helper function to gain access to the internal member so that it can be
//! passed as an output parameter, without overloading the & operator.

inline BSTR* AttachTo(ComStr& bstr)
{
	if (!bstr.Empty())
		throw Core::BadLogicException(TXT("Cannot attach to a non-empty smart pointer"));

	return &bstr.m_bstr;
}

//namespace WCL
}

#endif // WCL_COMSTR_HPP
