////////////////////////////////////////////////////////////////////////////////
//! \file   FolderIteratorTests.cpp
//! \brief  The unit tests for the FolderIterator class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/FolderIterator.hpp>
#include <WCL/Path.hpp>
#include <WCL/File.hpp>

static const tchar* TEST_FOLDER_1 = TXT("Test-Folder-1");
static const tchar* TEST_FOLDER_2 = TXT("Test-Folder-2");
static const tchar* TEST_FILE_1   = TXT("Test-File-1.txt");

static const CPath strTempDir = CPath::TempDir();
static const CPath strFolder1 = strTempDir / TXT("FolderIteratorTests");
static const CPath strFolder2 = strTempDir / TXT("FolderIteratorTests") / TEST_FOLDER_1;
static const CPath strFolder3 = strTempDir / TXT("FolderIteratorTests") / TEST_FOLDER_2;
static const CPath strFile    = strTempDir / TXT("FolderIteratorTests") / TEST_FILE_1;

TEST_SET(FolderIterator)
{

TEST_CASE_SETUP()
{
	ASSERT(!strFolder1.Exists());
	ASSERT(!strFolder2.Exists());
	ASSERT(!strFile.Exists());
}
TEST_CASE_SETUP_END

TEST_CASE_TEARDOWN()
{
	CFile::Delete(strFile);
	CFile::DeleteFolder(strFolder3);
	CFile::DeleteFolder(strFolder2);
	CFile::DeleteFolder(strFolder1);
}
TEST_CASE_TEARDOWN_END

TEST_CASE("an end iterator is comparable to itself")
{
	WCL::FolderIterator end;

	TEST_TRUE(WCL::FolderIterator() == end);
	TEST_FALSE(WCL::FolderIterator() != end);
}
TEST_CASE_END

TEST_CASE("dereferencing an end iterator throws an exception")
{
	WCL::FolderIterator end;

	TEST_THROWS(*end);
}
TEST_CASE_END

TEST_CASE("advancing an end iterator throws an exception")
{
	WCL::FolderIterator end;

	TEST_THROWS(++end);
}
TEST_CASE_END

TEST_CASE("iterating a folder that does not exist throws an exception")
{
	TEST_THROWS(WCL::FolderIterator(tstring(strFolder1), TXT("*.txt")));
}
TEST_CASE_END

TEST_CASE("iterating an empty folder returns an iterator to the end of the sequence")
{
	CFile::CreateFolder(strFolder1);

	tstring strFolder(strFolder1);

	WCL::FolderIterator it1(strFolder);
	WCL::FolderIterator end;

	TEST_TRUE(it1 == end);

	WCL::FolderIterator it2(strFolder, TXT("*.txt"));

	TEST_TRUE(it2 == end);
	TEST_TRUE(tstricmp(it2.Folder().c_str(), strFolder1) == 0);
	TEST_TRUE(tstricmp(it2.Mask().c_str(), TXT("*.txt")) == 0);
}
TEST_CASE_END

TEST_CASE("iterating a non-empty folder finds files and folders by default")
{
	CFile::CreateFolder(strFolder1);
	CFile::CreateFolder(strFolder2);
	CFile::WriteTextFile(strFile, CString(TXT("lorem ipsum")), ANSI_TEXT);

	bool bSeenFolder = false;
	bool bSeenFile = false;

	tstring strFolder(strFolder1);

	for (WCL::FolderIterator it(strFolder), end; it != end; ++it)
	{
		if (tstricmp(*it, TEST_FOLDER_1) == 0)
			bSeenFolder = true;

		if (tstricmp(*it, TEST_FILE_1) == 0)
			bSeenFile = true;
	}

	TEST_TRUE(bSeenFolder);
	TEST_TRUE(bSeenFile);
}
TEST_CASE_END

TEST_CASE("explicitly iterating folders should skip files")
{
	CFile::CreateFolder(strFolder1);
	CFile::CreateFolder(strFolder2);
	CFile::WriteTextFile(strFile, CString(TXT("Test")), ANSI_TEXT);
	CFile::CreateFolder(strFolder3);

	uint    count = 0;
	tstring strFolder(strFolder1);
	WCL::FolderIterator end;

	for (WCL::FolderIterator it(strFolder, TXT("*.*"), WCL::FolderIterator::FIND_FOLDERS); it != end; ++it)
	{
		TEST_FALSE(tstricmp(*it, TEST_FILE_1) == 0);

		++count;
	}

	TEST_TRUE(count == 2);
}
TEST_CASE_END

TEST_CASE("explicitly iterating files should skip folders")
{
	CFile::CreateFolder(strFolder1);
	CFile::CreateFolder(strFolder2);
	CFile::WriteTextFile(strFile, CString(TXT("Test")), ANSI_TEXT);
	CFile::CreateFolder(strFolder3);

	uint    count = 0;
	tstring strFolder(strFolder1);
	WCL::FolderIterator end;

	for (WCL::FolderIterator it(strFolder, TXT("*.*"), WCL::FolderIterator::FIND_FILES); it != end; ++it)
	{
		TEST_FALSE(tstricmp(*it, TEST_FOLDER_1) == 0);
		TEST_FALSE(tstricmp(*it, TEST_FOLDER_2) == 0);

		++count;
	}

	TEST_TRUE(count== 1);
}
TEST_CASE_END

TEST_CASE("explicitly iterating files and folders should include both files and folders")
{
	const int flags = WCL::FolderIterator::FIND_FOLDERS | WCL::FolderIterator::FIND_FILES;

	CFile::CreateFolder(strFolder1);
	CFile::CreateFolder(strFolder2);
	CFile::WriteTextFile(strFile, CString(TXT("Test")), ANSI_TEXT);
	CFile::CreateFolder(strFolder3);

	uint    count = 0;
	tstring strFolder(strFolder1);
	WCL::FolderIterator end;

	for (WCL::FolderIterator it(strFolder, TXT("*.*"), flags); it != end; ++it)
		++count;

	TEST_TRUE(count == 3);
}
TEST_CASE_END

}
TEST_SET_END
