/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		INIFILE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CIniFile class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "IniFile.hpp"
#include <stdlib.h>
#include "StrCvt.hpp"
#include "StrTok.hpp"
#include "StrArray.hpp"
#include "Rect.hpp"
#include <tchar.h>
#include "Win32Exception.hpp"
#include <malloc.h>

//! The size of the string buffer in characters.
const size_t MAX_CHARS = 256;

/******************************************************************************
** Method:		Constructor.
**
** Description:	Setup the Path as the application path and name, replacing
**				.EXE with .INI.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CIniFile::CIniFile()
{
	tchar szPath[MAX_PATH+1] = { 0 };

	// Get the Applications full path and name.
	DWORD dwChars = ::GetModuleFileName(NULL, szPath, MAX_PATH);

	if (dwChars == 0)
		throw WCL::Win32Exception(::GetLastError(), TXT("Failed to retrieve the full path of the module"));

	// Assume no path by default.
	tchar* pszFileName = szPath;

	// Find the start of the filename.
	tchar* pszFinalSep = tstrrchr(szPath, TXT('\\'));

	if (pszFinalSep != nullptr)
		pszFileName = pszFinalSep+1;

	// Append or replace the extension.
	tchar* pszExt = tstrrchr(pszFileName, TXT('.'));

	if (pszExt != nullptr)
		tstrcpy(pszExt, TXT(".ini"));
	else
		tstrcat(pszFileName, TXT(".ini"));

	// Save final path.
	m_strPath = szPath;
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	Initialises with the given path.
**
** Parameters:	pszPath		.INI file path.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CIniFile::CIniFile(const tchar* pszPath)
	: m_strPath(pszPath)
{
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	Initialises with the given directory and file name.
**
** Parameters:	pszDir		File directory.
**				pszFile		File name.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CIniFile::CIniFile(const tchar* pszDir, const tchar* pszFile)
	: m_strPath(pszDir, pszFile)
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

CIniFile::~CIniFile()
{
}

/******************************************************************************
** Method:		Read/Write String/Int/Long/Bool/Rect.
**
** Description:	Methods to read and write specific data types to and from the
**				.ini file.
**
** Parameters:	pszSection		The [..] section heading.
**				pszEntry		The ?= entry name.
**				Default			The default value.
**
** Returns:		Depends on method.
**
*******************************************************************************
*/

CString CIniFile::ReadString(const tchar* pszSection, const tchar* pszEntry, 
						const tchar* pszDefault) const
{
	ASSERT(pszSection);
	ASSERT(pszEntry);
	ASSERT(pszDefault);
	
	tchar szBuffer[MAX_CHARS+1] = { 0 };

	::GetPrivateProfileString(pszSection, pszEntry, pszDefault, szBuffer, MAX_CHARS, m_strPath);

	return szBuffer;
}
						
tstring CIniFile::ReadString(const tstring& strSection, const tstring& strEntry, const tstring& strDefault) const
{
	tchar szBuffer[MAX_CHARS+1] = { 0 };

	::GetPrivateProfileString(strSection.c_str(), strEntry.c_str(), strDefault.c_str(), szBuffer, MAX_CHARS, m_strPath);

	return szBuffer;
}

void CIniFile::WriteString(const tchar* pszSection, const tchar* pszEntry, const tchar* pszValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);
	ASSERT(pszValue);
	
	::WritePrivateProfileString(pszSection, pszEntry, pszValue, m_strPath);
}
						
void CIniFile::WriteString(const tstring& strSection, const tstring& strEntry, const tstring& strValue)
{
	::WritePrivateProfileString(strSection.c_str(), strEntry.c_str(), strValue.c_str(), m_strPath);
}

int CIniFile::ReadInt(const tchar* pszSection, const tchar* pszEntry, int nDefault) const
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	return ::GetPrivateProfileInt(pszSection, pszEntry, nDefault, m_strPath);
}
						
void CIniFile::WriteInt(const tchar* pszSection, const tchar* pszEntry, int iValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);
	
	::WritePrivateProfileString(pszSection, pszEntry, CStrCvt::FormatInt(iValue), m_strPath);
}
						
uint CIniFile::ReadUInt(const tchar* pszSection, const tchar* pszEntry, uint nDefault) const
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	tchar szValue[MAX_CHARS+1] = { 0 };

	// Read as a string.
	::GetPrivateProfileString(pszSection, pszEntry, TXT(""), szValue, MAX_CHARS, m_strPath);
	
	// Read anything?
	if (szValue[0] == TXT('\0'))
		return nDefault;
		
	// Convert to value and return
	return CStrCvt::ParseUInt(szValue);
}
						
