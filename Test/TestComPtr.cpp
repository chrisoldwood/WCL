////////////////////////////////////////////////////////////////////////////////
//! \file   TestComPtr.cpp
//! \brief  The unit tests for the ComPtr class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ComPtr.hpp>
#include <WCL/AutoCom.hpp>
#include <shlobj.h>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the ComPtr class.

void TestComPtr()
{
	typedef WCL::ComPtr<IMalloc> IMallocPtr;
	typedef WCL::IFacePtr<IMalloc> IFaceOnlyPtr;
	typedef WCL::ComPtr<IUnknown> IUnknownPtr;
	typedef WCL::ComPtr<IClassFactory> IClassFactoryPtr;

	WCL::AutoCom oAutoCom(COINIT_APARTMENTTHREADED);

	IMalloc* pMalloc1 = nullptr;

	::CoGetMalloc(1, &pMalloc1);

	ASSERT(pMalloc1 != nullptr);

	IMallocPtr pTest1;

	TEST_TRUE(pTest1.Get() == nullptr);

	::CoGetMalloc(1, AttachTo(pTest1));

	TEST_TRUE(pTest1.Get() != nullptr);

//	IMallocPtr pTest2 = pMalloc1;		// Shouldn't compile.

	IMallocPtr pTest3(pMalloc1);

	TEST_TRUE(pTest3.Get() == pMalloc1);

	pTest3 = pTest3;

	TEST_TRUE(pTest3.Get() == pMalloc1);

	IMallocPtr pTest4(pTest1);

	TEST_TRUE(pTest4.Get() == pTest1.Get());

	pTest4 = pTest1;

	TEST_TRUE(pTest4.Get() == pTest1.Get());

	IFaceOnlyPtr pMalloc2;

	::CoGetMalloc(1, AttachTo(pMalloc2));

	ASSERT(pMalloc2.Get() != nullptr);

	IMallocPtr pTest5(pMalloc2);

	TEST_TRUE(pTest5.Get() == pMalloc2.Get());

	pTest5 = pMalloc2;

	TEST_TRUE(pTest5.Get() == pMalloc2.Get());

	IUnknownPtr pUnknown(pMalloc2);

	TEST_TRUE(pUnknown.Get() != nullptr);

	pUnknown.QueryInterface(pMalloc2);

	TEST_TRUE(pUnknown.Get() != nullptr);

	IClassFactoryPtr pFactory;

	TEST_THROWS(pFactory.QueryInterface(pMalloc2));

	IUnknownPtr pShell(CLSID_Shell);

	TEST_TRUE(pShell.Get() != nullptr);

	pShell.Release();

	TEST_TRUE(pShell.Get() == nullptr);

	pShell.CreateInstance(CLSID_Shell);

	TEST_TRUE(pShell.Get() != nullptr);

	pShell.Release();
}
