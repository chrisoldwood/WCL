////////////////////////////////////////////////////////////////////////////////
//! \file   TreeView.cpp
//! \brief  The TreeView class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "TreeView.hpp"
#include <commctrl.h>

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) // GCC 4.2+
// missing initializer for member 'X'
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

TreeView::TreeView()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

TreeView::~TreeView()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get the default window creation settings.

void TreeView::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = WC_TREEVIEW;
	rParams.dwExStyle   |= WS_EX_CLIENTEDGE;
	rParams.dwStyle     |= WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
}

////////////////////////////////////////////////////////////////////////////////
//! Set an image list for the tree view.

void TreeView::SetImageList(uint nType, const CImageList& oImageList)
{
	ASSERT(m_hWnd != NULL);
	ASSERT(oImageList.Handle() != NULL);
	ASSERT(oImageList.Owner()  == false);

//	TreeView_SetImageList(m_hWnd, oImageList.Handle(), nType);
    SendMessage(TVM_SETIMAGELIST, nType, reinterpret_cast<LPARAM>(oImageList.Handle()));
}

////////////////////////////////////////////////////////////////////////////////
//! Set an image list for the tree view.

void TreeView::SetImageList(uint nType, uint nRscID, uint nImgWidth, COLORREF crMask)
{
	CImageList oImageList;

	// Load the image list.
	oImageList.LoadRsc(nRscID, nImgWidth, crMask);

	SetImageList(nType, oImageList);
}

////////////////////////////////////////////////////////////////////////////////
//! Insert a tree item.

HTREEITEM TreeView::InsertItem(HTREEITEM hParent, HTREEITEM hPredecessor, const tstring& strText,
								bool bHasChildren, int nImage)
{
	ASSERT(m_hWnd != NULL);

	TVINSERTSTRUCT oItem = { 0 };

	oItem.hParent        = hParent;
	oItem.hInsertAfter   = hPredecessor;
	oItem.item.mask      = TVIF_TEXT | TVIF_CHILDREN;
	oItem.item.pszText   = const_cast<tchar*>(strText.c_str());
	oItem.item.cChildren = bHasChildren ? 1 : 0;

	if (nImage != -1)
	{
		oItem.item.mask          |= TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		oItem.item.iImage         = nImage;
		oItem.item.iSelectedImage = nImage;
	}

	return TreeView_InsertItem(m_hWnd, &oItem);
}

////////////////////////////////////////////////////////////////////////////////
//! Update a tree item.

void TreeView::UpdateItem(HTREEITEM hItem, const tstring& strText, bool bHasChildren, int nImage)
{
	ASSERT(m_hWnd != NULL);
	ASSERT(hItem != NULL);

	TVITEM oItem = { 0 };

	oItem.mask           = TVIF_TEXT | TVIF_CHILDREN | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	oItem.hItem          = hItem;
	oItem.pszText        = const_cast<tchar*>(strText.c_str());
	oItem.cChildren      = bHasChildren ? 1 : 0;
	oItem.iImage         = nImage;
	oItem.iSelectedImage = nImage;

	(void)TreeView_SetItem(m_hWnd, &oItem);
}

////////////////////////////////////////////////////////////////////////////////
//! Select a tree item.

void TreeView::Select(HTREEITEM hItem)
{
	ASSERT(m_hWnd != NULL);
	ASSERT(hItem != NULL);

	(void)TreeView_SelectItem(m_hWnd, hItem);
}

//namespace WCL
}
