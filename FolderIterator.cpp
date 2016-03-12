////////////////////////////////////////////////////////////////////////////////
//! \file   FolderIterator.cpp
//! \brief  The FolderIterator class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "FolderIterator.hpp"
#include "WCL/Win32Exception.hpp"
#include <Core/BadLogicException.hpp>
#include <Core/FileSystem.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor. This creates an iterator that is the 'end' iterator.

FolderIterator::FolderIterator()
	: m_strFolder()
	, m_strMask()
	, m_nFlags(NONE)
	, m_hFindFile(INVALID_HANDLE_VALUE)
	, m_oFindData()
{
#ifdef _DEBUG
	memset(&m_oFindData, 0xCCCC, sizeof(m_oFindData));
#endif
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from the folder to iterate and the file mask to use.

FolderIterator::FolderIterator(const tstring& strFolder, const tstring& strMask, int nFlags)
	: m_strFolder(strFolder)
	, m_strMask(strMask)
	, m_nFlags(nFlags)
	, m_hFindFile(INVALID_HANDLE_VALUE)
	, m_oFindData()
{
#ifdef _DEBUG
	memset(&m_oFindData, 0xCCCC, sizeof(m_oFindData));
#endif

	Begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

FolderIterator::~FolderIterator()
{
	Reset();
}

////////////////////////////////////////////////////////////////////////////////
//! Dereference operator.

const tchar* FolderIterator::operator*() const
{
	if (!IsValid())
		throw Core::BadLogicException(TXT("Attempt to dereference an invalid iterator"));

	return m_oFindData.cFileName;
}

////////////////////////////////////////////////////////////////////////////////
//! Advance the iterator.

FolderIterator& FolderIterator::operator++()
{
	if (!IsValid())
		throw Core::BadLogicException(TXT("Attempt to advance an invalid iterator"));

	Next();

	// Skip files and/or folders if required.
	while ( IsValid()
		 && ( (((m_oFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) && ((m_nFlags & FIND_FOLDERS) == 0))
		   || (((m_oFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) && ((m_nFlags & FIND_FILES)   == 0)) ) )
	{
		Next();
	}

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//! Compare two iterators for equivalence.

bool FolderIterator::Equals(const FolderIterator& RHS) const
{
	// Handles differ?
	if (m_hFindFile != RHS.m_hFindFile)
		return false;

	// Both at end?
	if (m_hFindFile == INVALID_HANDLE_VALUE)
		return true;

	ASSERT((m_oFindData.dwReserved0     != 0xCCCC) && (m_oFindData.dwReserved0     != 0xDDDD));
	ASSERT((RHS.m_oFindData.dwReserved0 != 0xCCCC) && (RHS.m_oFindData.dwReserved0 != 0xDDDD));

	// Compare filenames.
	return (tstricmp(m_oFindData.cFileName, RHS.m_oFindData.cFileName) == 0);
}

////////////////////////////////////////////////////////////////////////////////
//! Start the enumeration.

void FolderIterator::Begin()
{
	ASSERT(!IsValid());

	// Create the full query.
	tstring strQuery = m_strFolder;

	if ( (!strQuery.empty()) && (strQuery[strQuery.length()-1] != TXT('\\')) )
		strQuery += TXT('\\');

	strQuery += m_strMask;

#ifdef _DEBUG
	memset(&m_oFindData, 0, sizeof(m_oFindData));
#endif

	// Start the enumeration.
	HANDLE hFindFile = ::FindFirstFile(strQuery.c_str(), &m_oFindData);

	if (hFindFile == INVALID_HANDLE_VALUE)
	{
		DWORD dwLastError = ::GetLastError();

		// Enumeration failed?
		if (dwLastError != ERROR_FILE_NOT_FOUND)
			throw Win32Exception(Core::fmt(TXT("Failed to find files with query '%s'"), strQuery.c_str()));
	}

	// Update state.
	m_hFindFile = hFindFile;

	// Skip the pseudo folders "." and "..".
	while ( IsValid()
		 && ( (tstricmp(m_oFindData.cFileName, TXT(".")) == 0)
		   || (tstricmp(m_oFindData.cFileName, TXT("..")) == 0) ) )
	{
		Next();
	}

	// Skip files and/or folders if required.
	while ( IsValid()
		 && ( (((m_oFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) && ((m_nFlags & FIND_FOLDERS) == 0))
		   || (((m_oFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) && ((m_nFlags & FIND_FILES)   == 0)) ) )
	{
		Next();
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Continue the enumeration.

void FolderIterator::Next()
{
	ASSERT(IsValid());

	// Get next entry.
	BOOL nResult = ::FindNextFile(m_hFindFile, &m_oFindData);

	if (nResult == 0)
	{
		DWORD dwLastError = ::GetLastError();

		// Enumeration failed?
		if (dwLastError != ERROR_NO_MORE_FILES)
			throw Win32Exception(Core::fmt(TXT("Failed to continue enumerating folder '%s'"), m_strFolder.c_str()));

		// Enumeration completed.
		Reset();
	}
}

////////////////////////////////////////////////////////////////////////////////
//! End the enumeration of the folder.

void FolderIterator::Reset()
{
	// Close the underlying handle.
	if (m_hFindFile != INVALID_HANDLE_VALUE)
		::FindClose(m_hFindFile);

	// Reset state.
	m_hFindFile = INVALID_HANDLE_VALUE;
#ifdef _DEBUG
	memset(&m_oFindData, 0xDDDD, sizeof(m_oFindData));
#endif
}

////////////////////////////////////////////////////////////////////////////////
//! Find all files in the folder.

FileNames FindFilesInFolder(const tstring& folder)
{
	return FindFilesInFolder(folder, TXT("*.*"));
}

////////////////////////////////////////////////////////////////////////////////
//! Find all files in the folder matching the file mask.

FileNames FindFilesInFolder(const tstring& folder, const tstring& mask)
{
	WCL::FolderIterator end;
	WCL::FolderIterator it(folder, mask, WCL::FolderIterator::FIND_FILES);

	FileNames fileNames; 

	for (; it != end; ++it)
		fileNames.insert(*it);

	return fileNames;
}

////////////////////////////////////////////////////////////////////////////////
//! Find all folders in the folder.

FolderNames FindFoldersInFolder(const tstring& folder)
{
	WCL::FolderIterator end;
	WCL::FolderIterator it(folder, TXT("*.*"), WCL::FolderIterator::FIND_FOLDERS);

	FolderNames folderNames; 

	for (; it != end; ++it)
		folderNames.insert(*it);

	return folderNames;
}

////////////////////////////////////////////////////////////////////////////////
//! Find all files in the folder and its subfolders that match the file mask.

static void FindFilesInFolderRecursively(const tstring& folder, const tstring& mask, PathNames& pathNames)
{
	typedef FolderNames::const_iterator FolderNameCIter;
	typedef FileNames::const_iterator FileNameCIter;

	FolderNames folderName = FindFoldersInFolder(folder);

	for (FolderNameCIter it = folderName.begin(); it != folderName.end(); ++it)
		FindFilesInFolderRecursively(Core::combinePaths(folder, *it), mask, pathNames);

	FileNames filesNames = FindFilesInFolder(folder, mask);

	for (FileNameCIter it = filesNames.begin(); it != filesNames.end(); ++it)
		pathNames.insert(Core::combinePaths(folder, *it));
}

////////////////////////////////////////////////////////////////////////////////
//! Find all files in the folder and its subfolders that match the file mask.

PathNames FindFilesInFolderRecursively(const tstring& folder, const tstring& mask)
{
	PathNames pathNames;

	FindFilesInFolderRecursively(folder, mask, pathNames);

	return pathNames;
}

//namespace WCL
}
