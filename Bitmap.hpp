/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BITMAP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CBitmap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BITMAP_HPP
#define BITMAP_HPP

// Forward reference.
class CDC;

/******************************************************************************
** 
** This encapsulates a device dependant bitmap.
**
*******************************************************************************
*/

class CBitmap
{
public:
	//
	// Constructors/Destructor.
	//
	CBitmap();
	~CBitmap();

	void Create(const CSize& rSize);
	void Create(const CSize& rSize, const CDC& rDC);
	void LoadRsc(uint iRscID);
		
	//
	// Member access.
	//
	HBITMAP Handle() const;
	CSize Size() const;
	
protected:
	//
	// Members.
	//
	HBITMAP	m_hBitmap;
	CSize	m_Size;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HBITMAP CBitmap::Handle() const
{
	return m_hBitmap;
}

inline CSize CBitmap::Size() const
{
	ASSERT(m_hBitmap);
	
	return m_Size;
}

#endif //BITMAP_HPP
