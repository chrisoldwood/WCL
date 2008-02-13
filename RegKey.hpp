////////////////////////////////////////////////////////////////////////////////
//! \file   RegKey.hpp
//! \brief  The RegKey class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef REGKEY_HPP
#define REGKEY_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The class used to read and write from the loca Registry.

class RegKey
{
public:
	//! Default constructor.
	RegKey();

	//! Destructor.
	~RegKey();
	
	//
	// Properties.
	//

	//! Get the underlying handle.
	HKEY Handle() const;

	//! Query if the key is open.
	bool IsOpen() const;

	//
	// Methods.
	//

	//! Create a key and open it for writing.
	void Create(HKEY hParentKey, const tchar* pszSubKey); // throw(RegistryException)

	//! Open the key for reading or writing.
	void Open(HKEY hParentKey, const tchar* pszSubKey, REGSAM dwAccess); // throw(RegistryException)

	//! Close the key.
	void Close();

	//
	// Key value methods.
	//

	//! Read the default value for the key.
	CString ReadDefaultValue() const; // throw(RegistryException)

	//! Read a named string value under the key.
	CString ReadStringValue(const tchar* pszName, const tchar* pszDefault) const;

	//! Write the default value for the key.
	void WriteDefaultValue(const tchar* pszValue); // throw(RegistryException)

	//! Write a named string value under the key.
	void WriteStringValue(const tchar* pszName, const tchar* pszValue); // throw(RegistryException)

	//
	// Class methods.
	//

	//! Query if the key exists.
	static bool Exists(HKEY hParentKey, const tchar* pszSubKey);

	//! Delete the key.
	static bool Delete(HKEY hParentKey, const tchar* pszSubKey);

	//! Read the default value for a key.
	static CString ReadKeyDefaultValue(HKEY hParentKey, const tchar* pszSubKey);

	//! Write the default value for a key.
	static void WriteKeyDefaultValue(HKEY hParentKey, const tchar* pszSubKey, const tchar* pszValue);

	//! Write a named string value under a key.
	static void WriteKeyStringValue(HKEY hParentKey, const tchar* pszSubKey, const tchar* pszName, const tchar* pszValue);

	//! Convert a registry key type to the symbolic name.
	static const tchar* KeyTypeToStr(DWORD dwType);

private:
	//
	// Members.
	//
	HKEY	m_hKey;		//!< The handle to the key.
//	CString	m_strKey;	//!< The full path of the key.

	// Disallow copying.
	RegKey(const RegKey&);
	RegKey& operator=(const RegKey&);
};

////////////////////////////////////////////////////////////////////////////////
//! Get the underlying handle.

inline HKEY RegKey::Handle() const
{
	return m_hKey;
}

////////////////////////////////////////////////////////////////////////////////
//! Query if the key is open.

inline bool RegKey::IsOpen() const
{
	return (m_hKey != NULL);
}

//namespace WCL
}

#endif //REGKEY_HPP
