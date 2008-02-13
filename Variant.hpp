////////////////////////////////////////////////////////////////////////////////
//! \file   Variant.hpp
//! \brief  The Variant class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef VARIANT_HPP
#define VARIANT_HPP

#include "ComStr.hpp"

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A wrapper facade for the VARIANT type.

class Variant : public VARIANT
{
public:
	//! Default constructor.
	Variant();

	//! Construction by creating a BSTR of the string.
	explicit Variant(const wchar_t* pszValue);

	//! Construction by taking ownership of a BSTR value.
	explicit Variant(ComStr& bstrValue);

	//! Construction by coercing another variant to a different type.
	Variant(const VARIANT& vtVariant, VARTYPE eType); // throw(ComException)

	//! Destructor.
	~Variant();

	//
	// Class methods.
	//

	//! Format the variant type as a string.
	static const tchar* FormatType(VARTYPE eType);

	//! Format the final variant type and any flags as a string.
	static CString FormatFullType(const VARIANT* pVariant);
};

//namespace WCL
}

#endif // VARIANT_HPP
