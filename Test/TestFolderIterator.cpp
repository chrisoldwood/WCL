////////////////////////////////////////////////////////////////////////////////
//! \file   TestFolderIterator.cpp
//! \brief  The unit tests for the FolderIterator class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/FolderIterator.hpp>
#include <WCL/Path.hpp>
#include <WCL/File.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the FolderIterator class.

void TestFolderIterator()
{
	CPath strTempDir = CPath::TempDir();
	CPath strFolder1 = strTempDir / TXT("FolderIterator");
	CPath strFolder2 = strTempDir / TXT("FolderIterator") / TXT("Test");
	CPath strFolder3 = strTempDir / TXT("FolderIterator") / TXT("Test2");
	CPath strFile    = strTempDir / TXT("FolderIterator") / TXT("Test.txt");

	CFile::Delete(strFile);
	CFile::DeleteFolder(strFolder3);
	CFile::DeleteFolder(strFolder2);
	CFile::DeleteFolder(strFolder1);

	ASSERT(!strFolder1.Exists());
	ASSERT(!strFolder2.Exists());
	ASSERT(!strFile.Exists());

	TEST_THROWS(WCL::FolderIterator(tstring(strFolder1), TXT("*.txt")));

	WCL::FolderIterator end;

	TEST_TRUE(WCL::FolderIterator() == end);
	TEST_FALSE(WCL::FolderIterator() != end);

	CFile::CreateFolder(strFolder1);

	tstring             strFolder(strFolder1);
	WCL::FolderIterator it1(strFolder);

	TEST_TRUE(it1 == end);

	WCL::FolderIterator it2(strFolder, TXT("*.txt"));

	TEST_TRUE(it2 == end);
	TEST_TRUE(tstricmp(it2.Folder().c_str(), strFolder1) == 0);
	TEST_TRUE(tstricmp(it2.Mask().c_str(), TXT("*.txt")) == 0);

	CFile::CreateFolder(strFolder2);
	CFile::WriteTextFile(strFile, CString(TXT("Test")), ANSI_TEXT);

	bool bSeenFolder = false;
	bool bSeenFile = false;

	for (WCL::FolderIterator it(strFolder); it != end; ++it)
	{
		if (tstricmp(*it, TXT("test")) == 0)
			bSeenFolder = true;

		if (tstricmp(*it, TXT("test.txt")) == 0)
			bSeenFile = true;
	}

	TEST_TRUE(bSeenFolder);
	TEST_TRUE(bSeenFile);

	TEST_THROWS(*end);
	TEST_THROWS(++end);

	CFile::CreateFolder(strFolder3);

	uint nFolders = 0;

	for (WCL::FolderIterator it(strFolder, TXT("*.*"), WCL::FolderIterator::FIND_FOLDERS); it != end; ++it)
		++nFolders;

	TEST_TRUE(nFolders == 2);

	uint nFiles = 0;

	for (WCL::FolderIterator it(strFolder, TXT("*.*"), WCL::FolderIterator::FIND_FILES); it != end; ++it)
		++nFiles;

	TEST_TRUE(nFiles == 1);

	uint nTotal = 0;
	int  nFlags = WCL::FolderIterator::FIND_FOLDERS | WCL::FolderIterator::FIND_FILES;

	for (WCL::FolderIterator it(strFolder, TXT("*.*"), nFlags); it != end; ++it)
		++nTotal;

	TEST_TRUE(nTotal == 3);

	CFile::Delete(strFile);
	CFile::DeleteFolder(strFolder3);
	CFile::DeleteFolder(strFolder2);
	CFile::DeleteFolder(strFolder1);
}
