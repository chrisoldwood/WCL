/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LIBRARY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CLibrary class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef LIBRARY_HPP
#define LIBRARY_HPP

/******************************************************************************
** 
** A class to encapsulate a component such as a DLL.
**
*******************************************************************************
*/

class CLibrary
{
public:
	//
	// Constructors/Destructor.
	//
	CLibrary();
	CLibrary(const char* pszPath);
	~CLibrary();

	//
	// Methods.
	//
	bool Load();
	void Free();

	bool IsLoaded() const;

	FARPROC GetProcAddress(const char* pszName) const;

	//
	// Accessors.
	//
	HINSTANCE    Handle() const;
	const CPath& Path() const;

protected:
	//
	// Members
	//
	HINSTANCE	m_hInstance;
	CPath		m_strPath;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HINSTANCE CLibrary::Handle() const
{
	return m_hInstance;
}

inline const CPath& CLibrary::Path() const
{
	return m_strPath;
}

inline bool CLibrary::IsLoaded() const
{
	return (m_hInstance != NULL);
}

inline FARPROC CLibrary::GetProcAddress(const char* pszName) const
{
	ASSERT(IsLoaded());

	return ::GetProcAddress(m_hInstance, pszName);
}

#endif //LIBRARY_HPP
