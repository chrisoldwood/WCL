/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DOC.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDoc class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef DOC_HPP
#define DOC_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Path.hpp"

/******************************************************************************
** 
** This is the base class for all documents.
**
*******************************************************************************
*/

class CDoc
{
public:
	//
	// Constructors/Destructor.
	//
	CDoc();
	virtual ~CDoc();
	
	//
	// Attributes.
	//
	virtual bool Modified() const;
	virtual bool Untitled() const;

	//
	// Accessors & mutators.
	//
	const CPath& Path() const;
	void Path(const char* pszPath);

	virtual bool Load();
	virtual bool Save();

protected:
	//
	// Members.
	//
	CPath	m_Path;

	//
	// Persistance methods.
	//
	virtual void Read (WCL::IInputStream&  rStream);
	virtual void Write(WCL::IOutputStream& rStream);

private:
	// Disallow copies.
	CDoc(const CDoc&);
	void operator=(const CDoc&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline bool CDoc::Modified() const
{
	return false;
}

inline bool CDoc::Untitled() const
{
	return (m_Path == "Untitled");
}

inline const CPath& CDoc::Path() const
{
	return m_Path;
}

inline void CDoc::Path(const char* pszPath)
{
	ASSERT(pszPath != NULL);

	m_Path = pszPath;
}

#endif //DOC_HPP
