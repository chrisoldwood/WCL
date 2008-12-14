////////////////////////////////////////////////////////////////////////////////
//! \file   RegKey.cpp
//! \brief  The RegKey class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "RegKey.hpp"
#include "RegistryException.hpp"
#include <Core/StringUtils.hpp>
#include <limits>
#include <tchar.h>
#include <shlwapi.h>

// Using declarations.
using WCL::RegistryException;

// Linker directives.
#pragma comment(lib, "shlwapi.lib")

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

RegKey::RegKey()
	: m_hKey(NULL)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

RegKey::~RegKey()
{
	Close();
}

////////////////////////////////////////////////////////////////////////////////
//! Create a key and open it for writing.

void RegKey::Create(HKEY hParentKey, const tchar* pszSubKey)
{
	ASSERT(m_hKey     == NULL);
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);

	LONG lResult = ::RegCreateKey(hParentKey, pszSubKey, &m_hKey);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, TXT("Failed to create a registry key"));
}

////////////////////////////////////////////////////////////////////////////////
//! Open the key for reading or writing.

void RegKey::Open(HKEY hParentKey, const tchar* pszSubKey, REGSAM dwAccess)
{
	ASSERT(m_hKey     == NULL);
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);

	LONG lResult = ::RegOpenKeyEx(hParentKey, pszSubKey, NULL, dwAccess, &m_hKey);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, TXT("Failed to open a registry key"));
}

////////////////////////////////////////////////////////////////////////////////
//! Close the key.

void RegKey::Close()
{
	// Key open?
	if (m_hKey != NULL)
	{
		// Close it.
		::RegCloseKey(m_hKey);
		m_hKey = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read the default value for the key.

CString RegKey::ReadDefaultValue() const
{
	ASSERT(m_hKey != NULL);
	
	LONG lSize = 0;

	// Get the data type and size in bytes.
	LONG lResult = ::RegQueryValue(m_hKey, NULL, NULL, &lSize);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, TXT("Failed to read the default key value size"));

	// Allow for a nul terminator.
	lSize += sizeof(tchar);

	// Allocate a temporary buffer.
	tchar* pszBuffer = static_cast<tchar*>(_alloca(lSize));

	memset(pszBuffer, 0, lSize);

	// Fetch the data.
	lResult = ::RegQueryValue(m_hKey, NULL, pszBuffer, &lSize);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, TXT("Failed to read the default key value"));

	return pszBuffer;
}

////////////////////////////////////////////////////////////////////////////////
//! Read a named string value under the key.

CString RegKey::ReadStringValue(const tchar* pszName, const tchar* pszDefault) const
{
	ASSERT(m_hKey     != NULL);
	ASSERT(pszName    != NULL);
	ASSERT(pszDefault != NULL);
	
	DWORD dwType = REG_NONE;
	DWORD dwSize = 0;

	// Get the data type and size;
	if (::RegQueryValueEx(m_hKey, pszName, NULL, &dwType, NULL, &dwSize) != ERROR_SUCCESS)
		return pszDefault;

	if (dwType != REG_SZ)
		throw RegistryException(Core::Fmt(TXT("Failed to read a string registry key because its type is %s"), KeyTypeToStr(dwType)));

	// Allow for a nul terminator.
	dwSize += sizeof(tchar);

	// Allocate a temporary buffer.
	tchar* pszBuffer = static_cast<tchar*>(_alloca(dwSize));

	memset(pszBuffer, 0, dwSize);

	// Fetch the data.
	if (::RegQueryValueEx(m_hKey, pszName, NULL, &dwType, (LPBYTE)pszBuffer, &dwSize) != ERROR_SUCCESS)
		return pszDefault;

	return pszBuffer;
}

////////////////////////////////////////////////////////////////////////////////
//! Write the default value for the key.

void RegKey::WriteDefaultValue(const tchar* pszValue)
{
	ASSERT(m_hKey   != NULL);
	ASSERT(pszValue != NULL);

	LONG lResult = ::RegSetValue(m_hKey, NULL, REG_SZ, pszValue, tstrlen(pszValue));

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, TXT("Failed to write the default key value"));
}

////////////////////////////////////////////////////////////////////////////////
//! Write a named string value under the key.

void RegKey::WriteStringValue(const tchar* pszName, const tchar* pszValue)
{
	ASSERT(m_hKey   != NULL);
	ASSERT(pszValue != NULL);

	size_t nChars = tstrlen(pszValue);
	size_t nBytes = Core::NumBytes<tchar>(nChars) + sizeof(tchar);

	LONG lResult = ::RegSetValueEx(m_hKey, pszName, 0, REG_SZ, reinterpret_cast<CONST BYTE*>(pszValue), nBytes);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, TXT("Failed to write a regsitry value"));
}

////////////////////////////////////////////////////////////////////////////////
//! Query if the key exists.

