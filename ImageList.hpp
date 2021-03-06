/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		IMAGELIST.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CImageList class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef IMAGELIST_HPP
#define IMAGELIST_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <commctrl.h>

/******************************************************************************
**
** This class wraps the ImageList image collection.
**
*******************************************************************************
*/

class CImageList /*: private NotCopyable*/
{
public:
	//
	// Constructors/Destructor.
	//
	CImageList();
	~CImageList();

	void LoadRsc(uint nRscID, uint nImgWidth, COLORREF crMask, bool bOwner = false);

	//
	// Properties.
	//
	HIMAGELIST Handle() const;
	bool       Owner() const;

protected:
	//
	// Members.
	//
	HIMAGELIST	m_hImageList;
	bool		m_bOwner;

private:
	// NotCopyable.
	CImageList(const CImageList&);
	CImageList& operator=(const CImageList&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HIMAGELIST CImageList::Handle() const
{
	return m_hImageList;
}

inline bool CImageList::Owner() const
{
	return m_bOwner;
}

#endif // IMAGELIST_HPP
