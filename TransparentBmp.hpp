/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TRANSPARENTBMP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CTransparentBmp class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TRANSPARENTBMP_HPP
#define TRANSPARENTBMP_HPP

/******************************************************************************
** 
** This class is used to create transparent bitmaps.
**
*******************************************************************************
*/

class CTransparentBmp
{
public:
	//
	// Constructors/Destructor.
	//
	CTransparentBmp();
	~CTransparentBmp();

	void LoadRsc(uint iRscID, COLORREF clrTransparent);
	
	//
	// Member access.
	//
	const CBitmap& Mask()  const;
	const CBitmap& Image() const;
	const CSize&   Size()  const;
	
protected:
	//
	// Members.
	//
	CBitmap		m_bmpMask;			// The image mask.
	CBitmap		m_bmpImage;			// The image.
	CSize		m_Size;				// The images dimensions.
	COLORREF	m_clrTransparent;	// The colour used for transparency.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline const CBitmap& CTransparentBmp::Mask() const
{
	return m_bmpMask;
}

inline const CBitmap& CTransparentBmp::Image() const
{
	return m_bmpImage;
}

inline const CSize& CTransparentBmp::Size() const
{
	ASSERT(m_bmpMask.Handle()  != NULL);
	ASSERT(m_bmpImage.Handle() != NULL);
	
	return m_Size;
}

#endif //TRANSPARENTBMP_HPP
