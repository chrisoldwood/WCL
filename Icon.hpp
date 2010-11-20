/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ICON.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CIcon class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ICON_HPP
#define ICON_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
**
** This class wraps a standard GDI icon.
**
*******************************************************************************
*/

class CIcon /*: private NotCopyable*/
{
public:
	//
	// Constructors/Destructor.
	//
	CIcon();
	CIcon(uint nRscID);
	CIcon(uint nRscID, uint nWidth, uint nHeight);
	~CIcon();

	void LoadRsc(uint nRscID);
	void LoadRsc(uint nRscID, uint nWidth, uint nHeight);
	void LoadRsc(const tchar* pszRsc);

	//
	// Member access.
	//
	HICON Handle() const;

protected:
	//
	// Members.
	//
	HICON	m_hIcon;
	bool	m_bOwner;

private:
	// NotCopyable.
	CIcon(const CIcon&);
	CIcon& operator=(const CIcon&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HICON CIcon::Handle() const
{
	return m_hIcon;
}

#endif // ICON_HPP
