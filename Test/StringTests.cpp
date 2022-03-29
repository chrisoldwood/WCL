////////////////////////////////////////////////////////////////////////////////
//! \file   StringTests.cpp
//! \brief  The unit tests for the CString class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <Core/tiosfwd.hpp>
#include <sstream>
#include <WCL/StringIO.hpp>
#include <WCL/MemStream.hpp>
#include <WCL/Buffer.hpp>
#include <Core/AnsiWide.hpp>

#ifdef ANSI_BUILD
typedef wchar_t		otherchar_t;
#define O2T(string)	W2A(string)
#define OTXT(x)		L ## x
#define otherstrlen	wcslen
#else
typedef char		otherchar_t;
#define O2T(string)	A2W(string)
#define OTXT(x)		x
#define otherstrlen	strlen
#endif

TEST_SET(String)
{
	CString str = CString::Fmt(TXT("%s"), TXT("Hello World"));

TEST_CASE("[in]equality operator performs a case-sensitive comparison")
{
	TEST_TRUE(str == TXT("Hello World"));
	TEST_TRUE(str != TXT("hello world"));
}
TEST_CASE_END

TEST_CASE("less operator performs a case-sensitive comparison")
{
	TEST_FALSE(str < TXT("HELLO WORLD"));
	TEST_TRUE (str < TXT("hello world"));
	TEST_FALSE(str < TXT("Hello World"));

	TEST_FALSE(str < CString(TXT("HELLO WORLD")));
	TEST_TRUE (str < CString(TXT("hello world")));
	TEST_FALSE(str < CString(TXT("Hello World")));
}
TEST_CASE_END

TEST_CASE("stream inserter writes character sequence")
{
	CString value(TXT("unit test"));

	tostringstream out;

	out << value;

	TEST_TRUE(tstrstr(out.str().c_str(), value.c_str()) != nullptr);
}
TEST_CASE_END

TEST_CASE("an empty string can be inserted and extracted from a stream")
{
	const CString emptyValue(TXT(""));

	CBuffer	   buffer;
	CMemStream stream(buffer);

	stream.Create();

	WCL::IOutputStream& out = stream;

	out << emptyValue;

	stream.Close();
	stream.Open();

	WCL::IInputStream& in = stream;

	CString value;

	in >> value;

	TEST_TRUE(value.Length() == 0);
}
TEST_CASE_END

TEST_CASE("a non-empty string can be inserted and extracted from a stream")
{
	const CString testValue(TXT("unit test"));

	CBuffer	   buffer;
	CMemStream stream(buffer);

	stream.Create();

	WCL::IOutputStream& out = stream;

	out << testValue;

	stream.Close();
	stream.Open();

	WCL::IInputStream& in = stream;

	CString value;

	in >> value;

	TEST_TRUE(value.Length() == testValue.Length());
	TEST_TRUE(value == testValue);
}
TEST_CASE_END

TEST_CASE("a string is serialized to a stream based on its buffer capacity, not length")
{
	CString testValue(TXT("A very very very long string"));
	testValue = TXT("A short string");

	TEST_FALSE(testValue.Length()+1 == testValue.Capacity());

	CBuffer	   buffer;
	CMemStream stream(buffer);
	stream.Create();

	stream << testValue;

	stream.Close();

	TEST_TRUE(buffer.Size() == (sizeof(uint32) + Core::numBytes<tchar>(testValue.Capacity())));
}
TEST_CASE_END

TEST_CASE("a build dependent string can be written to a stream as the opposite string type")
{
	const otherchar_t* othercharString = OTXT("unit test");
	const CString tcharString(O2T(othercharString));

	CBuffer	   buffer;
	CMemStream stream(buffer);
	stream.Create();

	tcharString.WriteString<otherchar_t>(stream);

	stream.Close();

	TEST_TRUE(buffer.Size() == (sizeof(uint32) + Core::numBytes<otherchar_t>(tcharString.Capacity())));
	TEST_TRUE(memcmp(static_cast<const byte*>(buffer.Buffer()) + sizeof(uint32), othercharString, tcharString.Length()+1) == 0);
}
TEST_CASE_END

TEST_CASE("a build dependent string can be read from a stream of the opposite string type")
{
	const otherchar_t* othercharString = OTXT("unit test");
	const uint32 numChars =  otherstrlen(othercharString);
	CString tcharString;

	CBuffer    buffer;
	CMemStream stream(buffer);
	stream.Create();

	stream << numChars+1;
	stream.Write(othercharString, Core::numBytes<otherchar_t>(numChars+1));

	stream.Close();
	stream.Open();

	tcharString.ReadString<otherchar_t>(stream);

	stream.Close();

	TEST_TRUE(tcharString == O2T(othercharString));
}
TEST_CASE_END

}
TEST_SET_END
