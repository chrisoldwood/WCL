////////////////////////////////////////////////////////////////////////////////
//! \file   Variant.cpp
//! \brief  The Variant class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Variant.hpp"
#include "ComException.hpp"
#include <Core/StringUtils.hpp>
#include <Core/AnsiWide.hpp>
#include <WCL/VariantBool.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Variant::Variant()
{
	::VariantInit(this);
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a boolean value.

Variant::Variant(bool value)
{
	::VariantInit(this);

	V_VT(this)   = VT_BOOL;
	V_BOOL(this) = ToVariantBool(value);
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a 32-bit signed value.

Variant::Variant(int32 value)
{
	::VariantInit(this);

	V_VT(this) = VT_I4;
	V_I4(this) = value;
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a 32-bit unsigned long value.

Variant::Variant(uint32 value)
{
	::VariantInit(this);

	V_VT(this)  = VT_UI4;
	V_UI4(this) = value;
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a 64-bit signed value.

Variant::Variant(int64 value)
{
	::VariantInit(this);

	V_VT(this) = VT_I8;
	V_I8(this) = value;
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a 64-bit unsigned long value.

Variant::Variant(uint64 value)
{
	::VariantInit(this);

	V_VT(this)  = VT_UI8;
	V_UI8(this) = value;
}

////////////////////////////////////////////////////////////////////////////////
//! Construction by creating a BSTR of the string.

Variant::Variant(const wchar_t* value)
{
	::VariantInit(this);

	V_VT(this)   = VT_BSTR;
	V_BSTR(this) = ::SysAllocString(value);
}

////////////////////////////////////////////////////////////////////////////////
// Construction by taking ownership of a BSTR value.

Variant::Variant(ComStr& value)
{
	::VariantInit(this);

	V_VT(this)   = VT_BSTR;
	V_BSTR(this) = value.Detach();
}

////////////////////////////////////////////////////////////////////////////////
// Construction by coercing another variant to a different type.

Variant::Variant(const VARIANT& value, VARTYPE type)
{
	::VariantInit(this);

	HRESULT hr = ::VariantChangeType(this, const_cast<VARIANT*>(&value), 0, type);

	if (FAILED(hr))
		throw ComException(hr, Core::fmt(TXT("Failed to convert a variant from %s to %s"),
				formatFullType(value).c_str(), formatType(type)).c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Copy constructor.

Variant::Variant(const Variant& rhs)
{
	::VariantInit(this);

	HRESULT hr = ::VariantCopy(this, const_cast<Variant*>(&rhs));

	if (FAILED(hr))
		throw ComException(hr, Core::fmt(TXT("Failed to copy a '%s' variant"),
								formatFullType(rhs).c_str()).c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Assignment operator.

const Variant& Variant::operator=(const Variant& rhs)
{
	HRESULT hr = ::VariantCopy(this, const_cast<Variant*>(&rhs));

	if (FAILED(hr))
		throw ComException(hr, Core::fmt(TXT("Failed to copy a '%s' variant"),
								formatFullType(rhs).c_str()).c_str());

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Variant::~Variant()
{
	::VariantClear(this);
}

////////////////////////////////////////////////////////////////////////////////
//! Convert the variant value to a string.

tstring Variant::format() const
{
	VARTYPE type = V_VT(this);

	// No type as such?
	if ( (type == VT_EMPTY) || (type == VT_NULL) )
	{
		return TXT("");
	}
	// Already a string?
	else if (type == VT_BSTR)
	{
		return W2T(V_BSTR(this));
	}
	// Special handling for booleans.
	else if (type == VT_BOOL)
	{
		return (IsTrue(V_BOOL(this)) ? TXT("True") : TXT("False"));
	}

	// Try coercing to a string.
	Variant value(*this, VT_BSTR);

	return W2T(V_BSTR(&value));
}

////////////////////////////////////////////////////////////////////////////////
//! Try and convert the variant value to a string.

bool Variant::tryFormat(tstring& result) const
{
	VARTYPE type = V_VT(this);

	// No type as such?
	if ( (type == VT_EMPTY) || (type == VT_NULL) )
	{
		result = TXT("");
		return true;
	}

	// Already a string?
	if (type == VT_BSTR)
	{
		result = W2T(V_BSTR(this));
		return true;
	}

	// Special handling for booleans.
	if (type == VT_BOOL)
	{
		result = (IsTrue(V_BOOL(this)) ? TXT("True") : TXT("False"));
		return true;
	}

	ASSERT(!isArray());

	Variant value;

	// Attempt standard conversion.
	HRESULT hr = ::VariantChangeType(&value, const_cast<VARIANT*>(static_cast<const VARIANT*>(this)), 0, VT_BSTR);

	if (FAILED(hr))
		return false;

	result = W2T(V_BSTR(&value));

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//! Format the variant type as a string.

const tchar* Variant::formatType(VARTYPE type)
{
	const tchar* symbol = TXT("");

	switch (type & VT_TYPEMASK)
	{
		case VT_EMPTY:				symbol = TXT("VT_EMPTY");			break;
		case VT_NULL:				symbol = TXT("VT_NULL");			break;
		case VT_I2:					symbol = TXT("VT_I2");				break;
		case VT_I4:					symbol = TXT("VT_I4");				break;
		case VT_R4:					symbol = TXT("VT_R4");				break;
		case VT_R8:					symbol = TXT("VT_R8");				break;
		case VT_CY:					symbol = TXT("VT_CY");				break;
		case VT_DATE:				symbol = TXT("VT_DATE");			break;
		case VT_BSTR:				symbol = TXT("VT_BSTR");			break;
		case VT_DISPATCH:			symbol = TXT("VT_DISPATCH");		break;
		case VT_ERROR:				symbol = TXT("VT_ERROR");			break;
		case VT_BOOL:				symbol = TXT("VT_BOOL");			break;
		case VT_VARIANT:			symbol = TXT("VT_VARIANT");			break;
		case VT_UNKNOWN:			symbol = TXT("VT_UNKNOWN");			break;
		case VT_DECIMAL:			symbol = TXT("VT_DECIMAL");			break;
		case VT_I1:					symbol = TXT("VT_I1");				break;
		case VT_UI1:				symbol = TXT("VT_UI1");				break;
		case VT_UI2:				symbol = TXT("VT_UI2");				break;
		case VT_UI4:				symbol = TXT("VT_UI4");				break;
		case VT_I8:					symbol = TXT("VT_I8");				break;
		case VT_UI8:				symbol = TXT("VT_UI8");				break;
		case VT_INT:				symbol = TXT("VT_INT");				break;
		case VT_UINT:				symbol = TXT("VT_UINT");			break;
		case VT_VOID:				symbol = TXT("VT_VOID");			break;
		case VT_HRESULT:			symbol = TXT("VT_HRESULT");			break;
		case VT_PTR:				symbol = TXT("VT_PTR");				break;
		case VT_SAFEARRAY:			symbol = TXT("VT_SAFEARRAY");		break;
		case VT_CARRAY:				symbol = TXT("VT_CARRAY");			break;
		case VT_USERDEFINED:		symbol = TXT("VT_USERDEFINED");		break;
		case VT_LPSTR:				symbol = TXT("VT_LPSTR");			break;
		case VT_LPWSTR:				symbol = TXT("VT_LPWSTR");			break;
		case VT_FILETIME:			symbol = TXT("VT_FILETIME");		break;
		case VT_BLOB:				symbol = TXT("VT_BLOB");			break;
		case VT_STREAM:				symbol = TXT("VT_STREAM");			break;
		case VT_STORAGE:			symbol = TXT("VT_STORAGE");			break;
		case VT_STREAMED_OBJECT:	symbol = TXT("VT_STREAMED_OBJECT");	break;
		case VT_STORED_OBJECT:		symbol = TXT("VT_STORED_OBJECT");	break;
		case VT_BLOB_OBJECT:		symbol = TXT("VT_BLOB_OBJECT");		break;
		case VT_CF:					symbol = TXT("VT_CF");				break;
		case VT_CLSID:				symbol = TXT("VT_CLSID");			break;
		default:					ASSERT_FALSE();						break;
	}

	return symbol;
}

////////////////////////////////////////////////////////////////////////////////
//! Format the final variant type and any flags as a string. If the variant is
//! type VT_VARIANT|VT_BYREF, it gets the contained variants type.

tstring Variant::formatFullType(const VARIANT& value)
{
	const VARIANT* variant = &value;

	// Recurse, if just a reference to another variant.
	if (V_VT(variant) == (VT_VARIANT|VT_BYREF))
		variant = V_VARIANTREF(variant);

	VARTYPE type = V_VT(variant);

	// Get the variants type.
	tstring str = formatType(type);

	ushort flags = static_cast<ushort>(type & (~VT_TYPEMASK));

	if (flags & VT_VECTOR)
		str += TXT("|VT_VECTOR");

	if (flags & VT_ARRAY)
		str += TXT("|VT_ARRAY");

	if (flags & VT_BYREF)
		str += TXT("|VT_BYREF");

	return str;
}

////////////////////////////////////////////////////////////////////////////////
//! Helper function to get the variant value as a tstring.

template<>
tstring getValue(const Variant& value)
{
	VARTYPE type = value.type();

	// Treat the special empty types as empty strings.
	if ( (type == VT_NULL) || (type == VT_EMPTY) )
		return TXT("");

	if (type != VT_BSTR)
		throw ComException(DISP_E_TYPEMISMATCH, Core::fmt(TXT("Invalid variant type: %s, expected VT_BSTR or compatible type"),
													Variant::formatFullType(value).c_str()));

	return V_BSTR(&value);
}

////////////////////////////////////////////////////////////////////////////////
// Helper function to get the variant value as a boolean.

template<>
bool getValue(const Variant& value)
{
	VARTYPE type = value.type();

	if (type != VT_BOOL)
		throw ComException(DISP_E_TYPEMISMATCH, Core::fmt(TXT("Invalid variant type: %s, expected VT_BOOL"),
													Variant::formatFullType(value).c_str()));

	return IsTrue(V_BOOL(&value));
}

////////////////////////////////////////////////////////////////////////////////
// Helper function to get the variant value as a signed 32-bit integer.

template<>
int32 getValue(const Variant& value)
{
	VARTYPE type = value.type();

	if (type != VT_I4)
		throw ComException(DISP_E_TYPEMISMATCH, Core::fmt(TXT("Invalid variant type: %s, expected VT_I4 or compatible type"),
													Variant::formatFullType(value).c_str()));

	return V_I4(&value);
}

////////////////////////////////////////////////////////////////////////////////
// Helper function to get the variant value as an unsigned 32-bit integer.

template<>
uint32 getValue(const Variant& value)
{
	VARTYPE type = value.type();

	if (type != VT_UI4)
		throw ComException(DISP_E_TYPEMISMATCH, Core::fmt(TXT("Invalid variant type: %s, expected VT_UI4 or compatible type"),
													Variant::formatFullType(value).c_str()));

	return V_UI4(&value);
}

////////////////////////////////////////////////////////////////////////////////
// Helper function to get the variant value as a signed 32-bit integer.

template<>
int64 getValue(const Variant& value)
{
	VARTYPE type = value.type();

	// Widen smaller types.
	if (type == VT_I1)
		return V_I1(&value);

	if (type == VT_UI1)
		return V_UI1(&value);

	if (type == VT_I2)
		return V_I2(&value);

	if (type == VT_UI2)
		return V_UI2(&value);

	if (type == VT_I4)
		return V_I4(&value);

	if (type == VT_UI4)
		return V_UI4(&value);

	if (type != VT_I8)
		throw ComException(DISP_E_TYPEMISMATCH, Core::fmt(TXT("Invalid variant type: %s, expected VT_I8 or compatible type"),
													Variant::formatFullType(value).c_str()));

	return V_I8(&value);
}

////////////////////////////////////////////////////////////////////////////////
// Helper function to get the variant value as an unsigned 32-bit integer.

template<>
uint64 getValue(const Variant& value)
{
	VARTYPE type = value.type();

	// Widen smaller types.
	if (type == VT_UI1)
		return V_UI1(&value);

	if (type == VT_UI2)
		return V_UI2(&value);

	if (type == VT_UI4)
		return V_UI4(&value);

	if (type != VT_UI8)
		throw ComException(DISP_E_TYPEMISMATCH, Core::fmt(TXT("Invalid variant type: %s, expected VT_UI8 or compatible type"),
													Variant::formatFullType(value).c_str()));

	return V_UI8(&value);
}

//namespace WCL
}
