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

#if _MSC_VER > 1000
#pragma once
#endif

#include "Stream.hpp"
#include "Path.hpp"
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
	void Create(const tchar* pszPath);
	void Open(const tchar* pszPath, uint nMode);
	void Close();

	//
	// Overriden generic operations.
	//
	virtual void  Read(void* pBuffer, size_t iNumBytes);
	virtual void  Write(const void* pBuffer, size_t iNumBytes);
	virtual WCL::StreamPos Seek(WCL::StreamPos lPos, SeekPos eFrom = BEGIN);
	virtual bool  IsEOF();
	virtual void  Throw(int eErrCode, DWORD dwLastError);

	//
	// Other operations.
	//
	void  SetEOF();
	WCL::StreamPos Size();

	//
	// Class methods.
	//
	static bool  QueryInfo(const tchar* pszPath, struct _stat& oInfo);
	static ulong Size(const tchar* pszPath);

	static bool  Copy(const tchar* pszSrc, const tchar* pszDst, bool bOverwrite = false);
	static bool  Move(const tchar* pszSrc, const tchar* pszDst);
	static bool  Delete(const tchar* pszPath);

	static bool  CreateFolder(const tchar* pszPath, bool bCreatePath = false);
	static bool  DeleteFolder(const tchar* pszPath);

	static bool  CreateShortcut(const tchar* pszLink, const tchar* pszTarget, const tchar* pszDesc = NULL);

	//! Read the entire contents of a binary file.
	static size_t ReadFile(const tchar* pszPath, std::vector<byte>& vBuffer);

	//! Read the entire contents of a text file.
	static size_t ReadTextFile(const tchar* pszPath, CString& strContents, TextFormat& eFormat);

	//! Read the entire contents of a text file.
	static tstring ReadTextFile(const tchar* pszPath);

	//! Write the entire contents of a binary file.
	static void WriteFile(const tchar* pszPath, const std::vector<byte>& vBuffer);

	//! Write the entire contents of a text file.
	static void WriteTextFile(const tchar* pszPath, const CString& strContents, TextFormat eFormat);

protected:
	//
	// Internal members.
	//
	HANDLE			m_hFile;	// The files' handle.
	CPath			m_Path;		// The files' path.
	WCL::StreamPos	m_lEOF;		// Used to determine EOF.

private:
	// NotCopyable.
	CFile(const CFile&);
	CFile& operator=(const CFile&);
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
