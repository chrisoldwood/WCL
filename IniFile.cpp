/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		INIFILE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CIniFile class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <stdlib.h>

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

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
	char szPath[MAX_PATH+1];

	// Get the Applications full path and name.
	::GetModuleFileName(NULL, szPath, MAX_PATH);

	char* pszExt = strrchr(szPath, '.');
	ASSERT(pszExt != NULL);

	// Replace .EXE with .INI.
	strcpy(pszExt, ".ini");

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

CIniFile::CIniFile(const char* pszPath)
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

CIniFile::CIniFile(const char* pszDir, const char* pszFile)
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

CString CIniFile::ReadString(const char* pszSection, const char* pszEntry, 
						const char* pszDefault) const
{
	ASSERT(pszSection);
	ASSERT(pszEntry);
	ASSERT(pszDefault);
	
	char szBuffer[128];

	::GetPrivateProfileString(pszSection, pszEntry, pszDefault, szBuffer,
							sizeof(szBuffer), m_strPath);

	return szBuffer;
}
						
void CIniFile::WriteString(const char* pszSection, const char* pszEntry, const char* pszValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);
	ASSERT(pszValue);
	
	::WritePrivateProfileString(pszSection, pszEntry, pszValue, m_strPath);
}
						
int CIniFile::ReadInt(const char* pszSection, const char* pszEntry, int iDefault) const
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	return ::GetPrivateProfileInt(pszSection, pszEntry, iDefault, m_strPath);
}
						
void CIniFile::WriteInt(const char* pszSection, const char* pszEntry, int iValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);
	
	::WritePrivateProfileString(pszSection, pszEntry, CStrCvt::FormatInt(iValue), m_strPath);
}
						
long CIniFile::ReadLong(const char* pszSection, const char* pszEntry, long lDefault) const
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	char szValue[20];

	// Read as a string.
	::GetPrivateProfileString(pszSection, pszEntry, "", szValue, 
								sizeof(szValue), m_strPath);
	
	// Read anything?
	if (szValue[0] == '\0')
		return lDefault;
		
	// Convert to value and return
	return CStrCvt::ParseLong(szValue);
}
						
void CIniFile::WriteLong(const char* pszSection, const char* pszEntry, long lValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	::WritePrivateProfileString(pszSection, pszEntry, CStrCvt::FormatLong(lValue), m_strPath);
}
						
bool CIniFile::ReadBool(const char* pszSection, const char* pszEntry, bool bDefault) const
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	char szValue[10];

	// Read as a string.
	::GetPrivateProfileString(pszSection, pszEntry, "", szValue, 
								sizeof(szValue), m_strPath);

	// Read anything?
	if (szValue[0] == '\0')
		return bDefault;
		
	// Check first character.
	return ( (szValue[0] == 'T') || (szValue[0] == 't') );
}
						
void CIniFile::WriteBool(const char* pszSection, const char* pszEntry, bool bValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);

	if (bValue)
		::WritePrivateProfileString(pszSection, pszEntry, "True", m_strPath);
	else
		::WritePrivateProfileString(pszSection, pszEntry, "False", m_strPath);
}

CRect CIniFile::ReadRect(const char* pszSection, const char* pszEntry, const CRect& rcDefault) const
{
	// Read as a string.
	CString str = ReadString(pszSection, pszEntry, "");

	// Read anything?
	if (str == "")
		return rcDefault;

	CStrArray astrFields;

	// Parse.
	if (CStrTok::Split(str, ",", astrFields) != 4)
		return rcDefault;

	return CRect(atoi(astrFields[0]), atoi(astrFields[1]), atoi(astrFields[2]), atoi(astrFields[3]));
}

void CIniFile::WriteRect(const char* pszSection, const char* pszEntry, const CRect& rcValue)
{
	ASSERT(pszSection);
	ASSERT(pszEntry);
	
	CString str;

	str.Format("%d,%d,%d,%d", rcValue.left, rcValue.top, rcValue.right, rcValue.bottom);

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

void CIniFile::DeleteEntry(const char* pszSection, const char* pszEntry)
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

CStrArray CIniFile::ReadStrings(const char* pszSection, const char* pszEntry, char cSep, const char* pszDefault) const
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

void CIniFile::WriteStrings(const char* pszSection, const char* pszEntry, char cSep, const CStrArray& astrValues)
{
	ASSERT(pszSection != NULL);
	ASSERT(pszEntry   != NULL);

	CString str;

	// Build string list.
	for (int i = 0; i < astrValues.Size(); ++i)
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

int CIniFile::ReadSectionNames(CStrArray& astrNames)
{
	// Allocate initial buffer.
	DWORD dwSize   = 1024;
	char* pszNames = (char*) _alloca(dwSize);

	// Read all names, reallocating if necessary...
	while (::GetPrivateProfileSectionNames(pszNames, dwSize, m_strPath) >= (dwSize-2))
	{
		// Double the buffer size.
		dwSize  *= 2;
		pszNames = (char*) _alloca(dwSize);
	}

	// For all strings.
	while (*pszNames != '\0')
	{
		astrNames.Add(pszNames);
		pszNames += strlen(pszNames) + 1;
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

int CIniFile::ReadSection(const char* pszSection, CStrArray& astrEntries)
{
	ASSERT(pszSection);

	// Allocate initial buffer.
	DWORD dwSize     = 1024;
	char* pszEntries = (char*) _alloca(dwSize);

	// Read all entries, reallocating if necessary...
	while (::GetPrivateProfileSection(pszSection, pszEntries, dwSize, m_strPath) >= (dwSize-2))
	{
		// Double the buffer size.
		dwSize  *= 2;
		pszEntries = (char*) _alloca(dwSize);
	}

	// For all strings.
	while (*pszEntries != '\0')
	{
		astrEntries.Add(pszEntries);
		pszEntries += strlen(pszEntries) + 1;
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

int CIniFile::ReadSection(const char* pszSection, CStrArray& astrKeys, CStrArray& astrValues)
{
	ASSERT(pszSection);

	CStrArray astrEntries;

	// Read all the entries...
	if (ReadSection(pszSection, astrEntries))
	{
		// Split all entries.
		for (int i = 0; i < astrEntries.Size(); ++i)
		{
			// Split into key and value.
			CString strEntry = astrEntries[i];
			int     nLength  = strEntry.Length();
			int     nSepPos  = strEntry.Find('=');

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

void CIniFile::DeleteSection(const char* pszSection)
{
	ASSERT(pszSection);

	::WritePrivateProfileString(pszSection, NULL, NULL, m_strPath);
}
