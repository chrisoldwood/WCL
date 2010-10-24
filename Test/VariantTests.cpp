////////////////////////////////////////////////////////////////////////////////
//! \file   TestVariant.cpp
//! \brief  The unit tests for the Variant class.
//! \author Chris Oldwood

#include "stdafx.h"
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

TEST_CASE(Variant, defaultConstruction)
{
	WCL::Variant variant;

	TEST_TRUE(V_VT(&variant) == VT_EMPTY);
}
TEST_CASE_END

TEST_CASE(Variant, constructionFromBool)
{
	WCL::Variant variant1(true);

	TEST_TRUE(V_VT(&variant1)   == VT_BOOL);
	TEST_TRUE(V_BOOL(&variant1) == VARIANT_TRUE);

	WCL::Variant variant2(false);

	TEST_TRUE(V_VT(&variant2)   == VT_BOOL);
	TEST_TRUE(V_BOOL(&variant2) == VARIANT_FALSE);
}
TEST_CASE_END

TEST_CASE(Variant, constructionFromInt32)
{
	WCL::Variant variant(int32Max);

	TEST_TRUE(V_VT(&variant) == VT_I4);
	TEST_TRUE(V_I4(&variant) == int32Max);
}
TEST_CASE_END

TEST_CASE(Variant, constructionFromUint32)
{
	WCL::Variant variant(uint32Max);

	TEST_TRUE(V_VT(&variant)  == VT_UI4);
	TEST_TRUE(V_UI4(&variant) == uint32Max);
}
TEST_CASE_END

TEST_CASE(Variant, constructionFromInt64)
{
	WCL::Variant variant(int64Max);

	TEST_TRUE(V_VT(&variant) == VT_I8);
	TEST_TRUE(V_I8(&variant) == int64Max);
}
TEST_CASE_END

TEST_CASE(Variant, constructionFromUint64)
{
	WCL::Variant variant(uint64Max);

	TEST_TRUE(V_VT(&variant)  == VT_UI8);
	TEST_TRUE(V_UI8(&variant) == uint64Max);
}
TEST_CASE_END

TEST_CASE(Variant, constructionFromWideString)
{
	WCL::Variant variant(L"Unit Test");

	TEST_TRUE(V_VT(&variant) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&variant), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE(Variant, constructionFromBSTR)
{
	WCL::ComStr  bstr(TXT("Unit Test"));
	WCL::Variant variant(bstr);

	TEST_TRUE(V_VT(&variant) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&variant), L"Unit Test") == 0);
	TEST_TRUE(bstr.Get() == nullptr);
}
TEST_CASE_END

TEST_CASE(Variant, constructionByCoercion)
{
	WCL::Variant longVariant;

	V_VT(&longVariant)  = VT_I4;
	V_INT(&longVariant) = 1234;

	WCL::Variant bstrVariant(longVariant, VT_BSTR);

	TEST_TRUE(V_VT(&bstrVariant) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&bstrVariant), L"1234") == 0);
}
TEST_CASE_END

TEST_CASE(Variant, copyConstruction)
{
	WCL::ComStr  bstr(TXT("Unit Test"));
	WCL::Variant variant(bstr);

	WCL::Variant copy(variant);

	TEST_TRUE(V_VT(&copy) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&copy), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE(Variant, assignment)
{
	WCL::ComStr  bstr(TXT("Unit Test"));
	WCL::Variant variant(bstr);

	WCL::Variant copy;

	V_VT(&copy)  = VT_I4;
	V_INT(&copy) = 1234;

	copy = variant;

	TEST_TRUE(V_VT(&copy) == VT_BSTR);
	TEST_TRUE(wcscmp(V_BSTR(&copy), L"Unit Test") == 0);
}
TEST_CASE_END

TEST_CASE(Variant, type)
{
	WCL::Variant variant(L"Unit Test");

	TEST_TRUE(variant.type() == VT_BSTR);
}
TEST_CASE_END

TEST_CASE(Variant, formatType)
{
	WCL::VariantVector<uint> safeArray(1, VT_UI4);

	safeArray[0] = 1234u;

	WCL::Variant variantArray;

	V_VT(&variantArray)    = VT_ARRAY|VT_UI4;
	V_ARRAY(&variantArray) = safeArray.Detach();

	TEST_TRUE(tstrcmp(WCL::Variant::formatType(V_VT(&variantArray)), TXT("VT_UI4")) == 0);
	TEST_TRUE(WCL::Variant::formatFullType(variantArray) == TXT("VT_UI4|VT_ARRAY"));
}
TEST_CASE_END

TEST_CASE(Variant, format)
{
	WCL::Variant variant1;

	TEST_TRUE(variant1.format() == TXT(""));

	WCL::Variant variant2(1234L);

	TEST_TRUE(variant2.format() == TXT("1234"));

	WCL::Variant variant3;

	V_VT(&variant3) = VT_NULL;

	TEST_TRUE(variant3.format() == TXT(""));

	WCL::Variant variant4(true);

	TEST_TRUE(variant4.format() == TXT("True"));

	WCL::Variant variant5(false);

	TEST_TRUE(variant5.format() == TXT("False"));
}
TEST_CASE_END

TEST_CASE(Variant, getValueAsTstring)
{
	WCL::Variant variant(L"Unit Test");

	TEST_TRUE(WCL::getValue<tstring>(variant) == TXT("Unit Test"));

	WCL::Variant empty;

	TEST_TRUE(WCL::getValue<tstring>(empty).empty());

	WCL::Variant number(1234UL);

	TEST_THROWS(WCL::getValue<tstring>(number));
}
TEST_CASE_END

TEST_CASE(Variant, getValueAsBool)
{
	WCL::Variant variant(true);

	TEST_TRUE(WCL::getValue<bool>(variant) == true);
}
TEST_CASE_END

TEST_CASE(Variant, getValueAsInteger)
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
