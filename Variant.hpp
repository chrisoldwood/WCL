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

	//! Construction from a boolean value.
	explicit Variant(bool value);

	//! Construction from a 32-bit signed value.
	explicit Variant(int32 value);

	//! Construction from a 32-bit unsigned long value.
	explicit Variant(uint32 value);

	//! Construction from a 64-bit signed value.
	explicit Variant(int64 value);

	//! Construction from a 64-bit unsigned long value.
	explicit Variant(uint64 value);

	//! Construction by creating a BSTR of the string.
	explicit Variant(const wchar_t* value);

	//! Construction by taking ownership of a BSTR value.
	explicit Variant(ComStr& value);

	//! Construction by coercing another variant to a different type.
	Variant(const VARIANT& value, VARTYPE type); // throw(ComException)

	//! Copy constructor.
	Variant(const Variant& rhs);

	//! Assignment operator.
	const Variant& operator=(const Variant& rhs);

	//! Destructor.
	~Variant();

	//
	// Properties.
	//

	//! Get the values' full type.
	VARTYPE type() const;

	//! Is a variant array?
	bool isArray() const;

	//! Get the value type.
	VARTYPE valueType() const;

	//
	// Methods.
	//

	//! Convert the variant value to a string.
	tstring format() const; // throw(ComException)

	//! Try and convert the variant value to a string.
	bool tryFormat(tstring& result) const;

	//
	// Class methods.
	//

	//! Format the variant type as a string.
	static const tchar* formatType(VARTYPE type);

	//! Format the final variant type and any flags as a string.
	static tstring formatFullType(const VARIANT& value);
};

////////////////////////////////////////////////////////////////////////////////
//! Get the values' full type. This returns the actual type as stored in the
//! vt member of the underlying variant type.

inline VARTYPE Variant::type() const
{
	return V_VT(this);
}

////////////////////////////////////////////////////////////////////////////////
//! Is a variant array?

inline bool Variant::isArray() const
{
	VARTYPE flags = static_cast<VARTYPE>(type() & (~VT_TYPEMASK));

	return (flags & VT_ARRAY);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the value type. This returns just the data type part of the undelying
//! vt member, i.e. it strips of any flags such as VT_ARRAY.

inline VARTYPE Variant::valueType() const
{
	return static_cast<VARTYPE>(type() & VT_TYPEMASK);
}

////////////////////////////////////////////////////////////////////////////////
// Helper function to get the variant value as a specific type.

template<typename T>
T getValue(const Variant& value); // throw(ComException)

////////////////////////////////////////////////////////////////////////////////
// Helper functions to get the variant value as a specific type.

template<>
tstring getValue(const Variant& value); // throw(ComException)

template<>
bool getValue(const Variant& value); // throw(ComException)

template<>
int32 getValue(const Variant& value); // throw(ComException)

template<>
uint32 getValue(const Variant& value); // throw(ComException)

template<>
int64 getValue(const Variant& value); // throw(ComException)

template<>
uint64 getValue(const Variant& value); // throw(ComException)

//namespace WCL
}

#endif // VARIANT_HPP
