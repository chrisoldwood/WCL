/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ICON.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CIcon class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Icon.hpp"
#include "Module.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	Default constructor.
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
** Method:		Constructor.
**
** Description:	Construction from a resource.
**
** Parameters:	nRscID	The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CIcon::CIcon(uint nRscID)
	: m_hIcon(NULL)
	, m_bOwner(false)
{
	LoadRsc(nRscID);
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	Construction from a resource.
**
** Parameters:	nRscID				The resource ID.
**				nWidth, nHeight		The desired icon size.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CIcon::CIcon(uint nRscID, uint nWidth, uint nHeight)
	: m_hIcon(NULL)
	, m_bOwner(false)
{
	LoadRsc(nRscID, nWidth, nHeight);
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

void CIcon::LoadRsc(uint nRscID, uint nWidth, uint nHeight)
{
	ASSERT(m_hIcon == NULL);

	m_hIcon  = (HICON) ::LoadImage(CModule::This().Handle(), MAKEINTRESOURCE(nRscID), IMAGE_ICON, nWidth, nHeight, LR_SHARED);
	m_bOwner = false;

	ASSERT(m_hIcon != NULL);
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads the icon from the resource file.
**
** Parameters:	pszRsc	The resource name.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIcon::LoadRsc(const tchar* pszRsc)
{
	ASSERT(m_hIcon == NULL);

	m_hIcon  = ::LoadIcon(NULL, pszRsc);
	m_bOwner = false;

	ASSERT(m_hIcon != NULL);
}