bool RegKey::Exists(HKEY hParentKey, const tchar* pszSubKey)
{
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);

	HKEY hKey = NULL;

	// Try and open the key for reading.
	LONG lResult = ::RegOpenKeyEx(hParentKey, pszSubKey, NULL, KEY_READ, &hKey);

	if (hKey != NULL)
		::RegCloseKey(hKey);

	return (lResult == ERROR_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
//! Delete the key. This only deletes the key and any named values, it does not
//! recursively delete any subkeys.
//! If the method fails the error code can be retrieved with GetLastError().

bool RegKey::Delete(HKEY hParentKey, const tchar* pszSubKey)
{
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);

	LONG lResult = ::RegDeleteKey(hParentKey, pszSubKey);

	// Fill in LastError() for the caller.
	if (lResult != ERROR_SUCCESS)
		::SetLastError(lResult);

	return (lResult == ERROR_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
//! Delete the entire sub-tree.
//! If the method fails the error code can be retrieved with GetLastError().

bool RegKey::DeleteTree(HKEY hParentKey, const tchar* pszSubKey)
{
	DWORD dwResult = ::SHDeleteKey(hParentKey, pszSubKey);

	// Fill in LastError() for the caller.
	if (dwResult != ERROR_SUCCESS)
		::SetLastError(dwResult);

	return (dwResult == ERROR_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
//! Read the default value for a key.

CString RegKey::ReadKeyDefaultValue(HKEY hParentKey, const tchar* pszSubKey)
{
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);

	RegKey oKey;

	oKey.Open(hParentKey, pszSubKey, KEY_READ);
	
	return oKey.ReadDefaultValue();
}

////////////////////////////////////////////////////////////////////////////////
//! Write the default value for a key. The key is created if it doesn't exist.

void RegKey::WriteKeyDefaultValue(HKEY hParentKey, const tchar* pszSubKey, const tchar* pszValue)
{
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);
	ASSERT(pszValue   != NULL);

	RegKey oKey;

	// Open key, creating if necessary.
	if (Exists(hParentKey, pszSubKey))
		oKey.Open(hParentKey, pszSubKey, KEY_WRITE);
	else
		oKey.Create(hParentKey, pszSubKey);

	// Set the value.
	oKey.WriteDefaultValue(pszValue);
}

////////////////////////////////////////////////////////////////////////////////
//! Read a named string value under a key.

CString RegKey::ReadKeyStringValue(HKEY hParentKey, const tchar* pszSubKey, const tchar* pszName, const tchar* pszDefault)
{
	ASSERT(hParentKey != nullptr);
	ASSERT(pszSubKey  != nullptr);
	ASSERT(pszName    != nullptr);
	ASSERT(pszDefault != nullptr);

	CString strValue = pszDefault;

	if (Exists(hParentKey, pszSubKey))
	{
		RegKey oKey;

		oKey.Open(hParentKey, pszSubKey, KEY_READ);

		strValue = oKey.ReadStringValue(pszName, pszDefault);
	}

	return strValue;
}

////////////////////////////////////////////////////////////////////////////////
//! Write a named string value under a key. The key is created if it doesn't
//! exist.

void RegKey::WriteKeyStringValue(HKEY hParentKey, const tchar* pszSubKey, const tchar* pszName, const tchar* pszValue)
{
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);
	ASSERT(pszName    != NULL);
	ASSERT(pszValue   != NULL);

	RegKey oKey;

	// Open key, creating if necessary.
	if (Exists(hParentKey, pszSubKey))
		oKey.Open(hParentKey, pszSubKey, KEY_WRITE);
	else
		oKey.Create(hParentKey, pszSubKey);

	// Set the value.
	oKey.WriteStringValue(pszName, pszValue);
}

////////////////////////////////////////////////////////////////////////////////
//! Convert a registry key type to the symbolic name.

const tchar* RegKey::KeyTypeToStr(DWORD dwType)
{
	switch (dwType)
	{
		case REG_NONE:							return TXT("REG_NONE");
		case REG_SZ:							return TXT("REG_SZ");
		case REG_EXPAND_SZ:						return TXT("REG_EXPAND_SZ");
		case REG_BINARY:						return TXT("REG_BINARY");
		case REG_DWORD:							return TXT("REG_DWORD");
//		case REG_DWORD_LITTLE_ENDIAN:			return TXT("REG_DWORD_LITTLE_ENDIAN");
		case REG_DWORD_BIG_ENDIAN:				return TXT("REG_DWORD_BIG_ENDIAN");
		case REG_LINK:							return TXT("REG_LINK");
		case REG_MULTI_SZ:						return TXT("REG_MULTI_SZ");
		case REG_RESOURCE_LIST:					return TXT("REG_RESOURCE_LIST");
		case REG_FULL_RESOURCE_DESCRIPTOR:		return TXT("REG_FULL_RESOURCE_DESCRIPTOR");
		case REG_RESOURCE_REQUIREMENTS_LIST:	return TXT("REG_RESOURCE_REQUIREMENTS_LIST");
		case REG_QWORD:							return TXT("REG_QWORD");
//		case REG_QWORD_LITTLE_ENDIAN:			return TXT("REG_QWORD_LITTLE_ENDIAN");
		default:								ASSERT_FALSE();	break;
	};

	tchar szType[std::numeric_limits<DWORD>::digits10] = { 0 };

	return _ltot(dwType, szType, 10);
}

//namespace WCL
}
