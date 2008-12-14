////////////////////////////////////////////////////////////////////////////////
//! \file   IniFileCfgProvider.cpp
//! \brief  The IniFileCfgProvider class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "IniFileCfgProvider.hpp"
#include "File.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

IniFileCfgProvider::IniFileCfgProvider(const tstring& publisher, const tstring& application)
	: m_publisher(publisher)
	, m_application(application)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

IniFileCfgProvider::~IniFileCfgProvider()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Check if there is a config file already.

bool IniFileCfgProvider::isAvailable()
{
	CIniFile iniFile;

	return iniFile.m_strPath.Exists();
}

////////////////////////////////////////////////////////////////////////////////
//! Remove the config information.

void IniFileCfgProvider::removeConfig()
{
	CIniFile iniFile;

	CFile::Delete(iniFile.m_strPath);
}

////////////////////////////////////////////////////////////////////////////////
//! Read a string value.

tstring IniFileCfgProvider::readString(const tstring& sectionName, const tstring& keyName, const tstring& defaultValue) const
{
	if (sectionName.empty())
		return m_iniFile.ReadString(m_application, keyName, defaultValue);
	else
		return m_iniFile.ReadString(sectionName, keyName, defaultValue);
}

////////////////////////////////////////////////////////////////////////////////
//! Write a string value.

void IniFileCfgProvider::writeString(const tstring& sectionName, const tstring& keyName, const tstring& value)
{
	if (sectionName.empty())
		m_iniFile.WriteString(m_application, keyName, value);
	else
		m_iniFile.WriteString(sectionName, keyName, value);
}

////////////////////////////////////////////////////////////////////////////////
//! Delete the entire section.

void IniFileCfgProvider::deleteSection(const tstring& sectionName)
{
	m_iniFile.DeleteSection(sectionName.c_str());
}

//namespace WCL
}
