////////////////////////////////////////////////////////////////////////////////
//! \file   IFacePtrTests.cpp
//! \brief  The unit tests for the IFacePtr class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/IFacePtr.hpp>
#include "PtrTest.hpp"

TEST_SET(IFacePtr)
{
	typedef WCL::IFacePtr<IPtrTest> ITestPtr;

TEST_CASE("compilation should succeed")
{
	ITestPtr pITest1;
//	ITestPtr pITest2 = new PtrTest;			// Shouldn't compile.
	ITestPtr pITest3 = ITestPtr(new PtrTest);
	ITestPtr pITest4(new PtrTest);
	ITestPtr pITest5(pITest3);

	TEST_TRUE(pITest1.get() == nullptr);
	TEST_TRUE(pITest3.get() != nullptr);
	TEST_TRUE(pITest4.get() != nullptr);
	TEST_TRUE(pITest5.get() != nullptr);

	TEST_PASSED("compilation succeeded");
}
TEST_CASE_END

TEST_CASE("initial state is a null pointer")
{
	ITestPtr test;

	TEST_TRUE(test.get() == nullptr);
}
TEST_CASE_END

TEST_CASE("construction with a pointer passes ownership")
{
	PtrTest* expected = new PtrTest;
	ITestPtr  test(expected);

	TEST_TRUE(test.get() == expected);
}
TEST_CASE_END

TEST_CASE("owned pointer can be accessed as a pointer or reference")
{
	PtrTest* expected = new PtrTest;
	ITestPtr  test(expected);

	TEST_TRUE(test.get() == &test.getRef());
}
TEST_CASE_END

TEST_CASE("retrieving reference when pointer is null throws an exception")
{
	ITestPtr test;

	TEST_THROWS(test.getRef());
}
TEST_CASE_END

TEST_CASE("operator -> returns owned pointer")
{
	ITestPtr test(new PtrTest);

	TEST_TRUE(test->Run());
}
TEST_CASE_END

TEST_CASE("operator -> throws when the owned pointer is null")
{
	ITestPtr test;

	TEST_THROWS(test->Run());
}
TEST_CASE_END

TEST_CASE("operator * returns owned pointer as a reference")
{
	ITestPtr test(new PtrTest);

	TEST_TRUE((*test).Run());
}
TEST_CASE_END

TEST_CASE("operator * throws when the owned pointer is null")
{
	ITestPtr test;

	TEST_THROWS((*test).Run());
}
TEST_CASE_END

TEST_CASE("not operator returns if the contained pointer is null or not")
{
	ITestPtr hasNullPtr;
	ITestPtr hasRealPtr(new PtrTest);

	TEST_TRUE(!hasNullPtr);
	TEST_FALSE(!hasRealPtr);
}
TEST_CASE_END

TEST_CASE("[in]equivalence operator compares two pointers")
{
	ITestPtr hasNullPtr;
	ITestPtr hasRealPtr(new PtrTest);

	TEST_TRUE(hasNullPtr == hasNullPtr);
	TEST_TRUE(hasNullPtr != hasRealPtr);
	TEST_TRUE(hasRealPtr == hasRealPtr);
}
TEST_CASE_END

TEST_CASE("reset empties the pointer when argument is null pointer")
{
	ITestPtr test(new PtrTest);

	test.Release();

	TEST_TRUE(test.get() == nullptr);
}
TEST_CASE_END

TEST_CASE("detach releases ownership of the pointer")
{
	PtrTest  value;
	PtrTest* expected = &value;

	ITestPtr test(expected);

	TEST_TRUE(test.get() == expected);

	test.Detach();

	TEST_TRUE(test.get() == nullptr);
}
TEST_CASE_END

TEST_CASE("smart pointer unaware functions can attach a pointer to an empty instance")
{
	ITestPtr test;

	PtrTest* expected = new PtrTest;

	*AttachTo(test) = expected;

	TEST_TRUE(test.get() == expected);
}
TEST_CASE_END

TEST_CASE("attaching a pointer to a non-empty smart pointer throws an exception")
{
	ITestPtr test(new PtrTest);

	TEST_THROWS(AttachTo(test));
}
TEST_CASE_END

TEST_CASE("the pointer is empty when it owns nothing")
{
	const ITestPtr test;

	TEST_TRUE(test.empty());
}
TEST_CASE_END

TEST_CASE("the pointer is not empty when it owns something")
{
	const ITestPtr test(new PtrTest);

	TEST_FALSE(test.empty());
}
TEST_CASE_END

}
TEST_SET_END
