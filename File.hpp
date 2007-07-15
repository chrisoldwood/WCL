/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FILE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CFile class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_FILE_HPP
#define WCL_FILE_HPP

#include "Stream.hpp"
#include <sys/stat.h>

/******************************************************************************
** 
** This class encapsulates I/O to a binary/ASCII file.
**
*******************************************************************************
*/

class CFile : public CStream
{
public:
	//
	// Constructors/Destructor.
	//
	CFile();
	~CFile();
	
	//
	// Member access.
	//
	HANDLE Handle() const;
	CPath  Path() const;

	//
	// Open/Close operations.
	//
	void Create(const char* pszPath);
	void Open(const char* pszPath, uint nMode);
	void Close();

	//
	// Overriden generic operations.
	//
	virtual void  Read(void* pBuffer, uint iNumBytes);
	virtual void  Write(const void* pBuffer, uint iNumBytes);
	virtual ulong Seek(ulong lPos, uint nFrom = FILE_BEGIN);
	virtual bool  IsEOF();
	virtual void  Throw(int eErrCode);

	//
	// Other operations.
	//
	void  SetEOF();
	ulong Size();

	//
	// Class methods.
	//
	static bool  QueryInfo(const char* pszPath, struct _stat& oInfo);
	static ulong Size(const char* pszPath);

	static bool  Copy(const char* pszSrc, const char* pszDst, bool bOverwrite = false);
	static bool  Move(const char* pszSrc, const char* pszDst);
	static bool  Delete(const char* pszPath);

	static bool  CreateFolder(const char* pszPath, bool bCreatePath = false);
	static bool  DeleteFolder(const char* pszPath);

	static bool  CreateShortcut(const char* pszLink, const char* pszTarget, const char* pszDesc = NULL);

protected:
	//
	// Internal members.
	//
	HANDLE	m_hFile;	// The files' handle.
	CPath	m_Path;		// The files' path.
	ulong	m_lEOF;		// Used to determine EOF.
};


/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HANDLE CFile::Handle() const
{
	return m_hFile;
}

inline CPath CFile::Path() const
{
	return m_Path;
}

#endif // WCL_FILE_HPP
