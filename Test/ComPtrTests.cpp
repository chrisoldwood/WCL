////////////////////////////////////////////////////////////////////////////////
//! \file   ComPtrTests.cpp
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

TEST_CASE("initial state is a null pointer")
{
	IMallocPtr test;

	TEST_TRUE(test.get() == nullptr);
}
TEST_CASE_END

TEST_CASE("releasing a null pointer is benign")
{
	IUnknownPtr test;

	test.Release();

	TEST_TRUE(test.get() == nullptr);
}
TEST_CASE_END

TEST_CASE("smart pointer unaware functions can attach a pointer to an empty instance")
{
	IMallocPtr test;

	::CoGetMalloc(1, AttachTo(test));

	TEST_TRUE(test.get() != nullptr);
}
TEST_CASE_END

TEST_CASE("construction with a pointer passes ownership")
{
	IMalloc* expected = nullptr;

	::CoGetMalloc(1, &expected);

	IMallocPtr test(expected);

	TEST_TRUE(test.get() == expected);
}
TEST_CASE_END

TEST_CASE("assigment shares ownership")
{
	IMalloc* expected = nullptr;

	::CoGetMalloc(1, &expected);

	IMallocPtr original(expected), copy;

	TEST_TRUE(copy.get() == nullptr);

	copy = original;

	TEST_TRUE(copy.get() == expected);
}
TEST_CASE_END

TEST_CASE("construction is possible from an IFacePtr")
{
	IFaceOnlyPtr iface;

	::CoGetMalloc(1, AttachTo(iface));

	IMallocPtr test(iface);

	TEST_TRUE(test.get() == iface.get());
}
TEST_CASE_END

TEST_CASE("assignment is possible from an IFacePtr")
{
	IFaceOnlyPtr iface;

	::CoGetMalloc(1, AttachTo(iface));

	IMallocPtr copy;

	copy = iface;

	TEST_TRUE(copy.get() == iface.get());
}
TEST_CASE_END

TEST_CASE("construction from a different interface requires the object to support that interface")
{
	IFaceOnlyPtr iface;

	::CoGetMalloc(1, AttachTo(iface));

	IUnknownPtr unknown(iface);

	TEST_TRUE(unknown.get() != nullptr);
}
TEST_CASE_END

TEST_CASE("a pointer can acquire its object by querying another object for a different interface")
{
	IFaceOnlyPtr iface;

	::CoGetMalloc(1, AttachTo(iface));

	IUnknownPtr unknown;

	unknown.QueryInterface(iface);

	TEST_TRUE(unknown.get() != nullptr);
}
TEST_CASE_END

TEST_CASE("acquiring an unsupported interface throws an exception")
{
	IFaceOnlyPtr iface;

	::CoGetMalloc(1, AttachTo(iface));

	IClassFactoryPtr factory;

	TEST_THROWS(factory.QueryInterface(iface));
}
TEST_CASE_END

TEST_CASE("a COM object can be created through construction via its CLSID")
{
	IUnknownPtr test(CLSID_ShellDesktop);

	TEST_TRUE(test.get() != nullptr);
}
TEST_CASE_END

TEST_CASE("a COM object can be explictly created via its CLSID")
{
	IUnknownPtr test;

	test.CreateInstance(CLSID_ShellDesktop);

	TEST_TRUE(test.get() != nullptr);
}
TEST_CASE_END

TEST_CASE("explicitly releasing a pointer removes ownership")
{
	IUnknownPtr test(CLSID_ShellDesktop);

	test.Release();

	TEST_TRUE(test.get() == nullptr);
}
TEST_CASE_END

}
TEST_SET_END
