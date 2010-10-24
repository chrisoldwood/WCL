////////////////////////////////////////////////////////////////////////////////
//! \file   TestComPtr.cpp
//! \brief  The unit tests for the ComPtr class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ComPtr.hpp>
#include <WCL/AutoCom.hpp>
#include <shlobj.h>
#include <shlguid.h>
#include "TestIFaceTraits.hpp"

TEST_SET(ComPtr)
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

	TEST_TRUE(pTest1.get() == nullptr);

	::CoGetMalloc(1, AttachTo(pTest1));

	TEST_TRUE(pTest1.get() != nullptr);

//	IMallocPtr pTest2 = pMalloc1;		// Shouldn't compile.

	IMallocPtr pTest3(pMalloc1);

	TEST_TRUE(pTest3.get() == pMalloc1);

	pTest3 = pTest3;

	TEST_TRUE(pTest3.get() == pMalloc1);

	IMallocPtr pTest4(pTest1);

	TEST_TRUE(pTest4.get() == pTest1.get());

	pTest4 = pTest1;

	TEST_TRUE(pTest4.get() == pTest1.get());

	IFaceOnlyPtr pMalloc2;

	::CoGetMalloc(1, AttachTo(pMalloc2));

	ASSERT(pMalloc2.get() != nullptr);

	IMallocPtr pTest5(pMalloc2);

	TEST_TRUE(pTest5.get() == pMalloc2.get());

	pTest5 = pMalloc2;

	TEST_TRUE(pTest5.get() == pMalloc2.get());

	IUnknownPtr pUnknown(pMalloc2);

	TEST_TRUE(pUnknown.get() != nullptr);

	pUnknown.QueryInterface(pMalloc2);

	TEST_TRUE(pUnknown.get() != nullptr);

	IClassFactoryPtr pFactory;

	TEST_THROWS(pFactory.QueryInterface(pMalloc2));

	IUnknownPtr pShell(CLSID_ShellDesktop);

	TEST_TRUE(pShell.get() != nullptr);

	pShell.Release();

	TEST_TRUE(pShell.get() == nullptr);

	pShell.CreateInstance(CLSID_ShellDesktop);

	TEST_TRUE(pShell.get() != nullptr);

	pShell.Release();
}
TEST_SET_END
