/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ICON.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CIcon class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CIcon::CIcon()
	: m_hIcon(NULL)
	, m_bOwner(false)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CIcon::~CIcon()
{
	// Delete if valid and we own it.
	if ( (m_hIcon) && (m_bOwner) )
		::DestroyIcon(m_hIcon);
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads the icon from the resource file.
**
** Parameters:	iRscID		The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIcon::LoadRsc(uint nRscID)
{
	ASSERT(m_hIcon == NULL);

	m_hIcon  = ::LoadIcon(CModule::This().Handle(), MAKEINTRESOURCE(nRscID));
	m_bOwner = false;

	ASSERT(m_hIcon != NULL);
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads the icon from the resource file.
**				NB: This version uses LoadImage() to get a specifc sized icon.
**
** Parameters:	nRscID				The resource ID.
**				nWidth, nHeight		The desired icon size.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIcon::LoadRsc(uint nRscID, int nWidth, int nHeight)
{
	ASSERT(m_hIcon == NULL);

	m_hIcon  = (HICON) ::LoadImage(CModule::This().Handle(), MAKEINTRESOURCE(nRscID), IMAGE_ICON, nWidth, nHeight, LR_SHARED);
	m_bOwner = false;

	ASSERT(m_hIcon != NULL);
}