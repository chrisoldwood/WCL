////////////////////////////////////////////////////////////////////////////////
//! \file   RegKey.cpp
//! \brief  The RegKey class definition.
//! \author Chris Oldwood

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

// Using declarations.
using WCL::RegistryException;

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

void RegKey::Create(HKEY hParentKey, const char* pszSubKey)
{
	ASSERT(m_hKey     == NULL);
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);

	LONG lResult = ::RegCreateKey(hParentKey, pszSubKey, &m_hKey);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, "Failed to create a registry key");
}

////////////////////////////////////////////////////////////////////////////////
//! Open the key for reading or writing.

void RegKey::Open(HKEY hParentKey, const char* pszSubKey, REGSAM dwAccess)
{
	ASSERT(m_hKey     == NULL);
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);

	LONG lResult = ::RegOpenKeyEx(hParentKey, pszSubKey, NULL, dwAccess, &m_hKey);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, "Failed to open a registry key");
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

	// Get the data type and size;
	LONG lResult = ::RegQueryValue(m_hKey, NULL, NULL, &lSize);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, "Failed to read the default key value size");

	// Allow for a nul terminator.
	++lSize;

	// Allocate a temporary buffer.
	char* pszBuffer = (char*) _alloca(lSize);

	memset(pszBuffer, 0, lSize);

	// Fetch the data.
	lResult = ::RegQueryValue(m_hKey, NULL, pszBuffer, &lSize);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, "Failed to read the default key value");

	return pszBuffer;
}

////////////////////////////////////////////////////////////////////////////////
//! Read a named string value under the key.

CString RegKey::ReadStringValue(const char* pszName, const char* pszDefault) const
{
	ASSERT(m_hKey     != NULL);
	ASSERT(pszName    != NULL);
	ASSERT(pszDefault != NULL);
	
	DWORD dwType = REG_NONE;
	DWORD dwSize = 0;

	// Get the data type and size;
	if (::RegQueryValueEx(m_hKey, pszName, NULL, &dwType, NULL, &dwSize) != ERROR_SUCCESS)
		return pszDefault;

	ASSERT(dwType == REG_SZ);

	// Allow for a nul terminator.
	dwSize++;

	// Allocate a temporary buffer.
	char* pszBuffer = (char*) _alloca(dwSize);

	memset(pszBuffer, 0, dwSize);

	// Fetch the data.
	if (::RegQueryValueEx(m_hKey, pszName, NULL, &dwType, (LPBYTE)pszBuffer, &dwSize) != ERROR_SUCCESS)
		return pszDefault;

	return pszBuffer;
}

////////////////////////////////////////////////////////////////////////////////
//! Write the default value for the key.

void RegKey::WriteDefaultValue(const char* pszValue)
{
	ASSERT(m_hKey   != NULL);
	ASSERT(pszValue != NULL);

	LONG lResult = ::RegSetValue(m_hKey, NULL, REG_SZ, pszValue, strlen(pszValue));

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, "Failed to write the default key value");
}

////////////////////////////////////////////////////////////////////////////////
//! Write a named string value under the key.

void RegKey::WriteStringValue(const char* pszName, const char* pszValue)
{
	ASSERT(m_hKey   != NULL);
	ASSERT(pszValue != NULL);

	LONG lResult = ::RegSetValueEx(m_hKey, pszName, 0, REG_SZ, reinterpret_cast<CONST BYTE*>(pszValue), strlen(pszValue)+1);

	if (lResult != ERROR_SUCCESS)
		throw RegistryException(lResult, "Failed to write a regsitry value");
}

////////////////////////////////////////////////////////////////////////////////
//! Query if the key exists.

bool RegKey::Exists(HKEY hParentKey, const char* pszSubKey)
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

bool RegKey::Delete(HKEY hParentKey, const char* pszSubKey)
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
//! Read the default value for a key.

CString RegKey::ReadKeyDefaultValue(HKEY hParentKey, const char* pszSubKey)
{
	ASSERT(hParentKey != NULL);
	ASSERT(pszSubKey  != NULL);

	RegKey oKey;

	oKey.Open(hParentKey, pszSubKey, KEY_READ);
	
	return oKey.ReadDefaultValue();
}

////////////////////////////////////////////////////////////////////////////////
//! Write the default value for a key. The key is created if it doesn't exist.

void RegKey::WriteKeyDefaultValue(HKEY hParentKey, const char* pszSubKey, const char* pszValue)
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
//! Write a named string value under a key. The key is created if it doesn't
//! exist.

void RegKey::WriteKeyStringValue(HKEY hParentKey, const char* pszSubKey, const char* pszName, const char* pszValue)
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

//namespace WCL
}
