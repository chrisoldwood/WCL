////////////////////////////////////////////////////////////////////////////////
//! \file   FolderIterator.hpp
//! \brief  The FolderIterator class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_FOLDERITERATOR_HPP
#define WCL_FOLDERITERATOR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! An iterator for enumerating the file and directory names in a file-system
//! folder.

class FolderIterator /*: private Core::NotCopyable*/
{
public:
	//! The search flags.
	enum Flag
	{
		FIND_FOLDERS	= 0x0001,						//!< Find folders.
		FIND_FILES		= 0x0002,						//!< Find files.

		NONE			= 0x0000,						//!< The initial state.
		DEFAULT			= (FIND_FOLDERS | FIND_FILES),	//!< The default flags.
	};

	//! Default constructor.
	FolderIterator();

	//! Construction from the folder to iterate and the file mask to use.
	FolderIterator(const tstring& strFolder, const tstring& strMask = TXT("*.*"), int nFlags = DEFAULT); // throw(Win32Exception)

	//! Destructor.
	~FolderIterator();

	//
	// Properties.
	//

	//! Get the name of the folder.
	const tstring& Folder() const;

	//! Get the mask used for filtering.
	const tstring& Mask() const;

	//
	// Operators.
	//

	//! Dereference operator.
	const tchar* operator*() const;

	//! Advance the iterator.
	FolderIterator& operator++();

	//
	// Methods.
	//

	//! Compare two iterators for equivalence.
	bool Equals(const FolderIterator& RHS) const;

private:
	//
	// Members.
	//
	tstring			m_strFolder;	//!< The folder to iterate.
	tstring			m_strMask;		//!< The file mask to use.
	int				m_nFlags;		//!< The search flags.
	HANDLE			m_hFindFile;	//!< The underlying Win32 handle.
	WIN32_FIND_DATA	m_oFindData;	//!< The underlying enumeration data.

	//
	// Internal methods.
	//

	//! Check if the iterator is valid.
	bool IsValid() const;

	//! Start the enumeration.
	void Begin(); // throw(Win32Exception)

	//! Continue the enumeration.
	void Next(); // throw(Win32Exception)

	//! End the enumeration of the folder.
	void Reset();

	// NotCopyable.
	FolderIterator(const FolderIterator&);
	FolderIterator& operator=(const FolderIterator&);
};

////////////////////////////////////////////////////////////////////////////////
//! Get the name of the folder.

inline const tstring& FolderIterator::Folder() const
{
	return m_strFolder;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the mask used for filtering.

inline const tstring& FolderIterator::Mask() const
{
	return m_strMask;
}

////////////////////////////////////////////////////////////////////////////////
//! Check if the iterator is valid.

inline bool FolderIterator::IsValid() const
{
	return (m_hFindFile != INVALID_HANDLE_VALUE);
}

////////////////////////////////////////////////////////////////////////////////
//! Global equivalence operator for a folder iterator.

inline bool operator==(const FolderIterator& LHS, const FolderIterator& RHS)
{
	return LHS.Equals(RHS);
}

////////////////////////////////////////////////////////////////////////////////
//! Global non-equivalence operator for a folder iterator.

inline bool operator!=(const FolderIterator& LHS, const FolderIterator& RHS)
{
	return !operator==(LHS, RHS);
}

//namespace WCL
}

#endif // WCL_FOLDERITERATOR_HPP
