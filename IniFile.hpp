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
	CIniFile(const char* pszPath);
	CIniFile(const char* pszDir, const char* pszFile);
	~CIniFile();
	
	//
	// Entry read/write methods.
	//
	CString ReadString (const char* pszSection, const char* pszEntry, const char* pszDefault) const;
	int     ReadInt    (const char* pszSection, const char* pszEntry, int iDefault) const;
	long    ReadLong   (const char* pszSection, const char* pszEntry, long lDefault) const;
	bool    ReadBool   (const char* pszSection, const char* pszEntry, bool bDefault) const;
	CRect   ReadRect   (const char* pszSection, const char* pszEntry, const CRect& rcDefault) const;

	void    WriteString(const char* pszSection, const char* pszEntry, const char* pszValue);
	void    WriteInt   (const char* pszSection, const char* pszEntry, int iValue);
	void    WriteLong  (const char* pszSection, const char* pszEntry, long lValue);
	void    WriteBool  (const char* pszSection, const char* pszEntry, bool bValue);
	void    WriteRect  (const char* pszSection, const char* pszEntry, const CRect& rcValue);
	
	void    DeleteEntry(const char* pszSection, const char* pszEntry);

	//
	// Array entry read/write methods.
	//
	CStrArray ReadStrings (const char* pszSection, const char* pszEntry, char cSep, const char*      pszDefault) const;
	void      WriteStrings(const char* pszSection, const char* pszEntry, char cSep, const CStrArray& astrValues);

	//
	// Section methods.
	//
	int  ReadSectionNames(CStrArray& astrNames);
	int  ReadSection(const char* pszSection, CStrArray& astrEntries);
	int  ReadSection(const char* pszSection, CStrArray& astrKeys, CStrArray& astrValues);
	void DeleteSection(const char* pszSection);

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
