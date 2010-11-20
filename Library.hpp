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

#if _MSC_VER > 1000
#pragma once
#endif

#include "Path.hpp"

/******************************************************************************
**
** A class to encapsulate a component such as a DLL.
**
*******************************************************************************
*/

class CLibrary /*: private NotCopyable*/
{
public:
	//
	// Constructors/Destructor.
	//
	CLibrary();
	CLibrary(const tchar* pszPath);
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

private:
	// NotCopyable.
	CLibrary(const CLibrary&);
	CLibrary& operator=(const CLibrary&);
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
