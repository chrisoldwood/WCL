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
	: m_hFile(HFILE_ERROR)
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
	if (m_hFile != HFILE_ERROR)
		_lclose(m_hFile);
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
	m_eMode = WriteOnly;
	m_Path  = pszPath;
	m_hFile = _lcreat(m_Path, 0);

	// Error?
	if (m_hFile == HFILE_ERROR)
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

void CFile::Open(const char* pszPath, Mode eMode)
{
	m_eMode = eMode;
	m_Path  = pszPath;
	m_hFile = _lopen(m_Path, m_eMode);
	
	// Error?
	if (m_hFile == HFILE_ERROR)
	{
		// File exists?
		if (!m_Path.Exists())
			throw CFileException(CFileException::E_PATH_INVALID, *this);

		// Trying to write and file is read-only ?
		if ( ((eMode == WriteOnly) || (eMode == ReadWrite)) && (m_Path.ReadOnly()) )
			throw CFileException(CFileException::E_READ_ONLY, *this);
		
		// Unknown reason.
		throw CFileException(CFileException::E_OPEN_FAILED, *this);
	}

	// Get EOF by seeking to the end.
	m_lEOF = Seek(0, End);
	Seek(0, Start);
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
	ASSERT(m_hFile != HFILE_ERROR);

	_lclose(m_hFile);

	// Reset members.
	m_hFile = HFILE_ERROR;
	m_eMode = None;
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
	ASSERT(m_hFile != HFILE_ERROR);
	ASSERT( (m_eMode == ReadOnly) || (m_eMode == ReadWrite) );

	if (_lread(m_hFile, pBuffer, iNumBytes) != iNumBytes)
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
	ASSERT(m_hFile != HFILE_ERROR);
	ASSERT( (m_eMode == WriteOnly) || (m_eMode == ReadWrite) );

	if (_lwrite(m_hFile, (const char*)pBuffer, iNumBytes) != iNumBytes)
		throw CFileException(CFileException::E_WRITE_FAILED, *this);
}

/******************************************************************************
** Method:		Seek()
**
** Description:	Core method for changing the stream pointer.
**
** Parameters:	lPos		The new position.
**				eOrigin		The origin from where to seek.
**
** Returns:		The new stream pointer.
**
** Exceptions:	CFileException on error.
**
*******************************************************************************
*/

ulong CFile::Seek(ulong lPos, Origin eOrigin)
{
	ASSERT(m_hFile != HFILE_ERROR);

	// Try the seek.
	LONG lNewPos = _llseek(m_hFile, lPos, eOrigin);

	// Error?
	if (lNewPos == HFILE_ERROR)
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
	ASSERT(m_hFile != HFILE_ERROR);
	ASSERT(m_eMode == ReadOnly);

	return (Seek(0, Current) >= m_lEOF);
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
