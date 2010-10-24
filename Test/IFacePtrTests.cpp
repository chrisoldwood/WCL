////////////////////////////////////////////////////////////////////////////////
//! \file   IFacePtrTests.cpp
//! \brief  The unit tests for the IFacePtr class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/IFacePtr.hpp>
#include "PtrTest.hpp"

TEST_SET(IFacePtr)
{
	typedef WCL::IFacePtr<IPtrTest> ITestPtr;

	ITestPtr pITest1;
//	ITestPtr pITest2 = new PtrTest;			// Shouldn't compile.
	ITestPtr pITest3 = ITestPtr(new PtrTest);
	ITestPtr pITest4(new PtrTest);
	ITestPtr pITest5(pITest3);

	TEST_TRUE(pITest1.get() == nullptr);
	TEST_TRUE(pITest3.get() != nullptr);
	TEST_TRUE(pITest4.get() != nullptr);
	TEST_TRUE(pITest5.get() != nullptr);

	pITest1 = pITest3;
	pITest1 = pITest1;
//	IPtrTest* pIRaw = pITest1;				// Shouldn't compile.

	TEST_TRUE(pITest1.get() == pITest3.get());

	pITest1->Run();
	(*pITest1).Run();

//	TEST_FALSE((pITest1 == NULL) || (pITest1 != NULL));	// Shouldn't compile.
	TEST_FALSE(!pITest1);

	TEST_TRUE(pITest1 == pITest3);
	TEST_TRUE(pITest1 != pITest4);

	pITest1.Release();

	TEST_TRUE(pITest1.get() == nullptr);

	delete pITest4.Detach();

	TEST_TRUE(pITest4.get() == nullptr);

//	delete pTest1;	// Shouldn't compile.
}
TEST_SET_END
