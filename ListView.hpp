/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LISTVIEW.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CListView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef LISTVIEW_HPP
#define LISTVIEW_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"
#include "ImageList.hpp"
#include <vector>
#include <commctrl.h>

/******************************************************************************
**
** Structure used to define an array of ListView columns.
**
*******************************************************************************
*/

struct LVColumn
{
	const tchar*	pszName;	// The name.
	uint			nWidth;		// The width in pixels.
	uint			nFormat;	// The alignment of the text (LVCFMT_*).
};

/******************************************************************************
**
** This is a ListView control.
**
*******************************************************************************
*/

class CListView : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CListView();

	//
	// Attributes.
	//
	void CheckBoxes(bool bOn = true);
	void FullRowSelect(bool bOn = true);
	void GridLines(bool bOn = true);

	// Template shorthands.
	typedef std::vector<size_t> Items;

	//
	// Item methods.
	//
	void Reserve(size_t nItems);
	size_t AppendItem(const tchar* pszText, size_t nImage = Core::npos);
	size_t AppendItem(const tstring& text, size_t image = Core::npos);
	size_t InsertItem(size_t nItem, const tchar* pszText, size_t nImage = -1);
	size_t InsertItem(size_t item, const tstring& text, size_t icon = -1);

	void DeleteItem(size_t item, bool selectNextItem = false);
	void DeleteAllItems();

	void ItemText(size_t nItem, size_t nSubItem, const tchar* pszText);
	void ItemText(size_t item, size_t subItem, const tstring& text);

	void ItemImage(size_t nItem, size_t nImage);
	void ItemState(size_t nItem, uint nState, uint nMask);
	void ItemData(size_t nItem, LPARAM lParam);
	void ItemPtr(size_t nItem, const void* pData);
	void SetChecked(size_t nItem, bool bChecked = true);

	CString ItemText(size_t nItem, size_t nSubItem) const;
	size_t  ItemImage(size_t nItem) const;
	uint    ItemState(size_t nItem, uint nMask = LVIS_SELECTED) const;
	LPARAM  ItemData(size_t nItem) const;
	void*   ItemPtr(size_t nItem) const;
	bool    IsChecked(size_t nItem);

	void Select(size_t nItem, bool bSelect = true);
	void SelectFirstItem();
	bool IsSelection() const;
	size_t Selection() const;
	size_t Selections(Items& vItems) const;
	bool IsSelected(size_t nItem) const;
	void RestoreSel(size_t nItem);

	size_t ItemCount() const;

	void MakeItemVisible(size_t nItem);

	//
	// Column methods.
	//
	size_t NumColumns() const;
	void InsertColumn(size_t nColumn, const tchar* pszName, size_t nWidth, uint nFormat = LVCFMT_LEFT);
	void InsertColumn(size_t column, const tstring& name, size_t width, uint format = LVCFMT_LEFT);
	void InsertColumns(const LVColumn* pColumns, size_t nColumns);
	void DeleteColumn(size_t nColumn);
	void DeleteAllColumns();
	size_t ColumnWidth(size_t nColumn) const;
	void ColumnWidth(size_t nColumn, uint nWidth);
	void ColumnWidthAuto(size_t nColumn, bool bFitHeader = false);
	tstring ColumnName(size_t nColumn);

	//
	// Search methods.
	//
	size_t FindItem(const tchar* pszText, bool bPartial = false, size_t nStart = -1) const;
	size_t FindItem(LPARAM lData, size_t nStart = -1) const;
	size_t FindItem(const void* pData, size_t nStart = -1) const;
	size_t FindAllItems(const void* pData, Items& vItems) const;

	//
	// Misc methods.
	//
	void ImageList(uint nType, const CImageList& oImageList);
	void ImageList(uint nType, uint nRscID, uint nImgWidth, COLORREF crMask);
	void IconSpacing(uint iHorzSpacing, uint iVertSpacing);
	size_t StringWidth(const tchar* pszString) const;
	size_t StringWidth(size_t nChars) const;
	int  Sort(PFNLVCOMPARE pfnCompare, LPARAM lParamSort);

	//! Calculate the mouse co-ordinates for the message, relative to the window.
	CPoint calcMsgMousePos(const NMITEMACTIVATE& message) const;

protected:
	//
	// Members.
	//

	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CListView::CheckBoxes(bool bOn)
{
	DWORD dwMask  = LVS_EX_CHECKBOXES;
	DWORD dwStyle = (bOn) ? dwMask : 0;

	(void)ListView_SetExtendedListViewStyleEx(m_hWnd, dwMask, dwStyle);
}

inline void CListView::FullRowSelect(bool bOn)
{
	DWORD dwMask  = LVS_EX_FULLROWSELECT;
	DWORD dwStyle = (bOn) ? dwMask : 0;

	(void)ListView_SetExtendedListViewStyleEx(m_hWnd, dwMask, dwStyle);
}

inline void CListView::GridLines(bool bOn)
{
	DWORD dwMask  = LVS_EX_GRIDLINES;
	DWORD dwStyle = (bOn) ? dwMask : 0;

	(void)ListView_SetExtendedListViewStyleEx(m_hWnd, dwMask, dwStyle);
}

