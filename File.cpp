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
#include <tchar.h>
#include <limits>

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
	, m_Path()
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

void CFile::Create(const tchar* pszPath)
{
	m_nMode = GENERIC_WRITE;
	m_Path  = pszPath;
	m_hFile = ::CreateFile(m_Path, m_nMode, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Error?
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		DWORD dwLastError = ::GetLastError();

		// File is read-only?
		if (m_Path.ReadOnly())
			throw CFileException(CFileException::E_READ_ONLY, m_Path, ERROR_ACCESS_DENIED);

		// Unknown reason.
		throw CFileException(CFileException::E_CREATE_FAILED, m_Path, dwLastError);
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

void CFile::Open(const tchar* pszPath, uint nMode)
{
	m_nMode = nMode;
	m_Path  = pszPath;
	m_hFile = ::CreateFile(m_Path, m_nMode, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// Error?
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		DWORD dwLastError = ::GetLastError();

		// File exists?
		if (!m_Path.Exists())
			throw CFileException(CFileException::E_PATH_INVALID, m_Path, ERROR_FILE_NOT_FOUND);

		// Trying to write and file is read-only ?
		if ( (nMode & GENERIC_WRITE) && (m_Path.ReadOnly()) )
			throw CFileException(CFileException::E_READ_ONLY, m_Path, ERROR_ACCESS_DENIED);

		// Unknown reason.
		throw CFileException(CFileException::E_OPEN_FAILED, m_Path, dwLastError);
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
	m_nMode = GENERIC_NONE;
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

void CFile::Read(void* pBuffer, size_t iNumBytes)
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);
	ASSERT(m_nMode & GENERIC_READ);
	ASSERT(iNumBytes <= std::numeric_limits<DWORD>::max());

	DWORD dwRead = 0;

	if (::ReadFile(m_hFile, pBuffer, static_cast<DWORD>(iNumBytes), &dwRead, NULL) == 0)
		throw CFileException(CFileException::E_READ_FAILED, m_Path, ::GetLastError());
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

void CFile::Write(const void* pBuffer, size_t iNumBytes)
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);
	ASSERT(m_nMode & GENERIC_WRITE);
	ASSERT(iNumBytes <= std::numeric_limits<DWORD>::max());

	DWORD dwWritten = 0;

	if (::WriteFile(m_hFile, pBuffer, static_cast<DWORD>(iNumBytes), &dwWritten, NULL) == 0)
		throw CFileException(CFileException::E_WRITE_FAILED, m_Path, ::GetLastError());
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

WCL::StreamPos CFile::Seek(WCL::StreamPos lPos, SeekPos eFrom)
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);

	// Reset error flag.
	::SetLastError(NO_ERROR);

	// Try the seek.
	WCL::StreamPos lNewPos = ::SetFilePointer(m_hFile, static_cast<LONG>(lPos), NULL, eFrom);

	// Error?
	DWORD dwLastError = ::GetLastError();

	if (dwLastError != NO_ERROR)
		throw CFileException(CFileException::E_SEEK_FAILED, m_Path, dwLastError);

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

	return (Seek(0, CURRENT) >= m_lEOF);
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

void CFile::Throw(int eErrCode, DWORD dwLastError)
{
	throw CFileException(eErrCode, m_Path, dwLastError);
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

WCL::StreamPos CFile::Size()
{
	WCL::StreamPos lCurPos = Seek(0, CURRENT);
	WCL::StreamPos lSize   = Seek(0, END);

	Seek(lCurPos, BEGIN);

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

bool CFile::QueryInfo(const tchar* pszPath, struct _stat& oInfo)
{
	ASSERT(pszPath != NULL);

	memset(&oInfo, 0, sizeof(oInfo));

	int nResult = _tstat(pszPath, &oInfo);

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

ulong CFile::Size(const tchar* pszPath)
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

bool CFile::Copy(const tchar* pszSrc, const tchar* pszDst, bool bOverwrite)
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

bool CFile::Move(const tchar* pszSrc, const tchar* pszDst)
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

bool CFile::Delete(const tchar* pszPath)
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

bool CFile::CreateFolder(const tchar* pszPath, bool bCreatePath)
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

bool CFile::DeleteFolder(const tchar* pszPath)
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

bool CFile::CreateShortcut(const tchar* pszLink, const tchar* pszTarget, const tchar* pszDesc)
{
	ASSERT(pszLink   != NULL);
	ASSERT(pszTarget != NULL);

	// Initialise COM.
	HRESULT hResult = ::CoInitialize(NULL);

	if (SUCCEEDED(hResult))
	{
		IShellLink* pIShellLink = NULL;

		// Get a pointer to the IShellLink interface.
		hResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, reinterpret_cast<LPVOID*>(&pIShellLink));

		if (SUCCEEDED(hResult))
		{
			// Set the link properties.
			pIShellLink->SetPath(pszTarget);
			pIShellLink->SetWorkingDirectory(CPath(pszTarget).Directory());

			if ((pszDesc != NULL) && (*pszDesc != TXT('\0')))
				pIShellLink->SetDescription(pszDesc);

			IPersistFile* pIPersistFile = NULL;

			// Query IShellLink for the IPersistFile interface for saving the shortcut.
			hResult = pIShellLink->QueryInterface(IID_IPersistFile, reinterpret_cast<LPVOID*>(&pIPersistFile));

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

////////////////////////////////////////////////////////////////////////////////
//! Read the entire contents of a binary file. It returns the number of bytes
//! read.

size_t CFile::ReadFile(const tchar* pszPath, std::vector<byte>& vBuffer)
{
	CFile oFile;

	oFile.Open(pszPath, GENERIC_READ);

	// Allocate a buffer for the entire file.
	size_t nLength = static_cast<size_t>(oFile.Size());

	vBuffer.resize(nLength);

	// Read the entire contents.
	if (nLength > 0)
		oFile.Read(&vBuffer.front(), nLength);

	oFile.Close();

	return vBuffer.size();
}

////////////////////////////////////////////////////////////////////////////////
//! Read the entire contents of a text file. It returns the number of characters
//! read.

size_t CFile::ReadTextFile(const tchar* pszPath, CString& strContents, TextFormat& eFormat)
{
	std::vector<byte> vBuffer;

	// Read the file into our temporary buffer.
	ReadFile(pszPath, vBuffer);

	size_t nChars  = 0;
	size_t nOffset = 0;

	// Contains a Unicode BOM?.
	if ( (vBuffer.size() >= 2) && (vBuffer[0] == 0xFF) && (vBuffer[1] == 0xFE) )
	{
		eFormat = UNICODE_TEXT;
		nChars  = (vBuffer.size() - 2) / sizeof(wchar_t);
		nOffset = 1;
	}
	// Contains a UTF-8 BOM?
	else if ( (vBuffer.size() >= 3) && (vBuffer[0] == 0xEF) && (vBuffer[1] == 0xBB) && (vBuffer[2] == 0xBF) )
	{
		eFormat = ANSI_TEXT;
		nChars  = vBuffer.size() - 3;
		nOffset = 3;
	}
	// No BOM.
	else
	{
		eFormat = ANSI_TEXT;
		nChars  = vBuffer.size();
		nOffset = 0;
	}

	// Allocate the final string buffer.
	strContents.BufferSize(nChars+1);

	if (nChars > 0)
	{
		// Copy the contents to the return buffer.
		if (eFormat == ANSI_TEXT)
		{
			const char* pszBegin = reinterpret_cast<const char*>(&vBuffer.front()) + nOffset;
			const char* pszEnd   = pszBegin + nChars;

#ifdef ANSI_BUILD
			std::copy(pszBegin, pszEnd, strContents.Buffer());
#else
			Core::ansiToWide(pszBegin, pszEnd, strContents.Buffer());
#endif
		}
		else // (eFormat == UNICODE_TEXT)
		{
			const wchar_t* pszBegin = reinterpret_cast<const wchar_t*>(&vBuffer.front()) + nOffset;
			const wchar_t* pszEnd   = pszBegin + nChars;

#ifdef ANSI_BUILD
			Core::wideToAnsi(pszBegin, pszEnd, strContents.Buffer());
#else
			std::copy(pszBegin, pszEnd, strContents.Buffer());
#endif
		}
	}

	// Ensure string is terminated.
	*(strContents.Buffer()+nChars) = TXT('\0');

	return nChars;
}

////////////////////////////////////////////////////////////////////////////////
//! Read the entire contents of a text file.

tstring CFile::ReadTextFile(const tchar* pszPath)
{
	CString    str;
	TextFormat eFormat;

	size_t nChars = ReadTextFile(pszPath, str, eFormat);

	return tstring(str.Buffer(), str.Buffer()+nChars);
}

////////////////////////////////////////////////////////////////////////////////
//! Write the entire contents of a binary file.

void CFile::WriteFile(const tchar* pszPath, const std::vector<byte>& vBuffer)
{
	CFile oFile;

	oFile.Create(pszPath);

	if (vBuffer.size() > 0)
		oFile.Write(&vBuffer.front(), vBuffer.size());

	oFile.Close();
}

////////////////////////////////////////////////////////////////////////////////
//! Write the entire contents of a text file.

void CFile::WriteTextFile(const tchar* pszPath, const CString& strContents, TextFormat eFormat)
{
	size_t nChars = strContents.Length();

	// Allocate the binary data buffer.
	std::vector<byte> vBuffer;

	if (eFormat == ANSI_TEXT)
		vBuffer.resize(Core::numBytes<char>(nChars));
	else
		vBuffer.resize(Core::numBytes<wchar_t>(nChars) + 2);

	// Write Unicode header, if required.
	if (eFormat == UNICODE_TEXT)
	{
		vBuffer[0] = 0xFF;
		vBuffer[1] = 0xFE;
	}

	if (nChars > 0)
	{
#ifdef ANSI_BUILD
		const char* pszBegin = strContents.Buffer();
		const char* pszEnd   = pszBegin + nChars;
#else
		const wchar_t* pszBegin = strContents.Buffer();
		const wchar_t* pszEnd   = pszBegin + nChars;
#endif

		// Copy the contents to the write buffer.
		if (eFormat == ANSI_TEXT)
		{
			char* pszDest = reinterpret_cast<char*>(&vBuffer.front());

#ifdef ANSI_BUILD
			std::copy(pszBegin, pszEnd, pszDest);
#else
			Core::wideToAnsi(pszBegin, pszEnd, pszDest);
#endif
		}
		else // (eFormat == UNICODE_TEXT)
		{
			wchar_t* pszDest = reinterpret_cast<wchar_t*>(&vBuffer.front()+2);

#ifdef ANSI_BUILD
			Core::ansiToWide(pszBegin, pszEnd, pszDest);
#else
			std::copy(pszBegin, pszEnd, pszDest);
#endif
		}
	}

	WriteFile(pszPath, vBuffer);
}