void CIniFile::WriteUInt(const tchar* pszSection, const tchar* pszEntry, uint nValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	::WritePrivateProfileString(pszSection, pszEntry, CStrCvt::FormatUInt(nValue), m_strPath);
}
						
long CIniFile::ReadLong(const tchar* pszSection, const tchar* pszEntry, long lDefault) const
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	tchar szValue[MAX_CHARS+1] = { 0 };

	// Read as a string.
	::GetPrivateProfileString(pszSection, pszEntry, TXT(""), szValue, MAX_CHARS, m_strPath);
	
	// Read anything?
	if (szValue[0] == TXT('\0'))
		return lDefault;
		
	// Convert to value and return
	return CStrCvt::ParseLong(szValue);
}
						
void CIniFile::WriteLong(const tchar* pszSection, const tchar* pszEntry, long lValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	::WritePrivateProfileString(pszSection, pszEntry, CStrCvt::FormatLong(lValue), m_strPath);
}
						
bool CIniFile::ReadBool(const tchar* pszSection, const tchar* pszEntry, bool bDefault) const
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	tchar szValue[MAX_CHARS+1] = { 0 };

	// Read as a string.
	::GetPrivateProfileString(pszSection, pszEntry, TXT(""), szValue, MAX_CHARS, m_strPath);

	// Read anything?
	if (szValue[0] == TXT('\0'))
		return bDefault;
		
	// Check first character.
	return ( (szValue[0] == TXT('T')) || (szValue[0] == TXT('t')) );
}
						
bool CIniFile::ReadBool(const tstring& strSection, const tstring& strEntry, bool bDefault) const
{
	return ReadBool(strSection.c_str(), strEntry.c_str(), bDefault);
}

void CIniFile::WriteBool(const tchar* pszSection, const tchar* pszEntry, bool bValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	if (bValue)
		::WritePrivateProfileString(pszSection, pszEntry, TXT("True"), m_strPath);
	else
		::WritePrivateProfileString(pszSection, pszEntry, TXT("False"), m_strPath);
}

CRect CIniFile::ReadRect(const tchar* pszSection, const tchar* pszEntry, const CRect& rcDefault) const
{
	// Read as a string.
	CString str = ReadString(pszSection, pszEntry, TXT(""));

	// Read anything?
	if (str == TXT(""))
		return rcDefault;

	CStrArray astrFields;

	// Parse.
	if (CStrTok::Split(str, TXT(","), astrFields) != 4)
		return rcDefault;

	return CRect(_ttoi(astrFields[0]), _ttoi(astrFields[1]), _ttoi(astrFields[2]), _ttoi(astrFields[3]));
}

void CIniFile::WriteRect(const tchar* pszSection, const tchar* pszEntry, const CRect& rcValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);
	
	CString str;

	str.Format(TXT("%d,%d,%d,%d"), rcValue.left, rcValue.top, rcValue.right, rcValue.bottom);

	::WritePrivateProfileString(pszSection, pszEntry, str, m_strPath);
}

/******************************************************************************
** Method:		DeleteEntry()
**
** Description:	Deletes an entry from a section.
**
** Parameters:	pszSection	The section to delete from.
**				pszEntry	The entry to delete.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIniFile::DeleteEntry(const tchar* pszSection, const tchar* pszEntry)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	::WritePrivateProfileString(pszSection, pszEntry, NULL, m_strPath);
}

/******************************************************************************
** Method:		ReadStrings()
**
** Description:	Read and parse a list of strings speparated by a character.
**
** Parameters:	pszSection	The section to delete from.
**				pszEntry	The entry to delete.
**				cSep		The string separator.
**				pszDefault	The default list.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStrArray CIniFile::ReadStrings(const tchar* pszSection, const tchar* pszEntry, tchar cSep, const tchar* pszDefault) const
{
	ASSERT(pszSection != NULL);
	ASSERT(pszEntry   != NULL);
	ASSERT(pszDefault != NULL);

	CStrArray astr;

	// Get the entry.
	CString str = ReadString(pszSection, pszEntry, pszDefault);

	// Split list.
	CStrTok::Split(str, cSep, astr);

	return astr;
}

/******************************************************************************
** Method:		DeleteEntry()
**
** Description:	Deletes an entry from a section.
**
** Parameters:	pszSection	The section to delete from.
**				pszEntry	The entry to delete.
**				cSep		The string separator.
**				astrValues	The string list.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIniFile::WriteStrings(const tchar* pszSection, const tchar* pszEntry, tchar cSep, const CStrArray& astrValues)
{
	ASSERT(pszSection != NULL);
	ASSERT(pszEntry   != NULL);

	CString str;

	// Build string list.
	for (size_t i = 0; i < astrValues.Size(); ++i)
	{
		if (i != 0)
			str += cSep;

		str += astrValues[i];
	}

	WriteString(pszSection, pszEntry, str);
}

/******************************************************************************
** Method:		ReadSectionNames()
**
** Description:	Gets the names of all sections within the file.
**
** Parameters:	astrNames	The return buffer for the names.
**
** Returns:		The number of names read.
**
*******************************************************************************
*/

