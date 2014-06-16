////////////////////////////////////////////////////////////////////////////////
//! \file   MemStreamTests.cpp
//! \brief  The unit tests for the MemStream class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/MemStream.hpp>
#include <WCL/Buffer.hpp>
#include <Core/ArrayPtr.hpp>

TEST_SET(MemStream)
{

TEST_CASE("a stream is empty when the underlying buffer is empty")
{
	CBuffer	   buffer;
	CMemStream stream(buffer);

	TEST_TRUE(stream.Size() == 0);
}
TEST_CASE_END

TEST_CASE("a stream has the same size as the underlying buffer")
{
	CBuffer	   buffer(100);
	CMemStream stream(buffer);

	TEST_TRUE(stream.Size() == buffer.Size());
}
TEST_CASE_END

TEST_CASE("writing to a stream writes to the underlying buffer")
{
	CBuffer	   buffer;
	CMemStream stream(buffer);

	const char* testValue = "unit test";

	stream.Create();
	stream.Write(testValue, strlen(testValue));
	stream.Close();

	TEST_TRUE(buffer.Size() == strlen(testValue));
	TEST_TRUE(memcmp(buffer.Buffer(), testValue, strlen(testValue)) == 0);
}
TEST_CASE_END

TEST_CASE("reading from a stream reads from the underlying buffer")
{
	const char* testValue = "unit test";

	CBuffer	   buffer(testValue, strlen(testValue));
	CMemStream stream(buffer);

	Core::ArrayPtr<char> readValue(new char[strlen(testValue)]);

	stream.Open();
	stream.Read(readValue.get(), buffer.Size());
	stream.Close();

	TEST_TRUE(memcmp(readValue.get(), testValue, strlen(testValue)) == 0);
}
TEST_CASE_END

}
TEST_SET_END
