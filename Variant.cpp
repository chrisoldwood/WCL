////////////////////////////////////////////////////////////////////////////////
//! \file   Variant.cpp
//! \brief  The Variant class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Variant.hpp"
#include "ComException.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Variant::Variant()
{
	::VariantInit(this);
}

////////////////////////////////////////////////////////////////////////////////
// Construction by taking ownership of a BSTR value.

Variant::Variant(ComStr& bstrValue)
{
	::VariantInit(this);

	V_VT(this)   = VT_BSTR;
	V_BSTR(this) = bstrValue.Detach();
}

////////////////////////////////////////////////////////////////////////////////
// Construction by coercing another variant to a different type.

Variant::Variant(const VARIANT& vtVariant, VARTYPE eType)
{
	::VariantInit(this);

	HRESULT hr = ::VariantChangeType(this, const_cast<VARIANT*>(&vtVariant), 0, eType);

	if (FAILED(hr))
		throw ComException(hr, CString::Fmt("Failed to convert a variant from %s to %s",
				FormatFullType(&vtVariant), FormatType(eType)));
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Variant::~Variant()
{
	::VariantClear(this);
}

////////////////////////////////////////////////////////////////////////////////
//! Format the variant type as a string.

const char* Variant::FormatType(VARTYPE eType)
{
	const char* pszType = "";

	switch (eType & VT_TYPEMASK)
	{
		case VT_EMPTY:				pszType = "VT_EMPTY";			break;
		case VT_NULL:				pszType = "VT_NULL";			break;
		case VT_I2:					pszType = "VT_I2";				break;
		case VT_I4:					pszType = "VT_I4";				break;
		case VT_R4:					pszType = "VT_R4";				break;
		case VT_R8:					pszType = "VT_R8";				break;
		case VT_CY:					pszType = "VT_CY";				break;
		case VT_DATE:				pszType = "VT_DATE";			break;
		case VT_BSTR:				pszType = "VT_BSTR";			break;
		case VT_DISPATCH:			pszType = "VT_DISPATCH";		break;
		case VT_ERROR:				pszType = "VT_ERROR";			break;
		case VT_BOOL:				pszType = "VT_BOOL";			break;
		case VT_VARIANT:			pszType = "VT_VARIANT";			break;
		case VT_UNKNOWN:			pszType = "VT_UNKNOWN";			break;
		case VT_DECIMAL:			pszType = "VT_DECIMAL";			break;
		case VT_I1:					pszType = "VT_I1";				break;
		case VT_UI1:				pszType = "VT_UI1";				break;
		case VT_UI2:				pszType = "VT_UI2";				break;
		case VT_UI4:				pszType = "VT_UI4";				break;
		case VT_I8:					pszType = "VT_I8";				break;
		case VT_UI8:				pszType = "VT_UI8";				break;
		case VT_INT:				pszType = "VT_INT";				break;
		case VT_UINT:				pszType = "VT_UINT";			break;
		case VT_VOID:				pszType = "VT_VOID";			break;
		case VT_HRESULT:			pszType = "VT_HRESULT";			break;
		case VT_PTR:				pszType = "VT_PTR";				break;
		case VT_SAFEARRAY:			pszType = "VT_SAFEARRAY";		break;
		case VT_CARRAY:				pszType = "VT_CARRAY";			break;
		case VT_USERDEFINED:		pszType = "VT_USERDEFINED";		break;
		case VT_LPSTR:				pszType = "VT_LPSTR";			break;
		case VT_LPWSTR:				pszType = "VT_LPWSTR";			break;
		case VT_FILETIME:			pszType = "VT_FILETIME";		break;
		case VT_BLOB:				pszType = "VT_BLOB";			break;
		case VT_STREAM:				pszType = "VT_STREAM";			break;
		case VT_STORAGE:			pszType = "VT_STORAGE";			break;
		case VT_STREAMED_OBJECT:	pszType = "VT_STREAMED_OBJECT";	break;
		case VT_STORED_OBJECT:		pszType = "VT_STORED_OBJECT";	break;
		case VT_BLOB_OBJECT:		pszType = "VT_BLOB_OBJECT";		break;
		case VT_CF:					pszType = "VT_CF";				break;
		case VT_CLSID:				pszType = "VT_CLSID";			break;
		default:					ASSERT_FALSE();					break;
	}

	return pszType;
}

////////////////////////////////////////////////////////////////////////////////
//! Format the final variant type and any flags as a string. If the variant is
//! type VT_VARIANT|VT_BYREF, it gets the contained variants type.

CString Variant::FormatFullType(const VARIANT* pVariant)
{
	// Recurse, if just a reference to another variant.
	if (V_VT(pVariant) == (VT_VARIANT|VT_BYREF))
		pVariant = V_VARIANTREF(pVariant);

	VARTYPE eType = V_VT(pVariant);

	// Get the variants type.
	CString str = FormatType(eType);

	ushort nFlags = static_cast<ushort>(eType & (~VT_TYPEMASK));

	if (nFlags & VT_VECTOR)
		str += "|VT_VECTOR";

	if (nFlags & VT_ARRAY)
		str += "|VT_ARRAY";

	if (nFlags & VT_BYREF)
		str += "|VT_BYREF";

	return str;
}

//namespace WCL
}
