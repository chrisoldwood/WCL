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
	CPath(const CPath&   strSrc);
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
	CPath   Drive() const;
	CPath   Directory() const;
	CString FileName() const;
	CString FileTitle() const;
	CString FileExt() const;

	//
	// File Open dialog.
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
	const CPath& operator=(const CString& rSrc);
	const CPath& operator=(const char* pszBuffer);
	
	void operator+=(const char* pszPath);

protected:
	//
	// Internal methods.
	//
	static void StripFinalSlash(char* pszPath);

	static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CPath::CPath(const char* pszPath)
{
	ASSERT(pszPath != NULL);

	Copy(pszPath);
}

inline CPath::CPath(const CString& strSrc)
{
	Copy(strSrc);
}

inline CPath::CPath(const CPath& strSrc)
{
	Copy(strSrc);
}

inline CPath::CPath(const char* pszDir, const char* pszFile)
{
	ASSERT(pszDir  != NULL);
	ASSERT(pszFile != NULL);

	Copy(pszDir);
	operator +=(pszFile);
}

inline const CPath& CPath::operator=(const CString& rSrc)
{
	Copy(rSrc);
	return *this;
}

inline const CPath& CPath::operator=(const char* pszBuffer)
{
	ASSERT(pszBuffer != NULL);

	Copy(pszBuffer);
	return *this;
}

inline void CPath::operator+=(const char* pszPath)
{
	ASSERT(pszPath != NULL);

	int nLength = Length();

	// Add path separator?
	if ( (nLength > 0) && ((*this)[nLength-1] != '\\') )
		CString::operator +=('\\');

	CString::operator +=(pszPath);
}

/******************************************************************************
** 
** Global string operators.
**
*******************************************************************************
*/

inline CPath operator+(const CPath& strLHS, const CPath& strRHS)
{
	CPath str;

	str  = strLHS;
	str += strRHS;

	return str;
}

inline CPath operator+(const CPath& strLHS, const CString& strRHS)
{
	CPath str;

	str  = strLHS;
	str += strRHS;

	return str;
}

inline CPath operator+(const CPath& strLHS, const char* pszRHS)
{
	CPath str;

	str  = strLHS;
	str += pszRHS;

	return str;
}

#endif //PATH_HPP
