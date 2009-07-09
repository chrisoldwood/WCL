/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FILEEXCEPTION.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CFileException class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "FileException.hpp"
#include "Path.hpp"
#include "StrCvt.hpp"
#include <Core/StringUtils.hpp>

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFileException::CFileException(int eErrCode, const CPath& rPath, DWORD dwLastError)
{
	CString strLastError = CStrCvt::FormatError(dwLastError);

	// Convert error to string.
	switch(eErrCode)
	{
		case E_INVALID_FILE:
			m_strDetails = Core::Fmt(TXT("The file does not exist:\n\n%s"), rPath.c_str());
			break;

		case E_INVALID_FOLDER:
			m_strDetails = Core::Fmt(TXT("The folder does not exist:\n\n%s"), rPath.c_str());
			break;

		case E_OPEN_FAILED:
			m_strDetails = Core::Fmt(TXT("Failed to open file:\n\n%s\n\n%s"), rPath.c_str(), strLastError.c_str());
			break;

		case E_CREATE_FAILED:
			m_strDetails = Core::Fmt(TXT("Failed to create file:\n\n%s\n\n%s"), rPath.c_str(), strLastError.c_str());
			break;

		case E_READ_ONLY:
			m_strDetails = Core::Fmt(TXT("Failed to open file:\n\n%s\n\nThe file is read-only"), rPath.c_str());
			break;

		case E_PATH_INVALID:
			m_strDetails = Core::Fmt(TXT("Failed to open file:\n\n%s\n\nThe file does not exist"), rPath.c_str());
			break;

		case E_FORMAT_INVALID:
			m_strDetails = Core::Fmt(TXT("The file format is incorrect for:\n\n%s"), rPath.c_str());
			break;

		case E_VERSION_INVALID:
			m_strDetails = Core::Fmt(TXT("The file version is unsupported for:\n\n%s"), rPath.c_str());
			break;

		case E_READ_FAILED:
			m_strDetails = Core::Fmt(TXT("An error occured reading from:\n\n%s\n\n%s"), rPath.c_str(), strLastError.c_str());
			break;

		case E_WRITE_FAILED:
			m_strDetails = Core::Fmt(TXT("An error occured writing to:\n\n%s\n\n%s"), rPath.c_str(), strLastError.c_str());
			break;

		case E_SEEK_FAILED:
			m_strDetails = Core::Fmt(TXT("An error occured seeking in:\n\n%s\n\n%s"), rPath.c_str(), strLastError.c_str());
			break;

		// Shouldn't happen!
		default:
			ASSERT_FALSE();
			break;
	}
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFileException::~CFileException() throw()
{
}
