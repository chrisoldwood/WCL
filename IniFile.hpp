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
	~CIniFile();
	
	//
	// I/O.
	//
	CString ReadString (const char* pszSection, const char* pszEntry, const char* pszDefault) const;
	int     ReadInt    (const char* pszSection, const char* pszEntry, int iDefault) const;
	long    ReadLong   (const char* pszSection, const char* pszEntry, long lDefault) const;
	bool    ReadBool   (const char* pszSection, const char* pszEntry, bool bDefault) const;

	void    WriteString(const char* pszSection, const char* pszEntry, const char* pszValue);
	void    WriteInt   (const char* pszSection, const char* pszEntry, int iValue);
	void    WriteLong  (const char* pszSection, const char* pszEntry, long lValue);
	void    WriteBool  (const char* pszSection, const char* pszEntry, bool bValue);
	
	void    DeleteSection(const char* pszSection);
	void    DeleteKey    (const char* pszSection, const char* pszEntry);

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
