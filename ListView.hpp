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

/******************************************************************************
** 
** Structure used to define an array of ListView columns.
**
*******************************************************************************
*/

struct LVColumn
{
	const char*	pszName;	// The name.
	int			nWidth;		// The width in pixels.
	int			nFormat;	// The alignment of the text.
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

	//
	// Item methods.
	//
	void Reserve(int nItems);
	int  AppendItem(const char* pszText, int nImage = -1);
	int  InsertItem(int nPos, const char* pszText, int nImage = -1);
	void DeleteItem(int nItem);
	void DeleteAllItems();

	void ItemText(int nItem, int nSubItem, const char* pszText);
	void ItemImage(int nItem, int nImage);
	void ItemState(int nItem, int nState, int nMask);
	void ItemData(int nItem, LPARAM lParam);
	void ItemPtr(int nItem, const void* pData);

	CString ItemText(int nItem, int nSubItem) const;
	int     ItemState(int nItem, int nMask = LVIS_SELECTED) const;
	LPARAM  ItemData(int nItem) const;
	void*   ItemPtr(int nItem) const;

	void Select(int nItem, bool bSelect = true);
	bool IsSelection() const;
	int  Selection() const;
	bool IsSelected(int nItem) const;
	void RestoreSel(int nItem);

	int  ItemCount() const;

	void MakeItemVisible(int nItem);

	//
	// Column methods.
	//
	int  NumColumns() const;
	void InsertColumn(int iPos, const char* pszName, int iWidth, int iFormat = LVCFMT_LEFT);
	void InsertColumns(const LVColumn* pColumns, int nColumns);
	void DeleteColumn(int iPos);
	void DeleteAllColumns();
	int  ColumnWidth(int iPos) const;
	void ColumnWidth(int iPos, int nWidth);
	void ColumnWidthAuto(int iPos, bool bFitHeader = false);

	// Template shorthands.
	typedef TArray<uint> CUIntArray;

	//
	// Search methods.
	//
	int  FindItem(const char* pszText, bool bPartial = false, int nStart = -1) const;
	int  FindItem(LPARAM lData, int nStart = -1) const;
	int  FindItem(const void* pData, int nStart = -1) const;
	uint FindAllItems(const void* pData, CUIntArray& vItems) const;

	//
	// Misc methods.
	//
	void ImageList(uint nType, const CImageList& oImageList);
	void ImageList(uint nType, uint nRscID, int nImgWidth, COLORREF crMask);
	void IconSpacing(int iHorzSpacing, int iVertSpacing);
	int  StringWidth(const char* pszString) const;
	int  StringWidth(int nChars) const;
	int  Sort(PFNLVCOMPARE pfnCompare, LPARAM lParamSort);

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

	ListView_SetExtendedListViewStyleEx(m_hWnd, dwMask, dwStyle);
}

inline void CListView::FullRowSelect(bool bOn)
{
	DWORD dwMask  = LVS_EX_FULLROWSELECT;
	DWORD dwStyle = (bOn) ? dwMask : 0;

	ListView_SetExtendedListViewStyleEx(m_hWnd, dwMask, dwStyle);
}

inline void CListView::GridLines(bool bOn)
{
	DWORD dwMask  = LVS_EX_GRIDLINES;
	DWORD dwStyle = (bOn) ? dwMask : 0;

	ListView_SetExtendedListViewStyleEx(m_hWnd, dwMask, dwStyle);
}

inline void CListView::Reserve(int nItems)
{
	ListView_SetItemCount(m_hWnd, nItems);
}

inline int CListView::AppendItem(const char* pszText, int nImage)
{
	return InsertItem(ItemCount(), pszText, nImage);
}

inline void CListView::DeleteItem(int nItem)
{
	ListView_DeleteItem(m_hWnd, nItem);
}

inline void CListView::DeleteAllItems()
{
	ListView_DeleteAllItems(m_hWnd);
}

inline void CListView::ItemText(int nItem, int nSubItem, const char* pszText)
{
	ListView_SetItemText(m_hWnd, nItem, nSubItem, (char*)pszText);
}

inline void CListView::ItemState(int nItem, int nState, int nMask)
{
	ListView_SetItemState(m_hWnd, nItem, nState, nMask);
}

inline void CListView::ItemPtr(int nItem, const void* pData)
{
	ItemData(nItem, (LPARAM)pData);
}

inline int CListView::ItemState(int nItem, int nMask) const
{
	return ListView_GetItemState(m_hWnd, nItem, nMask);
}

inline void* CListView::ItemPtr(int nItem) const
{
	return (void*) ItemData(nItem);
}

inline void CListView::Select(int nItem, bool bSelect)
{
	int nState = (bSelect) ? (LVIS_SELECTED | LVIS_FOCUSED) : 0;

	ItemState(nItem, nState, 0x000F);
}

inline bool CListView::IsSelection() const
{
	return (Selection() != LB_ERR);
}

inline bool CListView::IsSelected(int nItem) const
{
	return (ItemState(nItem) & LVIS_SELECTED);
}

inline int CListView::Selection() const
{
	return ListView_GetNextItem(m_hWnd, -1, LVNI_SELECTED);
}

inline int CListView::ItemCount() const
{
	return ListView_GetItemCount(m_hWnd);
}

inline void CListView::MakeItemVisible(int nItem)
{
	ListView_EnsureVisible(m_hWnd, nItem, FALSE);
}

inline int CListView::NumColumns() const
{
	return Header_GetItemCount(ListView_GetHeader(m_hWnd));
}

inline void CListView::DeleteColumn(int iPos)
{
	ListView_DeleteColumn(m_hWnd, iPos);
}

inline void CListView::DeleteAllColumns()
{
	int nColumns = NumColumns();

	while (nColumns-- >= 0)
		ListView_DeleteColumn(m_hWnd, 0);
}

inline int CListView::ColumnWidth(int iPos) const
{
	return ListView_GetColumnWidth(m_hWnd, iPos);
}

inline void CListView::ColumnWidth(int iPos, int nWidth)
{
	ListView_SetColumnWidth(m_hWnd, iPos, nWidth);
}

inline void CListView::ColumnWidthAuto(int iPos, bool bFitHeader)
{
	ListView_SetColumnWidth(m_hWnd, iPos, (bFitHeader) ? LVSCW_AUTOSIZE_USEHEADER : LVSCW_AUTOSIZE);
}

inline void CListView::IconSpacing(int iHorzSpacing, int iVertSpacing)
{
	ListView_SetIconSpacing(m_hWnd, iHorzSpacing, iVertSpacing);
}

inline int CListView::StringWidth(const char* pszString) const
{
	return ListView_GetStringWidth(m_hWnd, pszString);
}

inline int CListView::Sort(PFNLVCOMPARE pfnCompare, LPARAM lParamSort)
{
	return ListView_SortItems(m_hWnd, pfnCompare, lParamSort);
}

#endif //LISTVIEW_HPP
