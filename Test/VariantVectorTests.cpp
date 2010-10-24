////////////////////////////////////////////////////////////////////////////////
//! \file   VariantVectorTests.cpp
//! \brief  The unit tests for the VariantVector class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/VariantVector.hpp>
#include <Core/Scoped.hpp>

TEST_SET(VariantVector)
{

TEST_CASE("construction")
{
	WCL::VariantVector<long> vector1(10, VT_I4);

	TEST_TRUE(vector1.Size() == 10);

	SAFEARRAY* raw = vector1.Detach();

	TEST_TRUE(raw != nullptr);

	WCL::VariantVector<long> vector2(raw, VT_I4);

	TEST_TRUE(vector2.Size() == 10);
}
TEST_CASE_END

TEST_CASE("constIteration")
{
	typedef WCL::VariantVector<long> LongVector;

	const LongVector vector(1, VT_I4);

	LongVector::const_iterator it  = vector.begin();
	LongVector::const_iterator end = vector.end();

	TEST_TRUE(it != end);
	++it;
	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("nonconstIteration")
{
	typedef WCL::VariantVector<long> LongVector;

	LongVector vector(1, VT_I4);

	LongVector::iterator it  = vector.begin();
	LongVector::iterator end = vector.end();

	TEST_TRUE(it != end);
	++it;
	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("indexingOperator")
{
	typedef WCL::VariantVector<long> LongVector;

	LongVector vector1(1, VT_I4);

	vector1[0] = 1234;

	const LongVector vector2(vector1.Detach(), VT_I4);

	TEST_TRUE(vector2[0] == 1234);
}
TEST_CASE_END

}
TEST_SET_END