size_t CIniFile::ReadSectionNames(CStrArray& astrNames)
{
	// Allocate initial buffer.
	size_t nChars   = 1024;
	tchar* pszNames = static_cast<tchar*>(alloca(Core::NumBytes<tchar>(nChars+1)));

	// Read all names, reallocating if necessary...
	while (::GetPrivateProfileSectionNames(pszNames, static_cast<DWORD>(nChars), m_strPath) >= (nChars-2))
	{
		// Double the buffer size.
		nChars  *= 2;
		pszNames = static_cast<tchar*>(alloca(Core::NumBytes<tchar>(nChars+1)));
	}

	// For all strings.
	while (*pszNames != TXT('\0'))
	{
		astrNames.Add(pszNames);
		pszNames += tstrlen(pszNames) + 1;
	}

	return astrNames.Size();
}

/******************************************************************************
** Method:		ReadSection()
**
** Description:	Reads all the entries for a section.
**
** Parameters:	pszSection	The section name.
**				astrEntries	The return buffer for the entries.
**
** Returns:		The number of entries read.
**
*******************************************************************************
*/

size_t CIniFile::ReadSection(const tchar* pszSection, CStrArray& astrEntries)
{
	ASSERT(pszSection);

	// Allocate initial buffer.
	size_t nChars     = 1024;
	tchar* pszEntries = static_cast<tchar*>(alloca(Core::NumBytes<tchar>(nChars+1)));

	// Read all entries, reallocating if necessary...
	while (::GetPrivateProfileSection(pszSection, pszEntries, static_cast<DWORD>(nChars), m_strPath) >= (nChars-2))
	{
		// Double the buffer size.
		nChars    *= 2;
		pszEntries = static_cast<tchar*>(alloca(Core::NumBytes<tchar>(nChars+1)));
	}

	// For all strings.
	while (*pszEntries != TXT('\0'))
	{
		astrEntries.Add(pszEntries);
		pszEntries += tstrlen(pszEntries) + 1;
	}

	return astrEntries.Size();
}

/******************************************************************************
** Method:		ReadSection()
**
** Description:	Reads an entire section into two arrays of keys and values.
**
** Parameters:	pszSection	The section name.
**				astrKeys	The return buffer for the keys.
**				astrValues	The return buffer for the values.
**
** Returns:		The number of entries read.
**
*******************************************************************************
*/

size_t CIniFile::ReadSection(const tchar* pszSection, CStrArray& astrKeys, CStrArray& astrValues)
{
	ASSERT(pszSection);

	CStrArray astrEntries;

	// Read all the entries...
	if (ReadSection(pszSection, astrEntries))
	{
		// Split all entries.
		for (size_t i = 0; i < astrEntries.Size(); ++i)
		{
			// Split into key and value.
			CString strEntry = astrEntries[i];
			size_t  nLength  = strEntry.Length();
			size_t  nSepPos  = strEntry.Find(TXT('='));

			// Key set AND value set?
			if ( (nSepPos > 0) && ((nLength-nSepPos-1) > 0) )
			{
				astrKeys.Add(strEntry.Left(nSepPos));
				astrValues.Add(strEntry.Right(nLength-nSepPos-1));
			}
		}
	}

	ASSERT(astrKeys.Size() == astrValues.Size());

	return astrKeys.Size();
}

/******************************************************************************
** Method:		DeleteSection()
**
** Description:	Deletes an entire section.
**
** Parameters:	pszSection	The section to delete.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIniFile::DeleteSection(const tchar* pszSection)
{
	ASSERT(pszSection);

	::WritePrivateProfileString(pszSection, NULL, NULL, m_strPath);
}
