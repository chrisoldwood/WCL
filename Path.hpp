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
    CPath(const char* pszPath);
	CPath(const CPath& pathSrc);

	//
	// File/Dir attributes.
	//
    bool Exists() const;
    bool ReadOnly() const;

	// Max length of path.
	enum { MAX_LENGTH = 260 };

	//
	// Path components.
	//
	CPath   Directory() const;
	CString FileName() const;
	CString FileTitle() const;
	CString FileExt() const;

	//
	// Operations.
	//
	bool Rename(const char* pszPath);
	bool Delete();

	//
	// File Open dialog.
	enum DlgMode
	{
		OpenFile,
		SaveFile,
		SelectFile
	};
    
	bool Select(const CWnd& rParent, DlgMode eMode, const char* pszExts,
				const char* pszDefExt, const char* pszDir = NULL);

	//
	// Common path root directories.
	//
	static CPath CurrWorkDir();
	static CPath AppDir();
	static CPath WindowsDir();
	static CPath WindowsSystemDir();
	static CPath TempDir();

	//
	// Operators.
	//
	const CPath& operator=(const CString& rSrc);
	const CPath& operator=(const char* pszBuffer);
	
	void operator+=(const char* pszPath);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CPath::CPath(const char* pszPath)
{
	Copy(pszPath);
}

inline CPath::CPath(const CPath& pathSrc)
{
	Copy(pathSrc.m_pszData);
}

inline const CPath& CPath::operator=(const CString& rSrc)
{
	Copy(rSrc);
	return *this;
}

inline const CPath& CPath::operator=(const char* pszBuffer)
{
	Copy(pszBuffer);
	return *this;
}

inline void CPath::operator+=(const char* pszPath)
{
	ASSERT(pszPath);
	CString::operator +=("\\");
	CString::operator +=(pszPath);
}

#endif //PATH_HPP
