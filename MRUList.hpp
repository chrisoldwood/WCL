/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MRULIST.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMRUList class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MRULIST_HPP
#define MRULIST_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StrArray.hpp"

// Forward declarations.
class CMenu;
class CIniFile;

/******************************************************************************
** 
** This class manages the list of Most Recently Used files for an App.
**
*******************************************************************************
*/

class CMRUList
{
public:
	//
	// Constructors/Destructor.
	//
	CMRUList(size_t nMaxSize);
	~CMRUList();
	
	//
	// Accessors & mutators.
	//
	void Add(const tchar* pszPath);

	const CString& operator[](size_t nIndex) const;

	//
	// GUI methods.
	//
	void UpdateMenu(CMenu& rMenu, uint iCmdBase);

	//
	// Persistance methods.
	//
	void Load(CIniFile& rCfgFile, const tchar* pszSection = TXT("MRU"));
	void Save(CIniFile& rCfgFile, const tchar* pszSection = TXT("MRU"));

protected:
	//
	// Members.
	//
	size_t		m_nMaxSize;		// Max size of list.
	CStrArray	m_Paths;		// The list of MRU files.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline const CString& CMRUList::operator[](size_t nIndex) const
{
	return m_Paths[nIndex];
}

#endif //MRULIST_HPP
