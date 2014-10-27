////////////////////////////////////////////////////////////////////////////////
//! \file   PathTests.cpp
//! \brief  The unit tests for the CPath class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/Path.hpp>

TEST_SET(Path)
{

TEST_CASE("Initial state is an empty string")
{
	TEST_TRUE(CPath().Empty());
	TEST_TRUE(CPath().Length() == 0);
	TEST_TRUE(CPath() == TXT(""));
}
TEST_CASE_END

TEST_CASE("path can be constructed from a single path of various string types")
{
	TEST_TRUE(CPath(TXT("C:\\Temp")) == TXT("C:\\Temp"));
	TEST_TRUE(CPath(CString(TXT("C:\\Temp"))) == TXT("C:\\Temp"));
	TEST_TRUE(CPath(tstring(TXT("C:\\Temp"))) == TXT("C:\\Temp"));
}
TEST_CASE_END

TEST_CASE("path can be constructed from a folder and a file\folder name")
{
	TEST_TRUE(CPath(TXT("C:\\"), TXT("Temp")) == TXT("C:\\Temp"));
}
TEST_CASE_END

TEST_CASE("input paths are normalised to exclude the folder separator except for root paths")
{
	TEST_TRUE(CPath(TXT(".\\")) == TXT("."));
	TEST_TRUE(CPath(TXT("C:\\Temp\\")) == TXT("C:\\Temp"));

	TEST_TRUE(CPath(TXT("\\")) == TXT("\\"));
	TEST_TRUE(CPath(TXT("C:\\")) == TXT("C:\\"));
}
TEST_CASE_END

TEST_CASE("path can be assigned from a single path of various string types")
{
	CPath path;

	path = TXT("C:\\");
	TEST_TRUE(path == TXT("C:\\"));

	path = TXT("C:\\Temp\\");
	TEST_TRUE(path == TXT("C:\\Temp"));

	path = CString(TXT("C:\\Temp\\"));
	TEST_TRUE(path == TXT("C:\\Temp"));

	path = tstring(TXT("C:\\Temp\\"));
	TEST_TRUE(path == TXT("C:\\Temp"));
}
TEST_CASE_END

TEST_CASE("path can be implictly converted to various string types")
{
	CPath path(TXT("C:\\Temp"));

	const tchar* path_cstr = path;
	TEST_TRUE(tstrcmp(path_cstr, TXT("C:\\Temp")) == 0);

	CString path_cstring = path;
	TEST_TRUE(path_cstring == TXT("C:\\Temp"));

	tstring path_tstring(path);
	TEST_TRUE(path_tstring == TXT("C:\\Temp"));
}
TEST_CASE_END

TEST_CASE("the entire path without the file extension can be retrieved")
{
	CPath fullPathWithExtension(TXT("C:\\Folder\\File.Ext"));

	TEST_TRUE(fullPathWithExtension.PathWithoutExt() == TXT("C:\\Folder\\File"));

	CPath filenameWithNoExtension(TXT("File"));

	TEST_TRUE(filenameWithNoExtension.PathWithoutExt() == TXT("File"));
}
TEST_CASE_END

}
TEST_SET_END
