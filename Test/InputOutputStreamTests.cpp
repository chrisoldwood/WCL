////////////////////////////////////////////////////////////////////////////////
//! \file   InputOutputStreamTests.cpp
//! \brief  The unit tests for the IInputStream & IOutputStream operators.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/MemStream.hpp>
#include <WCL/Buffer.hpp>
#include <limits>

TEST_SET(InputOutputStream)
{

TEST_CASE("primitive values can be inserted and extracted from a stream")
{
	CBuffer	   buffer;
	CMemStream stream(buffer);

	stream.Create();

{
	WCL::IOutputStream& out = stream;

	out << std::numeric_limits<bool>::max();
	out << std::numeric_limits<int8>::max();
	out << std::numeric_limits<uint8>::max();
	out << std::numeric_limits<int16>::max();
	out << std::numeric_limits<uint16>::max();
	out << std::numeric_limits<int32>::max();
	out << std::numeric_limits<uint32>::max();
}

	stream.Close();
	stream.Open();

{
	bool   boolValue;
	int8   int8Value;
	uint8  uint8Value;
	int16  int16Value;
	uint16 uint16Value;
	int32  int32Value;
	uint32 uint32Value;

	WCL::IInputStream& in = stream;

	in >> boolValue;
	in >> int8Value;
	in >> uint8Value;
	in >> int16Value;
	in >> uint16Value;
	in >> int32Value;
	in >> uint32Value;

	TEST_TRUE(boolValue   == std::numeric_limits<bool>::max());
	TEST_TRUE(int8Value   == std::numeric_limits<int8>::max());
	TEST_TRUE(uint8Value  == std::numeric_limits<uint8>::max());
	TEST_TRUE(int16Value  == std::numeric_limits<int16>::max());
	TEST_TRUE(uint16Value == std::numeric_limits<uint16>::max());
	TEST_TRUE(int32Value  == std::numeric_limits<int32>::max());
	TEST_TRUE(uint32Value == std::numeric_limits<uint32>::max());
}

}
TEST_CASE_END

TEST_CASE("c-style string values can be inserted into a stream")
{
	const char*    ANSI_STRING = "unit test";
	const wchar_t* WIDE_STRING = L"unit test";

	CBuffer	   buffer;
	CMemStream stream(buffer);

	stream.Create();

{
	WCL::IOutputStream& out = stream;

	out << ANSI_STRING;
	out << WIDE_STRING;
}

	stream.Close();
	stream.Open();

{
	WCL::IInputStream& in = stream;

	uint32 stringLen;

	in >> stringLen;

	TEST_TRUE(stringLen == (strlen(ANSI_STRING)+1));

	std::vector<char> ansiStringValue(stringLen);
	const char*       ansiStringBuffer = &ansiStringValue[0];

	in.Read(const_cast<char*>(ansiStringBuffer), Core::numBytes<char>(stringLen));

	TEST_TRUE(strcmp(ansiStringBuffer, ANSI_STRING) == 0);

	in >> stringLen;

	TEST_TRUE(stringLen == (wcslen(WIDE_STRING)+1));

	std::vector<wchar_t> wideStringValue(stringLen);
	const wchar_t*       wideStringBuffer = &wideStringValue[0];

	in.Read(const_cast<wchar_t*>(wideStringBuffer), Core::numBytes<wchar_t>(stringLen));

	TEST_TRUE(wcscmp(wideStringBuffer, WIDE_STRING) == 0);
}

}
TEST_CASE_END

}
TEST_SET_END
