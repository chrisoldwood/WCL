/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		IMAGELIST.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CImageList class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ImageList.hpp"
#include "Module.hpp"

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

CImageList::CImageList()
	: m_hImageList(NULL)
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

CImageList::~CImageList()
{
	// Delete image list, if owner.
	if ( (m_hImageList != NULL) && (m_bOwner) )
		ImageList_Destroy(m_hImageList);
}

/******************************************************************************
** Method:		LoadRsc()
**
** Description:	Loads the image list from the resource file.
**
** Parameters:	nRscID		The resource ID.
**				nImgWidth	The width of each image.
**				crMask		The colour that represents the mask.
**				bOwner		Flag to determine if this is the owner.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CImageList::LoadRsc(uint nRscID, int nImgWidth, COLORREF crMask, bool bOwner)
{
	ASSERT(m_hImageList == NULL);

	m_hImageList = ImageList_LoadBitmap(CModule::This().Handle(), MAKEINTRESOURCE(nRscID), nImgWidth, 0, crMask);
	m_bOwner     = bOwner;

	ASSERT(m_hImageList != NULL);
}
