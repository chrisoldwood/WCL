/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FILE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CFile class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "File.hpp"
#include "FileException.hpp"
#include <io.h>
#include <shlobj.h>
#include <Core/AnsiWide.hpp>

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
			throw CFileException(CFileException::E_READ_ONLY, m_Path);
		
		// Unknown reason.
		throw CFileException(CFileException::E_CREATE_FAILED, m_Path);
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
			throw CFileException(CFileException::E_PATH_INVALID, m_Path);

		// Trying to write and file is read-only ?
		if ( (nMode & GENERIC_WRITE) && (m_Path.ReadOnly()) )
			throw CFileException(CFileException::E_READ_ONLY, m_Path);
		
		// Unknown reason.
		throw CFileException(CFileException::E_OPEN_FAILED, m_Path);
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
		throw CFileException(CFileException::E_READ_FAILED, m_Path);
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
		throw CFileException(CFileException::E_WRITE_FAILED, m_Path);
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

	// Reset error flag.
	::SetLastError(NO_ERROR);

	// Try the seek.
	ulong lNewPos = ::SetFilePointer(m_hFile, lPos, NULL, nFrom);

	// Error?
	if (::GetLastError() != NO_ERROR)
		throw CFileException(CFileException::E_SEEK_FAILED, m_Path);

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
	throw CFileException(eErrCode, m_Path);
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
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFile::Delete(const char* pszPath)
{
	ASSERT(pszPath != NULL);

	return (::DeleteFile(pszPath) != 0);
}

/******************************************************************************
** Method:		CreateFolder()
**
** Description:	Creates a folder.
**
** Parameters:	pszPath			The folder path.
**				bCreatePath		Create the in-between folders?
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFile::CreateFolder(const char* pszPath, bool bCreatePath)
{
	ASSERT(pszPath != NULL);

	// Try and create it.
	if (::CreateDirectory(pszPath, NULL) != 0)
		return true;

	if (bCreatePath)
	{
		// Failed for any reason other than an invalid path?
		if (::GetLastError() != ERROR_PATH_NOT_FOUND)
			return false;

		CPath strParent(CPath(pszPath).Directory());

		// Reached the root?
		if (strParent == pszPath)
			return false;

		// Recursively create parent folders.
		if (!CreateFolder(strParent, true))
			return false;
	
		// Try and create it again.
		if (::CreateDirectory(pszPath, NULL) != 0)
			return true;
	}

	return false;
}

/******************************************************************************
** Method:		DeleteFolder()
**
** Description:	Deletes a folder.
**
** Parameters:	pszPath		The folder path.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFile::DeleteFolder(const char* pszPath)
{
	ASSERT(pszPath != NULL);

	return (::RemoveDirectory(pszPath) != 0);
}

/******************************************************************************
** Method:		CreateShortcut()
**
** Description:	Create a shortcut to a file.
**
** Parameters:	pszLink		The path to the link.
**				pszTarget	The path of the file the link points to.
**				pszDesc		A description.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFile::CreateShortcut(const char* pszLink, const char* pszTarget, const char* pszDesc)
{
	ASSERT(pszLink   != NULL);
	ASSERT(pszTarget != NULL);

	// Initialise COM.
	HRESULT hResult = ::CoInitialize(NULL);

	if (SUCCEEDED(hResult))
	{
		IShellLink* pIShellLink = NULL;

		// Get a pointer to the IShellLink interface. 
		hResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*) &pIShellLink);

		if (SUCCEEDED(hResult))
		{ 
			// Set the link properties.
			pIShellLink->SetPath(pszTarget);
			pIShellLink->SetWorkingDirectory(CPath(pszTarget).Directory());

			if ((pszDesc != NULL) && (*pszDesc != '\0'))
				pIShellLink->SetDescription(pszDesc);
 
			IPersistFile* pIPersistFile = NULL;

			// Query IShellLink for the IPersistFile interface for saving the shortcut. 
			hResult = pIShellLink->QueryInterface(IID_IPersistFile, (LPVOID*) &pIPersistFile); 

			if (SUCCEEDED(hResult))
			{ 
				// Create the shortcut.
				hResult = pIPersistFile->Save(T2W(pszLink), TRUE);

				pIPersistFile->Release(); 
			} 

			pIShellLink->Release(); 
		}

		::CoUninitialize();
	}

	// If failed, store error in LastError.
	if (FAILED(hResult))
		::SetLastError(hResult);

	return SUCCEEDED(hResult);
}
