/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		INIFILE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CIniFile class declaration
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef INIFILE_HPP
#define INIFILE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Path.hpp"

// Forward declarations.
class CRect;

/******************************************************************************
** 
** This class encapsulates the behaviour of accessing a Windows .INI file.
**
*******************************************************************************
*/

class CIniFile
{
public:
	//
	// Constructors/Destructor.
	//
	CIniFile();
	CIniFile(const tchar* pszPath);
	CIniFile(const tchar* pszDir, const tchar* pszFile);
	~CIniFile();
	
	//
	// Entry read/write methods.
	//
	CString ReadString (const tchar* pszSection, const tchar* pszEntry, const tchar* pszDefault) const;
	tstring ReadString (const tstring& strSection, const tstring& strEntry, const tstring& strDefault) const;
	int     ReadInt    (const tchar* pszSection, const tchar* pszEntry, int nDefault) const;
	uint    ReadUInt   (const tchar* pszSection, const tchar* pszEntry, uint nDefault) const;
	long    ReadLong   (const tchar* pszSection, const tchar* pszEntry, long lDefault) const;
	bool    ReadBool   (const tchar* pszSection, const tchar* pszEntry, bool bDefault) const;
	bool    ReadBool   (const tstring& strSection, const tstring& strEntry, bool bDefault) const;
	CRect   ReadRect   (const tchar* pszSection, const tchar* pszEntry, const CRect& rcDefault) const;

	void    WriteString(const tchar* pszSection, const tchar* pszEntry, const tchar* pszValue);
	void    WriteString(const tstring& strSection, const tstring& strEntry, const tstring& strValue);
	void    WriteInt   (const tchar* pszSection, const tchar* pszEntry, int nValue);
	void    WriteUInt  (const tchar* pszSection, const tchar* pszEntry, uint nValue);
	void    WriteLong  (const tchar* pszSection, const tchar* pszEntry, long lValue);
	void    WriteBool  (const tchar* pszSection, const tchar* pszEntry, bool bValue);
	void    WriteRect  (const tchar* pszSection, const tchar* pszEntry, const CRect& rcValue);
	
	void    DeleteEntry(const tchar* pszSection, const tchar* pszEntry);

	//
	// Array entry read/write methods.
	//
	CStrArray ReadStrings (const tchar* pszSection, const tchar* pszEntry, tchar cSep, const tchar*     pszDefault) const;
	void      WriteStrings(const tchar* pszSection, const tchar* pszEntry, tchar cSep, const CStrArray& astrValues);

	//
	// Section methods.
	//
	size_t ReadSectionNames(CStrArray& astrNames);
	size_t ReadSection(const tchar* pszSection, CStrArray& astrEntries);
	size_t ReadSection(const tchar* pszSection, CStrArray& astrKeys, CStrArray& astrValues);
	void DeleteSection(const tchar* pszSection);

	//
	// Members.
	//
	CPath	m_strPath;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //INIFILE_HPP
