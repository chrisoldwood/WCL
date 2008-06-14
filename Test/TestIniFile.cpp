////////////////////////////////////////////////////////////////////////////////
//! \file   TestIniFile.cpp
//! \brief  The unit tests for the IniFile class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/IniFile.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the IniFile class.

void TestIniFile()
{
	CPath strFileName(CPath::ApplicationDir(), TXT("test.INI"));

	CIniFile oIniFile;

	TEST_TRUE(tstricmp(strFileName, oIniFile.m_strPath) == 0);
}
