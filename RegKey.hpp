/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REGKEY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CRegKey class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef REGKEY_HPP
#define REGKEY_HPP

/******************************************************************************
** 
** This class is used to access the registry.
**
*******************************************************************************
*/

class CRegKey
{
public:
	//
	// Constructors/Destructor.
	//
	CRegKey();
	~CRegKey();
	
	//
	// Accessors.
	//
	HKEY Handle() const;

	//
	// Methods.
	//
	bool Open(HKEY hKey, const char* pszSubKey);
	void Close();

	CString QueryString(const char* pszName, const char* pszDefault) const;

protected:
	//
	// Members.
	//
	HKEY m_hKey;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HKEY CRegKey::Handle() const
{
	return m_hKey;
}

#endif //REGKEY_HPP
