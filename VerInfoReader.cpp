////////////////////////////////////////////////////////////////////////////////
//! \file   VerInfoReader.cpp
//! \brief  The VerInfoReader class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "VerInfoReader.hpp"
#include "Win32Exception.hpp"
#include <Core/StringUtils.hpp>
#include <winver.h>
#include <algorithm>

#ifdef _MSC_VER
// Add .lib to linker.
#pragma comment(lib, "version")
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
// Constants.

const tchar* VerInfoReader::COMMENTS          = TXT("Comments");
const tchar* VerInfoReader::COMPANY_NAME      = TXT("CompanyName");
const tchar* VerInfoReader::FILE_DESCRIPTION  = TXT("FileDescription");
const tchar* VerInfoReader::FILE_VERSION      = TXT("FileVersion");
const tchar* VerInfoReader::INTERNAL_NAME     = TXT("InternalName");
const tchar* VerInfoReader::LEGAL_COPYRIGHT   = TXT("LegalCopyright");
const tchar* VerInfoReader::LEGAL_TRADEMARKS  = TXT("LegalTrademarks");
const tchar* VerInfoReader::ORIGINAL_FILENAME = TXT("OriginalFilename");
const tchar* VerInfoReader::PRODUCT_NAME      = TXT("ProductName");
const tchar* VerInfoReader::PRODUCT_VERSION   = TXT("ProductVersion");
const tchar* VerInfoReader::PRIVATE_BUILD     = TXT("PrivateBuild");
const tchar* VerInfoReader::SPECIAL_BUILD     = TXT("SpecialBuild");

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

VerInfoReader::VerInfoReader()
	: m_bOpen(false)
	, m_dwBufSize(0)
	, m_pDefTrans(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

VerInfoReader::~VerInfoReader()
{
	Close();
}

////////////////////////////////////////////////////////////////////////////////
//! Open the file for reading.

void VerInfoReader::Open(const tstring& strFileName)
{
	DWORD dwHandle;

	// Open the file for reading.
	DWORD dwSize = ::GetFileVersionInfoSize(strFileName.c_str(), &dwHandle);

	if (dwSize == 0)
		throw Win32Exception(::GetLastError(), TXT("Failed to open the file for reading"));

	Buffer pBuffer(new byte[dwSize]);

	BOOL bResult = ::GetFileVersionInfo(strFileName.c_str(), dwHandle, dwSize, pBuffer.Get());

	if (bResult == 0)
		throw Win32Exception(::GetLastError(), TXT("Failed to open the file for reading"));

	// Update state.
	m_bOpen       = true;
	m_strFileName = strFileName;
	m_dwBufSize   = dwSize;
	m_pBuffer.Reset(pBuffer.Detach());
}

////////////////////////////////////////////////////////////////////////////////
//! Close the file.

void VerInfoReader::Close()
{
	// Reset state.
	m_bOpen = false;
	m_strFileName.clear();
	m_dwBufSize = 0;
	m_pBuffer.Reset();
	m_pDefTrans = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the main file information block.

const VS_FIXEDFILEINFO* VerInfoReader::GetFileInfo() const
{
	ASSERT(m_bOpen);
	ASSERT(m_pBuffer.Get() != nullptr);

	void* pValue = nullptr;
	uint  nBytes = 0;

	tchar* lpSubBlock = const_cast<tchar*>(TXT("\\"));

	// Read the block of translations.
	BOOL bResult = ::VerQueryValue(m_pBuffer.Get(), lpSubBlock, &pValue, &nBytes);

	if ( (bResult == 0) || (pValue == nullptr) )
		throw Win32Exception(NO_ERROR, TXT("Failed to read the file information block"));

	ASSERT(nBytes == sizeof(VS_FIXEDFILEINFO));

	const VS_FIXEDFILEINFO* pFileInfo = static_cast<VS_FIXEDFILEINFO*>(pValue);

	return pFileInfo;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the sequence of available translations.

size_t VerInfoReader::GetTranslations(TranslationIter& itBegin, TranslationIter& itEnd) const
{
	ASSERT(m_bOpen);
	ASSERT(m_pBuffer.Get() != nullptr);

	void* pValue = nullptr;
	uint  nBytes = 0;

	tchar* lpSubBlock = const_cast<tchar*>(TXT("\\VarFileInfo\\Translation"));

	// Get the block of translations.
	/*BOOL bResult =*/ ::VerQueryValue(m_pBuffer.Get(), lpSubBlock, &pValue, &nBytes);

	// Convert raw buffer to output iterator pair.
	size_t nCount = nBytes / sizeof(Translation);

	itBegin = static_cast<TranslationIter>(pValue);
	itEnd   = itBegin + nCount;

	return nCount;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the default translation. The default translation is the first one in
//! the sequence if more than one is present. The method returns NULL if there
//! are no translations in the file.

const VerInfoReader::Translation* VerInfoReader::GetDefaultTranslation() const
{
	// Find default on first request.
	if (m_pDefTrans == nullptr)
	{
		TranslationIter itBegin;
		TranslationIter itEnd;

		// Cache default translation.
		if (GetTranslations(itBegin, itEnd) > 0)
			m_pDefTrans = itBegin;
	}

	return m_pDefTrans;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the string value for an entry. If the entry doesn't exist it just
//! returns an empty string.

tstring VerInfoReader::GetStringValue(const Translation& oTranslation, const tchar* pszName)
{
	ASSERT(m_bOpen);
	ASSERT(m_pBuffer.Get() != nullptr);
	ASSERT(pszName != nullptr);

	// Format the path to the value.
	tstring strEntry = Core::Fmt(TXT("\\StringFileInfo\\%04hX%04hX\\%s"),
										oTranslation.m_wLanguage, oTranslation.m_wCodePage, pszName);

	void* pValue = nullptr;
	uint  nChars = 0;

	// Read the value.
	BOOL bResult = ::VerQueryValue(m_pBuffer.Get(), const_cast<tchar*>(strEntry.c_str()), &pValue, &nChars);

	tstring strResult;

	if (bResult != 0)
	{
		// Create the return value from the buffer.
		// NB: We have to strip the nul terminator, if present.
		const tchar* pszBegin = static_cast<const tchar*>(pValue);
		const tchar* pszEnd   = std::find(pszBegin, pszBegin + nChars, TXT('\0'));

		strResult = tstring(pszBegin, pszEnd);
	}

	return strResult;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the string value for an entry from the default translation.

tstring VerInfoReader::GetStringValue(const tchar* pszName)
{
	const Translation* pDefTrans = GetDefaultTranslation();

	if (pDefTrans == nullptr)
		return TXT("");

	return GetStringValue(*pDefTrans, pszName);
}

////////////////////////////////////////////////////////////////////////////////
//! Check if the file has a Version Information resource.

bool VerInfoReader::HasVersionInfo(const tstring& strFileName)
{
	DWORD dwHandle;

	return (::GetFileVersionInfoSize(strFileName.c_str(), &dwHandle) != 0);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the string value for an entry from the default translation in the specified file.

tstring VerInfoReader::GetStringValue(const tstring& strFileName, const tchar* pszName)
{
	// No version information resource?
	if (!HasVersionInfo(strFileName))
		return TXT("");

	VerInfoReader oReader;

	// Open the file and read the value.
	oReader.Open(strFileName);

	return oReader.GetStringValue(pszName);
}

//namespace WCL
}
