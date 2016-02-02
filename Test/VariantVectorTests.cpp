////////////////////////////////////////////////////////////////////////////////
//! \file   VariantVectorTests.cpp
//! \brief  The unit tests for the VariantVector class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/VariantVector.hpp>
#include <Core/Scoped.hpp>

static void destroySafeArray(SAFEARRAY* safeArray)
{
	::SafeArrayDestroy(safeArray);
}

TEST_SET(VariantVector)
{
	typedef Core::Scoped<SAFEARRAY*> SafeArrayPtr;

TEST_CASE("construction from a size and type results in a vector of that size")
{
	WCL::VariantVector<long> vector(10, VT_I4);

	TEST_TRUE(vector.Size() == 10);
}
TEST_CASE_END

TEST_CASE("detaching the underlying safe array resets the vector")
{
	WCL::VariantVector<long> vector(10, VT_I4);

	SafeArrayPtr safeArray(destroySafeArray, vector.Detach());

	TEST_TRUE(safeArray.get() != nullptr);
	TEST_TRUE(vector.Size() == 0);
}
TEST_CASE_END

TEST_CASE("construction from a safearray transfers ownership by default")
{
	WCL::VariantVector<long> original(10, VT_I4);

	SAFEARRAY* array = original.Detach();

	{
		WCL::VariantVector<long> newOwner(array, VT_I4);

		TEST_TRUE(newOwner.Size() == 10);
	}

#ifdef _MSC_VER
	if (::IsDebuggerPresent())
	{
		// Sniffing the destroyed array! This only seems to work
		// if the debugger is attached (debug Windows heap enabled?)
		TEST_TRUE(array->cDims != 1);
		TEST_TRUE(array->cbElements != 4);
	}
	else
	{
		TEST_PASSED("No error thrown");
	}
#else
	TEST_PASSED("No error thrown");
#endif
}
TEST_CASE_END

TEST_CASE("construction from a safearray with ownership retained creates a view")
{
	WCL::VariantVector<long> original(10, VT_I4);

	SAFEARRAY* array = original.Detach();

	{
		WCL::VariantVector<long> newOwner(array, VT_I4, false);

		TEST_TRUE(newOwner.Size() == 10);
	}

	TEST_TRUE(array->cDims == 1);
	TEST_TRUE(array->cbElements == 4);

	destroySafeArray(array);

#ifdef _MSC_VER
	if (::IsDebuggerPresent())
	{
		// Sniffing the destroyed array! This only seems to work
		// if the debugger is attached (debug Windows heap enabled?)
		TEST_TRUE(array->cDims != 1);
		TEST_TRUE(array->cbElements != 4);
	}
	else
	{
		TEST_PASSED("No error thrown");
	}
#else
	TEST_PASSED("No error thrown");
#endif
}
TEST_CASE_END

TEST_CASE("a const instance returns const iterators")
{
	typedef WCL::VariantVector<long> LongVector;

	const LongVector vector(1, VT_I4);

	LongVector::const_iterator it  = vector.begin();
	LongVector::const_iterator end = vector.end();

	TEST_TRUE(it != end);

	++it;

//	*it = 1234;		// Shouldn't compile.

	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("a non-const instance returns non-const iterators")
{
	typedef WCL::VariantVector<long> LongVector;

	LongVector vector(1, VT_I4);

	LongVector::iterator it  = vector.begin();
	LongVector::iterator end = vector.end();

	TEST_PASSED("passed");
	TEST_TRUE(it != end);

	++it;

	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("the const indexing operator returns a const reference to the element")
{
	typedef WCL::VariantVector<long> LongVector;

	const LongVector vector(1, VT_I4);

//	vector[0] = 1234;   // Shouldn't compile.

	TEST_TRUE(vector[0] == 0);
}
TEST_CASE_END

TEST_CASE("the non-const indexing operator returns a non-const reference to the element")
{
	typedef WCL::VariantVector<long> LongVector;

	LongVector vector(1, VT_I4);

	vector[0] = 1234;

	TEST_TRUE(vector[0] == 1234);
}
TEST_CASE_END

}
TEST_SET_END
