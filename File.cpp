/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FILE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CFile class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <io.h>

/******************************************************************************
** Method:		Default constructor
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFile::CFile()
	: m_hFile(INVALID_HANDLE_VALUE)
	, m_lEOF(0)
{
}

/******************************************************************************
** Method:		Destructor
**
** Description:	Close the file, if open.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFile::~CFile()
{
	if (m_hFile != INVALID_HANDLE_VALUE)
		::CloseHandle(m_hFile);
}

/******************************************************************************
** Method:		Create()
**
** Description:	Create a new file, or open and truncate an existing one.
**
** Parameters:	pszPath		The file to create.
**
** Returns:		Nothing.
**
** Exceptions:	CFileException on error.
**
*******************************************************************************
*/

void CFile::Create(const char* pszPath)
{
	m_nMode = GENERIC_WRITE;
	m_Path  = pszPath;
	m_hFile = ::CreateFile(m_Path, m_nMode, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Error?
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		// File is read-only?
		if (m_Path.ReadOnly())
			throw CFileException(CFileException::E_READ_ONLY, *this);
		
		// Unknown reason.
		throw CFileException(CFileException::E_CREATE_FAILED, *this);
	}
}

/******************************************************************************
** Method:		Open()
**
** Description:	Open an existing file for reading and/or writing.
**
** Parameters:	pszPath		The file to create.
**				eMode		The access mode.
**
** Returns:		Nothing.
**
** Exceptions:	CFileException on error.
**
*******************************************************************************
*/

void CFile::Open(const char* pszPath, uint nMode)
{
	m_nMode = nMode;
	m_Path  = pszPath;
	m_hFile = ::CreateFile(m_Path, m_nMode, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	// Error?
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		// File exists?
		if (!m_Path.Exists())
			throw CFileException(CFileException::E_PATH_INVALID, *this);

		// Trying to write and file is read-only ?
		if ( (nMode & GENERIC_WRITE) && (m_Path.ReadOnly()) )
			throw CFileException(CFileException::E_READ_ONLY, *this);
		
		// Unknown reason.
		throw CFileException(CFileException::E_OPEN_FAILED, *this);
	}

	// Get EOF.
	m_lEOF = Size();
}

/******************************************************************************
** Method:		Close()
**
** Description:	Close the file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFile::Close()
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);

	::CloseHandle(m_hFile);

	// Reset members.
	m_hFile = INVALID_HANDLE_VALUE;
	m_nMode = NULL;
	m_lEOF  = 0;
}

/******************************************************************************
** Method:		Read()
**
** Description:	Core method for reading a number of bytes from the stream.
**
** Parameters:	pBuffer		The buffer to read to.
**				iNumBytes	The number of bytes to read.
**
** Returns:		Nothing.
**
** Exceptions:	CFileException on error.
**
*******************************************************************************
*/

void CFile::Read(void* pBuffer, uint iNumBytes)
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);
	ASSERT(m_nMode & GENERIC_READ);

	DWORD dwRead = 0;

	if (::ReadFile(m_hFile, pBuffer, iNumBytes, &dwRead, NULL) == 0)
		throw CFileException(CFileException::E_READ_FAILED, *this);
}

/******************************************************************************
** Method:		Write()
**
** Description:	Core method for writing a number of bytes to the stream.
**
** Parameters:	pBuffer		The buffer to write from.
**				iNumBytes	The number of bytes to write.
**
** Returns:		Nothing.
**
** Exceptions:	CFileException on error.
**
*******************************************************************************
*/

void CFile::Write(const void* pBuffer, uint iNumBytes)
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);
	ASSERT(m_nMode & GENERIC_WRITE);

	DWORD dwWritten = 0;

	if (::WriteFile(m_hFile, (const char*)pBuffer, iNumBytes, &dwWritten, NULL) == 0)
		throw CFileException(CFileException::E_WRITE_FAILED, *this);
}

/******************************************************************************
** Method:		Seek()
**
** Description:	Core method for changing the stream pointer.
**
** Parameters:	lPos		The new position.
**				nFrom		The origin from where to seek.
**
** Returns:		The new stream pointer.
**
** Exceptions:	CFileException on error.
**
*******************************************************************************
*/

