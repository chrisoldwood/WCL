////////////////////////////////////////////////////////////////////////////////
//! \file   VariantTests.cpp
//! \brief  The unit tests for the Variant class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/Variant.hpp>
#include <WCL/VariantVector.hpp>
#include <limits>

TEST_SET(Variant)
{
	const int32		int32Max  = std::numeric_limits<int32>::max();
	const uint32	uint32Max = std::numeric_limits<uint32>::max();
	const int64		int64Max  = std::numeric_limits<int64>::max();
	const uint64	uint64Max = std::numeric_limits<uint64>::max();

TEST_CASE("initial state is empty")
{
	WCL::Variant variant;

	TEST_TRUE(V_VT(&variant) == VT_EMPTY);
}
TEST_CASE_END

TEST_CASE("construction from C++ bool converts to a variant bool")
{
	WCL::Variant variant1(true);

	TEST_TRUE(V_VT(&variant1)   == VT_BOOL);
	TEST_TRUE(V_BOOL(&variant1) == VARIANT_TRUE);

	WCL::Variant variant2(false);

	TEST_TRUE(V_VT(&variant2)   == VT_BOOL);
	TEST_TRUE(V_BOOL(&variant2) == VARIANT_FALSE);
}
TEST_CASE_END

TEST_CASE("can be constructed from a signed integer")
{
	WCL::Variant variant(int32Max);

	TEST_TRUE(V_VT(&variant) == VT_I4);
	TEST_TRUE(V_I4(&variant) == int32Max);
}
TEST_CASE_END

TEST_CASE("can be constructed from an unsigned integer")
{
	WCL::Variant variant(uint32Max);

	TEST_TRUE(V_VT(&variant)  == VT_UI4);
	TEST_TRUE(V_UI4(&variant) == uint32Max);
}
TEST_CASE_END

TEST_CASE("can be constructed from a 64-bit signed integer")
{
	WCL::Variant variant(int64Max);

	TEST_TRUE(V_VT(&variant) == VT_I8);
	TEST_TRUE(V_I8(&variant) == int64Max);
}
TEST_CASE_END

TEST_CASE("can be constructed from a 64-but unsigned integer")
{
	WCL::Variant variant(uint64Max);

	TEST_TRUE(V_VT(&variant)  == VT_UI8);
	TEST_TRUE(V_UI8(&variant) == uint64Max);
}
TEST_CASE_END

TEST_CASE("can be constructed from a Unicode string")
{
	WCL::Variant variant(L"Unit Test");

	TEST_TRUE(V_VT(&variant) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&variant), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE("can be constructed from a BSTR")
{
	WCL::ComStr  bstr(TXT("Unit Test"));
	WCL::Variant variant(bstr);

	TEST_TRUE(V_VT(&variant) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&variant), L"Unit Test") == 0);
	TEST_TRUE(bstr.Get() == nullptr);
}
TEST_CASE_END

TEST_CASE("construction from another value and different type performs conversion of the value")
{
	WCL::Variant longVariant;

	V_VT(&longVariant) = VT_I4;
	V_I4(&longVariant) = 1234;

	WCL::Variant bstrVariant(longVariant, VT_BSTR);

	TEST_TRUE(V_VT(&bstrVariant) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&bstrVariant), L"1234") == 0);
}
TEST_CASE_END

TEST_CASE("construction from a value and an incompatible type throws an exception")
{
	WCL::Variant longVariant;

	V_VT(&longVariant) = VT_I4;
	V_I4(&longVariant) = 1234;

	TEST_THROWS(WCL::Variant(longVariant, VT_I1));
}
TEST_CASE_END

TEST_CASE("construction from another value creates a deep copy")
{
	WCL::ComStr  bstr(TXT("Unit Test"));
	WCL::Variant variant(bstr);

	WCL::Variant copy(variant);

	TEST_TRUE(V_VT(&copy) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&copy), L"Unit Test") == 0);
	TEST_TRUE(V_BSTR(&copy) != V_BSTR(&variant));
}
TEST_CASE_END

