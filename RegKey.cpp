/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REGKEY.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CRegKey class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CRegKey::CRegKey()
	: m_hKey(NULL)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CRegKey::~CRegKey()
{
	Close();
}

/******************************************************************************
** Method:		Open()
**
** Description:	Opens the specified key for reading.
**
** Parameters:	hKey		The root key.
**				pszSubKey	The path to the subkey.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

bool CRegKey::Open(HKEY hKey, const char* pszSubKey)
{
	ASSERT(m_hKey    == NULL);
	ASSERT(hKey      != NULL);
	ASSERT(pszSubKey != NULL);

	LONG lResult = ::RegOpenKeyEx(hKey, pszSubKey, NULL, KEY_QUERY_VALUE, &m_hKey);

	return (lResult == ERROR_SUCCESS);
}

/******************************************************************************
** Method:		Close()
**
** Description:	Close the key.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CRegKey::Close()
{
	// Key open?
	if (m_hKey != NULL)
	{
		// Close it.
		::RegCloseKey(m_hKey);
		m_hKey = NULL;
	}
}

/******************************************************************************
** Method:		QueryString()
**
** Description:	Gets a string value.
**
** Parameters:	pszName		The name of the value.
**				pszDefault	The default to return if not found/on error.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CString CRegKey::QueryString(const char* pszName, const char* pszDefault) const
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
