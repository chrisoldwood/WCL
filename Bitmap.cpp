/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BITMAP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CBitmap class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Bitmap.hpp"
#include "Module.hpp"
#include "DC.hpp"

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

CBitmap::CBitmap()
	: m_hBitmap(NULL)
	, m_Size()
{
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	Construction from a resource.
**
** Parameters:	iRscID		The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CBitmap::CBitmap(uint iRscID)
	: m_hBitmap(NULL)
	, m_Size()
{
	LoadRsc(iRscID);
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

CBitmap::~CBitmap()
{
	if (m_hBitmap)
		::DeleteObject(m_hBitmap);
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads a bitmap from the resource file.
**
** Parameters:	iRscID		The resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBitmap::LoadRsc(uint iRscID)
{
	ASSERT(m_hBitmap == NULL);

	// Load the resource.
	m_hBitmap = ::LoadBitmap(CModule::This().Handle(), MAKEINTRESOURCE(iRscID));
	ASSERT(m_hBitmap);

	// Get attributes.
	BITMAP	bmBitmap;
	GetObject(m_hBitmap, sizeof(BITMAP), &bmBitmap);

	// Set members.
	m_Size.cx = bmBitmap.bmWidth;
	m_Size.cy = bmBitmap.bmHeight;
}

/******************************************************************************
** Method:		Create()
**
** Description:	Creates a mono bitmap of the specified dimensions.
**
** Parameters:	rSize			The bitmap size.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBitmap::Create(const CSize& rSize)
{
	m_hBitmap = CreateBitmap(rSize.cx, rSize.cy, 1, 1, NULL);
	m_Size    = rSize;

	ASSERT(m_hBitmap);
}

/******************************************************************************
** Method:		Create()
**
** Description:	Creates a bitmap compatible with the specifed device.
**
** Parameters:	rSize	The bitmap size.
**				rDC		The dc to be compatible with.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBitmap::Create(const CSize& rSize, const CDC& rDC)
{
	m_hBitmap = CreateCompatibleBitmap(rDC.Handle(), rSize.cx, rSize.cy);
	m_Size    = rSize;

	ASSERT(m_hBitmap);
}
