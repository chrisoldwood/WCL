////////////////////////////////////////////////////////////////////////////////
//! \file   VerInfoReader.hpp
//! \brief  The VerInfoReader class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_VERINFOREADER_HPP
#define WCL_VERINFOREADER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/ArrayPtr.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A reader for the Version Information embedded inside the resources of an .exe
//! or .dll.

class VerInfoReader /*: private NotCopyable*/
{
public:
	////////////////////////////////////////////////////////////////////////////
	//! The language details of a specific Version Information translation .

	struct Translation
	{
		WORD	m_wLanguage;	//!< The language ID.
		WORD	m_wCodePage;	//!< The Code Page.
	};

	//! The iterator type for the translations sequence.
	typedef const Translation* TranslationIter;

	//! Default constructor.
	VerInfoReader();

	//! Destructor.
	~VerInfoReader();

	//
	// Properties.
	//

	//! Get if the file is open for reading.
	bool IsOpen() const;

	//! Get the name of the open file.
	const tstring& FileName() const;

	//
	// Methods.
	//

	//! Open the file for reading.
	void Open(const tstring& strFileName); // throw(Win32Exception)

	//! Close the file.
	void Close();

	//! Get the main file information block.
	const VS_FIXEDFILEINFO* GetFileInfo() const; // throw(Win32Exception)

	//! Get the sequence of available translations.
	size_t GetTranslations(TranslationIter& itBegin, TranslationIter& itEnd) const;

	//! Get the default translation.
	const Translation* GetDefaultTranslation() const;

	//! Get the string value for an entry.
	tstring GetStringValue(const Translation& oTranslation, const tchar* pszName);

	//! Get the string value for an entry from the default translation.
	tstring GetStringValue(const tchar* pszName);

	//
	// Class methods.
	//

	//! Check if the file has a Version Information resource.
	static bool HasVersionInfo(const tstring& strFileName);

	//! Get the string value for an entry from the default translation in the specified file.
	static tstring GetStringValue(const tstring& strFileName, const tchar* pszName);

	//
	// Constants.
	//
	static const tchar* COMMENTS;
	static const tchar* COMPANY_NAME;
	static const tchar* FILE_DESCRIPTION;
	static const tchar* FILE_VERSION;
	static const tchar* INTERNAL_NAME;
	static const tchar* LEGAL_COPYRIGHT;
	static const tchar* LEGAL_TRADEMARKS;
	static const tchar* ORIGINAL_FILENAME;
	static const tchar* PRODUCT_NAME;
	static const tchar* PRODUCT_VERSION;
	static const tchar* PRIVATE_BUILD;
	static const tchar* SPECIAL_BUILD;

private:
	//! The resource buffer type.
	typedef Core::ArrayPtr<byte> Buffer;

	//
	// Members.
	//
	bool						m_bOpen;			//!< Flag to signal if open for reading.
	tstring						m_strFileName;		//!< The name of the file being read.
	DWORD						m_dwBufSize;		//!< The size of the resource block.
	Buffer						m_pBuffer;			//!< The resource block buffer.
	mutable const Translation*	m_pDefTrans;		//!< The default translation.

private:
	// NotCopyable.
	VerInfoReader(const VerInfoReader&);
	VerInfoReader& operator=(const VerInfoReader&);
};

////////////////////////////////////////////////////////////////////////////////
//! Get if the file is open for reading.

inline bool VerInfoReader::IsOpen() const
{
	return m_bOpen;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the name of the open file.

inline const tstring& VerInfoReader::FileName() const
{
	return m_strFileName;
}

//namespace WCL
}

#endif // WCL_VERINFOREADER_HPP
