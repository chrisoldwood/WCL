////////////////////////////////////////////////////////////////////////////////
//! \file   FolderIteratorTests.cpp
//! \brief  The unit tests for the FolderIterator class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/FolderIterator.hpp>
#include <WCL/Path.hpp>
#include <WCL/File.hpp>
#include <Core/Algorithm.hpp>
#include <Core/Functor.hpp>

static const tchar* TEST_ROOT_NAME = TXT("FolderIteratorTests");

static const tchar* TEST_ROOT_FOLDER_1_NAME = TXT("Test-Root-Folder-1");
static const tchar* TEST_ROOT_FOLDER_2_NAME = TXT("Test-Root-Folder-2");
static const tchar* TEST_ROOT_FILE_1_NAME   = TXT("Test-Root-File-1.txt");
static const tchar* TEST_ROOT_FILE_2_NAME   = TXT("Test-Root-File-2.doc");

static const tchar* TEST_ROOT_FOLDER_1_FILE_1_NAME = TXT("Test-Root-Folder-1-File-1.txt");
static const tchar* TEST_ROOT_FOLDER_2_FILE_1_NAME = TXT("Test-Root-Folder-2-File-1.txt");

static const CPath TEMP_PATH      = CPath::TempDir();
static const CPath TEST_ROOT_PATH = TEMP_PATH / TEST_ROOT_NAME;

static const CPath TEST_ROOT_FOLDER_1_PATH = TEMP_PATH / TEST_ROOT_NAME / TEST_ROOT_FOLDER_1_NAME;
static const CPath TEST_ROOT_FOLDER_2_PATH = TEMP_PATH / TEST_ROOT_NAME / TEST_ROOT_FOLDER_2_NAME;
static const CPath TEST_ROOT_FILE_1_PATH   = TEMP_PATH / TEST_ROOT_NAME / TEST_ROOT_FILE_1_NAME;
static const CPath TEST_ROOT_FILE_2_PATH   = TEMP_PATH / TEST_ROOT_NAME / TEST_ROOT_FILE_2_NAME;

static const CPath TEST_ROOT_FOLDER_1_FILE_1_PATH = TEMP_PATH / TEST_ROOT_NAME / TEST_ROOT_FOLDER_1_NAME / TEST_ROOT_FOLDER_1_FILE_1_NAME;
static const CPath TEST_ROOT_FOLDER_2_FILE_1_PATH = TEMP_PATH / TEST_ROOT_NAME / TEST_ROOT_FOLDER_2_NAME / TEST_ROOT_FOLDER_2_FILE_1_NAME;

static const tstring TEST_FOLDER(TEST_ROOT_PATH);

static void assertTestFolderStructureIsClean()
{
	ASSERT(TEMP_PATH.Exists());
		ASSERT(!TEST_ROOT_PATH.Exists());
			ASSERT(!TEST_ROOT_FOLDER_1_PATH.Exists());
				ASSERT(!TEST_ROOT_FOLDER_1_FILE_1_PATH.Exists());
			ASSERT(!TEST_ROOT_FOLDER_2_PATH.Exists());
				ASSERT(!TEST_ROOT_FOLDER_2_FILE_1_PATH.Exists());
			ASSERT(!TEST_ROOT_FILE_1_PATH.Exists());
			ASSERT(!TEST_ROOT_FILE_2_PATH.Exists());
}

static void createTestFile(const CPath& path)
{
	CFile::WriteTextFile(path, TXT("lorem ipsum"), ANSI_TEXT);
}

static void createTestFolderStructure()
{
	CFile::CreateFolder(TEST_ROOT_PATH);
		CFile::CreateFolder(TEST_ROOT_FOLDER_1_PATH);
			createTestFile(TEST_ROOT_FOLDER_1_FILE_1_PATH);
		CFile::CreateFolder(TEST_ROOT_FOLDER_2_PATH);
			createTestFile(TEST_ROOT_FOLDER_2_FILE_1_PATH);
		createTestFile(TEST_ROOT_FILE_1_PATH);
		createTestFile(TEST_ROOT_FILE_2_PATH);
}

