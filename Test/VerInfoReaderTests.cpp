////////////////////////////////////////////////////////////////////////////////
//! \file   VerInfoReaderTests.cpp
//! \brief  The unit tests for the VerInfoReader class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/VerInfoReader.hpp>
#include <WCL/Path.hpp>

TEST_SET(VerInfoReader)
{
	const tstring filename(CPath::Application());

TEST_CASE("querying a file that doesn't have version information returns false")
{
	tstring nonExeFile(CPath::SystemDir() / TXT("compmgmt.msc"));

	TEST_TRUE(CPath(nonExeFile).Exists());
	TEST_TRUE(WCL::VerInfoReader::HasVersionInfo(nonExeFile) == false);
}
TEST_CASE_END

TEST_CASE("querying a file that does have version information returns true")
{
	TEST_TRUE(WCL::VerInfoReader::HasVersionInfo(filename) == true);
}
TEST_CASE_END

TEST_CASE("initial state is a closed reader")
{
	WCL::VerInfoReader reader;

	TEST_TRUE(reader.IsOpen() == false);
	TEST_TRUE(reader.FileName().empty() == true);
}
TEST_CASE_END

TEST_CASE("an open reader remembers the filename")
{
	WCL::VerInfoReader reader;

	reader.Open(filename);

	TEST_TRUE(reader.IsOpen() == true);
	TEST_TRUE(reader.FileName() == filename);
}
TEST_CASE_END

TEST_CASE("a closed reader forgets the filename")
{
	WCL::VerInfoReader reader;

	reader.Open(filename);
	reader.Close();

	TEST_TRUE(reader.IsOpen() == false);
	TEST_TRUE(reader.FileName().empty() == true);
}
TEST_CASE_END

TEST_CASE("getting the core file information returns the VS_FIXEDFILEINFO block")
{
	WCL::VerInfoReader reader;

	reader.Open(filename);

	const VS_FIXEDFILEINFO* pFileInfo = reader.GetFileInfo();

	TEST_TRUE(pFileInfo != nullptr);
	TEST_TRUE(pFileInfo->dwFileFlagsMask == VS_FFI_FILEFLAGSMASK);
	TEST_TRUE(pFileInfo->dwFileOS == VOS__WINDOWS32);
	TEST_TRUE(pFileInfo->dwFileType == VFT_APP);
}
TEST_CASE_END

TEST_CASE("querying for a string value without providing an explicit translation uses the default one")
{
	WCL::VerInfoReader reader;

	reader.Open(filename);

	TEST_TRUE(reader.GetStringValue(WCL::VerInfoReader::PRODUCT_VERSION) == TXT("1.0"));
}
TEST_CASE_END

TEST_CASE("querying for a string value without a reader requires the filename instead")
{
	TEST_TRUE(WCL::VerInfoReader::GetStringValue(filename, WCL::VerInfoReader::LEGAL_COPYRIGHT) == TXT("(C) Chris Oldwood"));
}
TEST_CASE_END

TEST_CASE("querying for translations returns a pair of iterators for the sequence")
{
	WCL::VerInfoReader reader;

	reader.Open(filename);

	WCL::VerInfoReader::TranslationIter itTransBegin;
	WCL::VerInfoReader::TranslationIter itTransEnd;

	size_t nCount = reader.GetTranslations(itTransBegin, itTransEnd);

	TEST_TRUE(nCount == 1);

	const WCL::VerInfoReader::Translation& oTranslation = *itTransBegin;

	TEST_TRUE(oTranslation.m_wLanguage == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK));
	TEST_TRUE(oTranslation.m_wCodePage == 1252);

	TEST_TRUE(reader.GetStringValue(oTranslation, WCL::VerInfoReader::FILE_VERSION) == TXT("1.0"));

	const WCL::VerInfoReader::Translation* pDefTrans = reader.GetDefaultTranslation();

	TEST_TRUE(pDefTrans == itTransBegin);
}
TEST_CASE_END

}
TEST_SET_END