TEST_CASE("assignment replaces the value with another of a potentially different underlying type")
{
	WCL::ComStr  bstr(TXT("Unit Test"));
	WCL::Variant variant(bstr);

	WCL::Variant copy;

	V_VT(&copy) = VT_I4;
	V_I4(&copy) = 1234;

	copy = variant;

	TEST_TRUE(V_VT(&copy) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&copy), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE("the raw variant type can be queried")
{
	WCL::Variant variant(L"Unit Test");

	TEST_TRUE(variant.type() == VT_BSTR);
}
TEST_CASE_END

TEST_CASE("the element data type of an array can queried")
{
	WCL::VariantVector<uint> safeArray(1, VT_UI4);

	WCL::Variant variantArray;

	V_VT(&variantArray)    = VT_ARRAY|VT_UI4;
	V_ARRAY(&variantArray) = safeArray.Detach();

	TEST_TRUE(variantArray.type() == (VT_ARRAY|VT_UI4));
	TEST_TRUE(variantArray.valueType() == VT_UI4);
}
TEST_CASE_END

TEST_CASE("formatting the variant type only includes the value type")
{
	TEST_TRUE(tstrcmp(WCL::Variant::formatType(VT_UI4), TXT("VT_UI4")) == 0);
}
TEST_CASE_END

TEST_CASE("formatting the full variant type includes the value type and flags")
{
	WCL::VariantVector<uint> safeArray(1, VT_UI4);

	safeArray[0] = 1234u;

	WCL::Variant variantArray;

	V_VT(&variantArray)    = VT_ARRAY|VT_UI4;
	V_ARRAY(&variantArray) = safeArray.Detach();

	TEST_TRUE(WCL::Variant::formatFullType(variantArray) == TXT("VT_UI4|VT_ARRAY"));
}
TEST_CASE_END

TEST_CASE("formatting a null or empty variant converts it to an empty string")
{
	WCL::Variant variant;

	TEST_TRUE(variant.format() == TXT(""));

	V_VT(&variant) = VT_NULL;

	TEST_TRUE(variant.format() == TXT(""));
}
TEST_CASE_END

TEST_CASE("formatting a numeric variant converts it to a string")
{
	WCL::Variant variant(1234L);

	TEST_TRUE(variant.format() == TXT("1234"));
}
TEST_CASE_END

TEST_CASE("formatting a boolean variant converts it to a 'True' or 'False' string")
{
	WCL::Variant variantTrue(true);

	TEST_TRUE(variantTrue.format() == TXT("True"));

	WCL::Variant variantFalse(false);

	TEST_TRUE(variantFalse.format() == TXT("False"));
}
TEST_CASE_END

TEST_CASE("querying a string variant for it's string value returns the string")
{
	WCL::Variant variant(L"Unit Test");

	TEST_TRUE(WCL::getValue<tstring>(variant) == TXT("Unit Test"));
}
TEST_CASE_END

TEST_CASE("querying an empty variant for it's string value returns an empty string")
{
	WCL::Variant empty;

	TEST_TRUE(WCL::getValue<tstring>(empty).empty());
}
TEST_CASE_END

TEST_CASE("querying a non-string variant for it's string value throws an exception")
{
	WCL::Variant number(1234UL);

	TEST_THROWS(WCL::getValue<tstring>(number));
}
TEST_CASE_END

TEST_CASE("querying a boolean variant for it's boolean value returns a C++ boolean value")
{
	WCL::Variant variant(true);

	TEST_TRUE(WCL::getValue<bool>(variant) == true);
}
TEST_CASE_END

TEST_CASE("querying a numeric variant for it's numeric value returns the value")
{
	WCL::Variant varInt32(int32Max);
	WCL::Variant varUint32(uint32Max);
	WCL::Variant varInt64(int64Max);
	WCL::Variant varUint64(uint64Max);

	TEST_TRUE(WCL::getValue<int32>(varInt32) == int32Max);

	TEST_TRUE(WCL::getValue<uint32>(varUint32) == uint32Max);

	TEST_TRUE(WCL::getValue<int64>(varInt32) == int32Max);
	TEST_TRUE(WCL::getValue<int64>(varUint32) == uint32Max);
	TEST_TRUE(WCL::getValue<int64>(varInt64) == int64Max);

	TEST_TRUE(WCL::getValue<uint64>(varUint32) == uint32Max);
	TEST_TRUE(WCL::getValue<uint64>(varUint64) == uint64Max);
}
TEST_CASE_END

}
TEST_SET_END
