////////////////////////////////////////////////////////////////////////////////
//! \file   TreeView.hpp
//! \brief  The TreeView class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_TREEVIEW_HPP
#define WCL_TREEVIEW_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"
#include "ImageList.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The TreeView common control.

class TreeView : public CStdWnd
{
public:
	//! Default constructor.
	TreeView();

	//! Destructor.
	virtual	~TreeView();
	
	//
	// Properties.
	//

	//! Get the root item.
	HTREEITEM Root() const;

	//! Get the current selection.
	HTREEITEM Selection() const;

	//! Set an image list for the tree view.
	void SetImageList(uint nType, const CImageList& oImageList);

	//! Set an image list for the tree view.
	void SetImageList(uint nType, uint nRscID, uint nImgWidth, COLORREF crMask);

	//
	// Methods.
	//

	//! Delete all items from the tree.
	void Clear();

	//! Insert the tree root item.
	HTREEITEM InsertRootItem(const tstring& strText, bool bHasChildren = false, int nImage = -1);

	//! Insert a tree item.
	HTREEITEM InsertItem(HTREEITEM hParent, HTREEITEM hPredecessor, const tstring& strText, bool bHasChildren = false, int nImage = -1);

	//! Update a tree item.
	void UpdateItem(HTREEITEM hItem, const tstring& strText, bool bHasChildren, int nImage);

	//! Select a tree item.
	void Select(HTREEITEM hItem);

protected:
	//
	// Internal methods.
	//

	//! Get the default window creation settings.
	virtual void GetCreateParams(WNDCREATE& rParams);
};

////////////////////////////////////////////////////////////////////////////////
//! Get the root item.

inline HTREEITEM TreeView::Root() const
{
	ASSERT(m_hWnd != NULL);

	return TreeView_GetRoot(m_hWnd);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the current selection.

inline HTREEITEM TreeView::Selection() const
{
	ASSERT(m_hWnd != NULL);

	return TreeView_GetSelection(m_hWnd);
}

////////////////////////////////////////////////////////////////////////////////
//! Delete all items from the tree.

inline void TreeView::Clear()
{
	ASSERT(m_hWnd != NULL);

	TreeView_DeleteAllItems(m_hWnd);
}

////////////////////////////////////////////////////////////////////////////////
//! Insert the tree root item.

inline HTREEITEM TreeView::InsertRootItem(const tstring& strText, bool bHasChildren, int nImage)
{
	return InsertItem(TVI_ROOT, TVI_ROOT, strText, bHasChildren, nImage);
}

//namespace WCL
}

#endif // WCL_TREEVIEW_HPP
