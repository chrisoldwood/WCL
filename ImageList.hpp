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

/******************************************************************************
** 
** This class wraps the ImageList image collection.
**
*******************************************************************************
*/

class CImageList
{
public:
	//
	// Constructors/Destructor.
	//
	CImageList();
	~CImageList();
	
	void LoadRsc(uint nRscID, int nImgWidth, COLORREF crMask, bool bOwner = false);

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