ulong CFile::Seek(ulong lPos, uint nFrom)
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);

	// Try the seek.
	ulong lNewPos = ::SetFilePointer(m_hFile, lPos, NULL, nFrom);

	// Error?
	if (::GetLastError() != NO_ERROR)
		throw CFileException(CFileException::E_SEEK_FAILED, *this);

	return lNewPos;
}

/******************************************************************************
** Method:		IsEOF()
**
** Description:	Used to detect when the end of the stream has been reached.
**
** Parameters:	None.
**
** Returns:		true or false
**
*******************************************************************************
*/

bool CFile::IsEOF()
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);
	ASSERT(m_nMode & GENERIC_READ);

	return (Seek(0, FILE_CURRENT) >= m_lEOF);
}

/******************************************************************************
** Method:		Throw()
**
** Description:	Throws an exception of the correct type for the derived stream.
**
** Parameters:	eErrCode	A CStreamException error code.
**
** Returns:		Nothing.
**
** Exceptions:	CFileException always.
**
*******************************************************************************
*/

void CFile::Throw(int eErrCode)
{
	throw CFileException(eErrCode, *this);
}

/******************************************************************************
** Method:		SetEOF()
**
** Description:	Sets the end of the file to the current file pointer.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFile::SetEOF()
{
	::SetEndOfFile(m_hFile);
}

/******************************************************************************
** Method:		size()
**
** Description:	Gets the current size of the file position.
**
** Parameters:	None.
**
** Returns:		The current size.
**
*******************************************************************************
*/

ulong CFile::Size()
{
	ulong lCurPos = Seek(0, FILE_CURRENT);
	ulong lSize   = Seek(0, FILE_END);

	Seek(lCurPos, FILE_BEGIN);

	return lSize;
}

/******************************************************************************
** Method:		QueryInfo()
**
** Description:	Queries for information about a file.
**
** Parameters:	pszPath		The file path.
**				oInfo		The returned information.
**
** Returns:		true or false
**
*******************************************************************************
*/

bool CFile::QueryInfo(const char* pszPath, struct _stat& oInfo)
{
	ASSERT(pszPath != NULL);

	memset(&oInfo, 0, sizeof(oInfo));

	int nResult = _stat(pszPath, &oInfo);

	return (nResult == 0);
}

/******************************************************************************
** Method:		Size()
**
** Description:	Gets the size of the file in bytes.
**
** Parameters:	pszPath		The file path.
**
** Returns:		The size or 0 on error.
**
*******************************************************************************
*/

ulong CFile::Size(const char* pszPath)
{
	ulong lSize = 0;

	struct _stat oInfo;

	if (QueryInfo(pszPath, oInfo))
		lSize = oInfo.st_size;

	return lSize;
}

/******************************************************************************
** Method:		Copy()
**
** Description:	Copies the file.
**
** Parameters:	pszSrc		The source file path.
**				pszDst		The destination file path.
**				bOverwrite	Overwrite if exists?
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFile::Copy(const char* pszSrc, const char* pszDst, bool bOverwrite)
{
	ASSERT(pszSrc != NULL);
	ASSERT(pszDst != NULL);

	return (::CopyFile(pszSrc, pszDst, !bOverwrite) != 0);
}

/******************************************************************************
** Method:		Move()
**
** Description:	Moves the file.
**
** Parameters:	pszSrc		The source file path.
**				pszDst		The destination file path.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFile::Move(const char* pszSrc, const char* pszDst)
{
	ASSERT(pszSrc != NULL);
	ASSERT(pszDst != NULL);

	return (::MoveFile(pszSrc, pszDst) != 0);
}

/******************************************************************************
** Method:		Delete()
**
** Description:	Deletes the given file.
**
** Parameters:	pszPath		The file path.
**
** Returns:		true or false
**
*******************************************************************************
*/

bool CFile::Delete(const char* pszPath)
{
	ASSERT(pszPath != NULL);

	return (::DeleteFile(pszPath) != 0);
}
