////////////////////////////////////////////////////////////////////////////////
//! \file   Variant.cpp
//! \brief  The Variant class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Variant.hpp"
#include "ComException.hpp"
#include <Core/StringUtils.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Variant::Variant()
{
	::VariantInit(this);
}

////////////////////////////////////////////////////////////////////////////////
//! Construction by creating a BSTR of the string.

Variant::Variant(const wchar_t* pszValue)
{
	::VariantInit(this);

	V_VT(this)   = VT_BSTR;
	V_BSTR(this) = ::SysAllocString(pszValue);
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
		throw ComException(hr, Core::Fmt(TXT("Failed to convert a variant from %s to %s"),
				FormatFullType(&vtVariant).c_str(), FormatType(eType)).c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Variant::~Variant()
{
	::VariantClear(this);
}

////////////////////////////////////////////////////////////////////////////////
//! Format the variant type as a string.

const tchar* Variant::FormatType(VARTYPE eType)
{
	const tchar* pszType = TXT("");

	switch (eType & VT_TYPEMASK)
	{
		case VT_EMPTY:				pszType = TXT("VT_EMPTY");			break;
		case VT_NULL:				pszType = TXT("VT_NULL");			break;
		case VT_I2:					pszType = TXT("VT_I2");				break;
		case VT_I4:					pszType = TXT("VT_I4");				break;
		case VT_R4:					pszType = TXT("VT_R4");				break;
		case VT_R8:					pszType = TXT("VT_R8");				break;
		case VT_CY:					pszType = TXT("VT_CY");				break;
		case VT_DATE:				pszType = TXT("VT_DATE");			break;
		case VT_BSTR:				pszType = TXT("VT_BSTR");			break;
		case VT_DISPATCH:			pszType = TXT("VT_DISPATCH");		break;
		case VT_ERROR:				pszType = TXT("VT_ERROR");			break;
		case VT_BOOL:				pszType = TXT("VT_BOOL");			break;
		case VT_VARIANT:			pszType = TXT("VT_VARIANT");			break;
		case VT_UNKNOWN:			pszType = TXT("VT_UNKNOWN");			break;
		case VT_DECIMAL:			pszType = TXT("VT_DECIMAL");			break;
		case VT_I1:					pszType = TXT("VT_I1");				break;
		case VT_UI1:				pszType = TXT("VT_UI1");				break;
		case VT_UI2:				pszType = TXT("VT_UI2");				break;
		case VT_UI4:				pszType = TXT("VT_UI4");				break;
		case VT_I8:					pszType = TXT("VT_I8");				break;
		case VT_UI8:				pszType = TXT("VT_UI8");				break;
		case VT_INT:				pszType = TXT("VT_INT");				break;
		case VT_UINT:				pszType = TXT("VT_UINT");			break;
		case VT_VOID:				pszType = TXT("VT_VOID");			break;
		case VT_HRESULT:			pszType = TXT("VT_HRESULT");			break;
		case VT_PTR:				pszType = TXT("VT_PTR");				break;
		case VT_SAFEARRAY:			pszType = TXT("VT_SAFEARRAY");		break;
		case VT_CARRAY:				pszType = TXT("VT_CARRAY");			break;
		case VT_USERDEFINED:		pszType = TXT("VT_USERDEFINED");		break;
		case VT_LPSTR:				pszType = TXT("VT_LPSTR");			break;
		case VT_LPWSTR:				pszType = TXT("VT_LPWSTR");			break;
		case VT_FILETIME:			pszType = TXT("VT_FILETIME");		break;
		case VT_BLOB:				pszType = TXT("VT_BLOB");			break;
		case VT_STREAM:				pszType = TXT("VT_STREAM");			break;
		case VT_STORAGE:			pszType = TXT("VT_STORAGE");			break;
		case VT_STREAMED_OBJECT:	pszType = TXT("VT_STREAMED_OBJECT");	break;
		case VT_STORED_OBJECT:		pszType = TXT("VT_STORED_OBJECT");	break;
		case VT_BLOB_OBJECT:		pszType = TXT("VT_BLOB_OBJECT");		break;
		case VT_CF:					pszType = TXT("VT_CF");				break;
		case VT_CLSID:				pszType = TXT("VT_CLSID");			break;
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
		str += TXT("|VT_VECTOR");

	if (nFlags & VT_ARRAY)
		str += TXT("|VT_ARRAY");

	if (nFlags & VT_BYREF)
		str += TXT("|VT_BYREF");

	return str;
}

//namespace WCL
}