static void deleteTestFolderStructure()
{
		CFile::Delete(TEST_ROOT_FILE_2_PATH);
		CFile::Delete(TEST_ROOT_FILE_1_PATH);
			CFile::Delete(TEST_ROOT_FOLDER_2_FILE_1_PATH);
		CFile::DeleteFolder(TEST_ROOT_FOLDER_2_PATH);
			CFile::Delete(TEST_ROOT_FOLDER_1_FILE_1_PATH);
		CFile::DeleteFolder(TEST_ROOT_FOLDER_1_PATH);
	CFile::DeleteFolder(TEST_ROOT_PATH);
}

CORE_DEFINE_PREDICATE_EX(PathEquals, CPath, const CPath&, value, const tstring& ,rhs)
{
	return (tstricmp(value.c_str(), rhs.c_str()) == 0);
}
CORE_END_PREDICATE

TEST_SET(FolderIterator)
{

TEST_CASE_SETUP()
{
	assertTestFolderStructureIsClean();
}
TEST_CASE_SETUP_END

TEST_CASE_TEARDOWN()
{
	deleteTestFolderStructure();
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
	TEST_THROWS(WCL::FolderIterator(TEST_FOLDER, TXT("*.txt")));
}
TEST_CASE_END

TEST_CASE("iterating an empty folder returns an iterator to the end of the sequence")
{
	CFile::CreateFolder(TEST_ROOT_PATH);

	WCL::FolderIterator it1(TEST_FOLDER);
	WCL::FolderIterator end;

	TEST_TRUE(it1 == end);

	WCL::FolderIterator it2(TEST_FOLDER, TXT("*.txt"));

	TEST_TRUE(it2 == end);
	TEST_TRUE(tstricmp(it2.Folder().c_str(), TEST_ROOT_PATH) == 0);
	TEST_TRUE(tstricmp(it2.Mask().c_str(), TXT("*.txt")) == 0);
}
TEST_CASE_END

TEST_CASE("iterating a non-empty folder finds files and folders by default")
{
	CFile::CreateFolder(TEST_ROOT_PATH);
	CFile::CreateFolder(TEST_ROOT_FOLDER_1_PATH);
	createTestFile(TEST_ROOT_FILE_1_PATH);

	bool bSeenFolder = false;
	bool bSeenFile = false;

	for (WCL::FolderIterator it(TEST_FOLDER), end; it != end; ++it)
	{
		if (tstricmp(*it, TEST_ROOT_FOLDER_1_NAME) == 0)
			bSeenFolder = true;

		if (tstricmp(*it, TEST_ROOT_FILE_1_NAME) == 0)
			bSeenFile = true;
	}

	TEST_TRUE(bSeenFolder);
	TEST_TRUE(bSeenFile);
}
TEST_CASE_END

TEST_CASE("explicitly iterating folders should skip files")
{
	CFile::CreateFolder(TEST_ROOT_PATH);
	CFile::CreateFolder(TEST_ROOT_FOLDER_1_PATH);
	createTestFile(TEST_ROOT_FILE_1_PATH);
	CFile::CreateFolder(TEST_ROOT_FOLDER_2_PATH);

	uint count = 0;
	WCL::FolderIterator end;

	for (WCL::FolderIterator it(TEST_FOLDER, TXT("*.*"), WCL::FolderIterator::FIND_FOLDERS); it != end; ++it)
	{
		TEST_FALSE(tstricmp(*it, TEST_ROOT_FILE_1_NAME) == 0);

		++count;
	}

	TEST_TRUE(count == 2);
}
TEST_CASE_END

TEST_CASE("explicitly iterating files should skip folders")
{
	CFile::CreateFolder(TEST_ROOT_PATH);
	CFile::CreateFolder(TEST_ROOT_FOLDER_1_PATH);
	createTestFile(TEST_ROOT_FILE_1_PATH);
	CFile::CreateFolder(TEST_ROOT_FOLDER_2_PATH);

	uint count = 0;
	WCL::FolderIterator end;

	for (WCL::FolderIterator it(TEST_FOLDER, TXT("*.*"), WCL::FolderIterator::FIND_FILES); it != end; ++it)
	{
		TEST_FALSE(tstricmp(*it, TEST_ROOT_FOLDER_1_NAME) == 0);
		TEST_FALSE(tstricmp(*it, TEST_ROOT_FOLDER_2_NAME) == 0);

		++count;
	}

	TEST_TRUE(count== 1);
}
TEST_CASE_END

TEST_CASE("explicitly iterating files and folders should include both files and folders")
{
	const int flags = WCL::FolderIterator::FIND_FOLDERS | WCL::FolderIterator::FIND_FILES;

	CFile::CreateFolder(TEST_ROOT_PATH);
	CFile::CreateFolder(TEST_ROOT_FOLDER_1_PATH);
	createTestFile(TEST_ROOT_FILE_1_PATH);
	CFile::CreateFolder(TEST_ROOT_FOLDER_2_PATH);

	uint count = 0;
	WCL::FolderIterator end;

	for (WCL::FolderIterator it(TEST_FOLDER, TXT("*.*"), flags); it != end; ++it)
		++count;

	TEST_TRUE(count == 3);
}
TEST_CASE_END

TEST_CASE("finding all files in a folder returns a list of all file names")
{
	createTestFolderStructure();

	WCL::FileNames fileNames = WCL::FindFilesInFolder(TEST_FOLDER);

	TEST_TRUE(fileNames.size() == 2);
	TEST_TRUE(Core::exists_if(fileNames, PathEquals(TEST_ROOT_FILE_1_NAME)));
	TEST_TRUE(Core::exists_if(fileNames, PathEquals(TEST_ROOT_FILE_2_NAME)));
}
TEST_CASE_END

TEST_CASE("finding all files in a folder returns a list of the file names that match the mask")
{
	createTestFolderStructure();

	WCL::FileNames fileNames = WCL::FindFilesInFolder(TEST_FOLDER, TXT("*.txt"));

	TEST_TRUE(fileNames.size() == 1);
	TEST_TRUE(Core::exists_if(fileNames, PathEquals(TEST_ROOT_FILE_1_NAME)));
}
TEST_CASE_END

TEST_CASE("finding all folders in a folder returns a list of all folder names")
{
	createTestFolderStructure();

	WCL::FolderNames folderNames = WCL::FindFoldersInFolder(TEST_FOLDER);

	TEST_TRUE(folderNames.size() == 2);
	TEST_TRUE(Core::exists_if(folderNames, PathEquals(TEST_ROOT_FOLDER_1_NAME)));
	TEST_TRUE(Core::exists_if(folderNames, PathEquals(TEST_ROOT_FOLDER_2_NAME)));
}
TEST_CASE_END

TEST_CASE("finding all files recursively returns a list of the file paths that match the filename mask")
{
	createTestFolderStructure();

	WCL::PathNames pathNames = WCL::FindFilesInFolderRecursively(TEST_FOLDER, TXT("*.txt"));

	TEST_TRUE(pathNames.size() == 3);
	TEST_TRUE(Core::exists_if(pathNames, PathEquals(TEST_ROOT_FILE_1_PATH)));
	TEST_TRUE(Core::exists_if(pathNames, PathEquals(TEST_ROOT_FOLDER_1_FILE_1_PATH)));
	TEST_TRUE(Core::exists_if(pathNames, PathEquals(TEST_ROOT_FOLDER_2_FILE_1_PATH)));
}
TEST_CASE_END

}
TEST_SET_END
