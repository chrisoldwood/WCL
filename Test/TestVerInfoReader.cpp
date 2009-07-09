////////////////////////////////////////////////////////////////////////////////
//! \file   TestVerInfoReader.cpp
//! \brief  The unit tests for the VerInfoReader class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/VerInfoReader.hpp>
#include <WCL/Path.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the VerInfoReader class.

void TestVerInfoReader()
{
	tstring strFileName(CPath::Application());
	tstring strBadFile(CPath::SystemDir() / TXT("compmgmt.msc"));

	TEST_TRUE(WCL::VerInfoReader::HasVersionInfo(strBadFile) == false);
	TEST_TRUE(WCL::VerInfoReader::HasVersionInfo(strFileName) == true);

	WCL::VerInfoReader oReader;

	TEST_TRUE(oReader.IsOpen() == false);
	TEST_TRUE(oReader.FileName().empty() == true);

	oReader.Open(strFileName);

	TEST_TRUE(oReader.IsOpen() == true);
	TEST_TRUE(oReader.FileName() == strFileName);

	const VS_FIXEDFILEINFO* pFileInfo = oReader.GetFileInfo();

	TEST_TRUE(pFileInfo != nullptr);
	TEST_TRUE(pFileInfo->dwFileFlagsMask == VS_FFI_FILEFLAGSMASK);
	TEST_TRUE(pFileInfo->dwFileOS == VOS__WINDOWS32);
	TEST_TRUE(pFileInfo->dwFileType == VFT_APP);

	WCL::VerInfoReader::TranslationIter itTransBegin;
	WCL::VerInfoReader::TranslationIter itTransEnd;

	size_t nCount = oReader.GetTranslations(itTransBegin, itTransEnd);

	TEST_TRUE(nCount == 1);

	const WCL::VerInfoReader::Translation& oTranslation = *itTransBegin;

	TEST_TRUE(oTranslation.m_wLanguage == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK));
	TEST_TRUE(oTranslation.m_wCodePage == 1252);

	TEST_TRUE(oReader.GetStringValue(oTranslation, WCL::VerInfoReader::FILE_VERSION) == TXT("1.0"));

	const WCL::VerInfoReader::Translation* pDefTrans = oReader.GetDefaultTranslation();

	TEST_TRUE(pDefTrans == itTransBegin);

	TEST_TRUE(oReader.GetStringValue(WCL::VerInfoReader::PRODUCT_VERSION) == TXT("1.0"));

	oReader.Close();

	TEST_TRUE(oReader.IsOpen() == false);
	TEST_TRUE(oReader.FileName().empty() == true);

	TEST_TRUE(WCL::VerInfoReader::GetStringValue(strFileName, WCL::VerInfoReader::LEGAL_COPYRIGHT) == TXT("(C) Chris Oldwood"));
}
