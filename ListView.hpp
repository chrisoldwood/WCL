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
	void CheckBoxes(bool bOn);
	void FullRowSelect(bool bOn);
	void GridLines(bool bOn);

	//
	// Item methods.
	//
	void Reserve(int nItems);
	int  AddItem(const char* pszText);
	int  AddItem(const char* pszText, LPARAM      lData, int nImage = -1);
	int  AddItem(const char* pszText, const void* pData, int nImage = -1);
	void DeleteItem(int nItem);
	void DeleteAllItems();

	void ItemText(int nItem, int nSubItem, const char* pszText);
	void ItemState(int nItem, int nState, int nMask);

	LPARAM ItemData(int nItem);
	void*  ItemPtr(int nItem);

	void Select(int nItem);
	int  SelectionMark() const;

	int  ItemCount() const;

	//
	// Column methods.
	//
	int  NumColumns() const;
	void InsertColumn(int iPos, const char* pszName, int iWidth, int iFormat = LVCFMT_LEFT);
	void InsertColumns(const LVColumn* pColumns, int nColumns);
	void DeleteColumn(int iPos);
	void DeleteAllColumns();

	//
	// Misc methods.
	//
	void ImageList(uint iRscID, int nImgWidth, COLORREF crMask);
	void IconSpacing(int iHorzSpacing, int iVertSpacing);
	int  StringWidth(const char* pszString);
	int  StringWidth(int nChars);

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

inline int CListView::AddItem(const char* pszText)
{
	return AddItem(pszText, (const void*)NULL, -1);
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

inline void CListView::Select(int nItem)
{
	ItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
}

inline int CListView::SelectionMark() const
{
	return ListView_GetSelectionMark(m_hWnd);
}

inline int CListView::ItemCount() const
{
	return ListView_GetItemCount(m_hWnd);
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

inline void CListView::IconSpacing(int iHorzSpacing, int iVertSpacing)
{
	ListView_SetIconSpacing(m_hWnd, iHorzSpacing, iVertSpacing);
}

inline int CListView::StringWidth(const char* pszString)
{
	return ListView_GetStringWidth(m_hWnd, pszString);
}

#endif //LISTVIEW_HPP
