/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PATH.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPath class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PATH_HPP
#define PATH_HPP

#if _MSC_VER > 1000
#pragma once
#endif

// Forward declarations.
class CWnd;

/******************************************************************************
** 
** A path is a string derived class that is used to manipulate filenames and
** directory paths.
**
*******************************************************************************
*/

class CPath : public CString
{
public:
	//
	// Constructors/Destructor.
	//
	CPath();
    CPath(const char*    pszPath);
	CPath(const CString& strSrc);
    CPath(const char*    pszDir, const char* pszFile);

	//
	// File/Dir attributes.
	//
    bool Exists() const;
    bool ReadOnly() const;
	bool IsFolder() const;

	//
	// Path components.
	//
	CString Drive() const;
	CPath	Root() const;
	CPath   Directory() const;
	CString FileName() const;
	CString FileTitle() const;
	CString FileExt() const;

	//
	// File Open dialog.
	//
	enum DlgMode
	{
		OpenFile,
		SaveFile,
		SelectFile
	};
    
	bool Select(const CWnd& rParent, DlgMode eMode, const char* pszExts, const char* pszDefExt, const char* pszDir = NULL);
	bool SelectDir(const CWnd& rParent, const char* pszTitle, const char* pszDir = NULL);
	bool SelectComputer(const CWnd& rParent, const char* pszTitle);

	static bool SelectFiles(const CWnd& rParent, const char* pszExts, const char* pszDefExt, CStrArray& astrFiles);
	static bool SelectFiles(const CWnd& rParent, const char* pszExts, const char* pszDefExt, const char* pszDir, CStrArray& astrFiles);

	//
	// Other methods.
	//
	void ExpandVars();

	//
	// Common root directories.
	//
	static CPath CurrentDir();
	static CPath ApplicationDir();
	static CPath ModuleDir();
	static CPath WindowsDir();
	static CPath SystemDir();
	static CPath TempDir();
	static CPath SpecialDir(int nCSIDL);

	static CPath ModuleDir(HMODULE hModule);

	//
	// Common full paths.
	//
	static CPath Application();
	static CPath Module();

	static CPath Module(HMODULE hModule);

	//
	// Operators.
	//
	char& operator[](int nChar);

	CPath& operator=(const char* pszSrc);
	CPath& operator=(const CString& strSrc);
	
	void operator/=(const char* pszPath);

	operator const char*() const;

	//
	// Friend functions.
	//
	friend CPath Append(const CPath& strLHS, const char* pszRHS);
	friend bool Equals(const CPath& strLHS, const char* pszRHS);

protected:
	//
	// Internal methods.
	//
	static void Normalise(char* pszPath);

	static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline char& CPath::operator[](int nChar)
{
	ASSERT( (nChar >=0) && (nChar < Length()) );

	return m_pszData[nChar];
}

inline CPath::operator const char*() const
{
	ASSERT(m_pszData);
	
	return m_pszData;
}

inline CPath& CPath::operator=(const char* pszSrc)
{
	ASSERT(pszSrc != NULL);

	Copy(pszSrc);

	return *this;
}

inline CPath& CPath::operator=(const CString& strSrc)
{
	Copy(strSrc);

	return *this;
}

/******************************************************************************
** 
** Global CPath operators. The idea of using / as the concatenation operator
** was shamelessly borrowed from Boost. 
**
*******************************************************************************
*/

inline CPath Append(const CPath& strLHS, const char* pszRHS)
{
	CPath str(strLHS);

	str /= pszRHS;

	return str;
}

inline CPath operator/(const CPath& strLHS, const char* pszRHS)
{
	return Append(strLHS, pszRHS);
}

inline CPath operator/(const CPath& strLHS, const CString& strRHS)
{
	return Append(strLHS, strRHS);
}

inline CPath operator/(const CPath& strLHS, const CPath& strRHS)
{
	return Append(strLHS, strRHS);
}

inline bool Equals(const CPath& strLHS, const char* pszRHS)
{
	return (strLHS.Compare(pszRHS, true) == 0);
}

inline bool operator==(const CPath& strLHS, const char* pszRHS)
{
	return Equals(strLHS, pszRHS);
}

inline bool operator==(const CPath& strLHS, const CString& strRHS)
{
	return Equals(strLHS, strRHS);
}

inline bool operator==(const CPath& strLHS, const CPath& strRHS)
{
	return Equals(strLHS, strRHS);
}

inline bool operator!=(const CPath& strLHS, const char* pszRHS)
{
	return !Equals(strLHS, pszRHS);
}

inline bool operator!=(const CPath& strLHS, const CString& strRHS)
{
	return !Equals(strLHS, strRHS);
}

inline bool operator!=(const CPath& strLHS, const CPath& strRHS)
{
	return !Equals(strLHS, strRHS);
}

#endif //PATH_HPP