inline void CListView::Reserve(size_t nItems)
{
	ListView_SetItemCount(m_hWnd, nItems);
}

inline size_t CListView::AppendItem(const tchar* pszText, size_t nImage)
{
	return InsertItem(ItemCount(), pszText, nImage);
}

inline size_t CListView::AppendItem(const tstring& text, size_t image)
{
	return InsertItem(ItemCount(), text.c_str(), image);
}

////////////////////////////////////////////////////////////////////////////////
//! Insert a new item into the control.

inline size_t CListView::InsertItem(size_t item, const tstring& text, size_t icon)
{
	return InsertItem(item, text.c_str(), icon);
}

inline void CListView::DeleteAllItems()
{
	(void)ListView_DeleteAllItems(m_hWnd);
}

inline void CListView::ItemText(size_t nItem, size_t nSubItem, const tchar* pszText)
{
	ListView_SetItemText(m_hWnd, static_cast<int>(nItem), static_cast<int>(nSubItem), const_cast<tchar*>(pszText));
}

////////////////////////////////////////////////////////////////////////////////
//! Set the text value for a sub item.

inline void CListView::ItemText(size_t item, size_t subItem, const tstring& text)
{
	ListView_SetItemText(m_hWnd, static_cast<int>(item), static_cast<int>(subItem), const_cast<tchar*>(text.c_str()));
}

inline void CListView::ItemState(size_t nItem, uint nState, uint nMask)
{
	ListView_SetItemState(m_hWnd, nItem, nState, nMask);
}

inline void CListView::ItemPtr(size_t nItem, const void* pData)
{
	ItemData(nItem, reinterpret_cast<LPARAM>(pData));
}

inline void CListView::SetChecked(size_t nItem, bool bChecked)
{
	ListView_SetCheckState(m_hWnd, nItem, bChecked);
}

inline uint CListView::ItemState(size_t nItem, uint nMask) const
{
	return ListView_GetItemState(m_hWnd, nItem, nMask);
}

inline void* CListView::ItemPtr(size_t nItem) const
{
	return reinterpret_cast<void*>(ItemData(nItem));
}

inline bool CListView::IsChecked(size_t nItem)
{
	return ListView_GetCheckState(m_hWnd, nItem);
}

inline void CListView::Select(size_t nItem, bool bSelect)
{
	uint nState = (bSelect) ? (LVIS_SELECTED | LVIS_FOCUSED) : 0;

	ItemState(nItem, nState, 0x000F);
}

inline void CListView::SelectFirstItem()
{
	if (ItemCount() != 0)
		Select(0);
}

inline bool CListView::IsSelection() const
{
	return (Selection() != Core::npos);
}

inline bool CListView::IsSelected(size_t nItem) const
{
	return (ItemState(nItem) & LVIS_SELECTED);
}

inline size_t CListView::Selection() const
{
	return ListView_GetNextItem(m_hWnd, -1, LVNI_SELECTED);
}

inline size_t CListView::ItemCount() const
{
	return ListView_GetItemCount(m_hWnd);
}

inline void CListView::MakeItemVisible(size_t nItem)
{
	(void)ListView_EnsureVisible(m_hWnd, nItem, FALSE);
}

inline size_t CListView::NumColumns() const
{
	return Header_GetItemCount(ListView_GetHeader(m_hWnd));
}

inline void CListView::InsertColumn(size_t column, const tstring& name, size_t width, uint format)
{
	InsertColumn(column, name.c_str(), width, format);
}

inline void CListView::DeleteColumn(size_t nColumn)
{
	(void)ListView_DeleteColumn(m_hWnd, nColumn);
}

inline void CListView::DeleteAllColumns()
{
	size_t nColumns = NumColumns();

	while (nColumns-- > 0)
		(void)ListView_DeleteColumn(m_hWnd, 0);
}

inline size_t CListView::ColumnWidth(size_t nColumn) const
{
	return ListView_GetColumnWidth(m_hWnd, nColumn);
}

inline void CListView::ColumnWidth(size_t nColumn, uint nWidth)
{
	(void)ListView_SetColumnWidth(m_hWnd, nColumn, nWidth);
}

inline void CListView::ColumnWidthAuto(size_t nColumn, bool bFitHeader)
{
	(void)ListView_SetColumnWidth(m_hWnd, nColumn, (bFitHeader) ? LVSCW_AUTOSIZE_USEHEADER : LVSCW_AUTOSIZE);
}

inline void CListView::IconSpacing(uint iHorzSpacing, uint iVertSpacing)
{
	(void)ListView_SetIconSpacing(m_hWnd, iHorzSpacing, iVertSpacing);
}

inline size_t CListView::StringWidth(const tchar* pszString) const
{
	return ListView_GetStringWidth(m_hWnd, pszString);
}

inline int CListView::Sort(PFNLVCOMPARE pfnCompare, LPARAM lParamSort)
{
	return ListView_SortItems(m_hWnd, pfnCompare, lParamSort);
}

#endif //LISTVIEW_HPP
