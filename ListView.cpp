/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LISTVIEW.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CListView class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Default constructor.
**
** Description:	Does nothing.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CListView::CListView()
{
}

/******************************************************************************
** Method:		GetCreateParams()
**
** Description:	Template method to get the window creation data.
**
** Parameters:	rParams		The create structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListView::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = WC_LISTVIEW;
	rParams.dwExStyle   |= WS_EX_CLIENTEDGE;
	rParams.dwStyle     |= WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS;
}

/******************************************************************************
** Method:		InsertItem()
**
** Description:	Inserts an item into the listview at the position given.
**
** Parameters:	nPos		The position to insert at.
**				pszText		The items label.
**				nImage		The index of the image list image (-1 for none).
**
** Returns:		The index of the item or -1 on error.
**
*******************************************************************************
*/

int CListView::InsertItem(int nPos, const char* pszText, int nImage)
{
	LVITEM lvItem = { 0 };

	// Initialise item structure.
	lvItem.mask    = LVIF_TEXT | LVIF_PARAM;
	lvItem.iItem   = nPos;
	lvItem.pszText = (char*) pszText;
	lvItem.iImage  = nImage;
	lvItem.lParam  = NULL;

	// Image specified?
	if (nImage != -1)
		lvItem.mask |= LVIF_IMAGE;

	return ListView_InsertItem(m_hWnd, &lvItem);
}

/******************************************************************************
** Method:		ItemImage()
**
** Description:	Sets the icon for the item.
**
** Parameters:	nItem		The item index.
**				nImage		The image index.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListView::ItemImage(int nItem, int nImage)
{
	LVITEM lvItem = { 0 };

	// Initialise item structure.
	lvItem.mask   = LVIF_IMAGE;
	lvItem.iItem  = nItem;
	lvItem.iImage = nImage;

	ListView_SetItem(m_hWnd, &lvItem);
}

/******************************************************************************
** Method:		ItemData()
**
** Description:	Sets the custom data for the item.
**
** Parameters:	nItem		The item index.
**				lParam		The item data.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListView::ItemData(int nItem, LPARAM lParam)
{
	LVITEM lvItem = { 0 };

	// Initialise item structure.
	lvItem.mask   = LVIF_PARAM;
	lvItem.iItem  = nItem;
	lvItem.lParam = lParam;

	ListView_SetItem(m_hWnd, &lvItem);
}

/******************************************************************************
** Method:		ItemText()
**
** Description:	Gets the text for the item.
**				NB: Uses a fixed buffer because there is no LVM_GETITEMTEXTLEN.
**
** Parameters:	nItem		The item index.
**				nSubItem	The sub item index.
**
** Returns:		The item text.
**
*******************************************************************************
*/

CString CListView::ItemText(int nItem, int nSubItem) const
{
	LVITEM  lvItem      = { 0 };
	char	szText[256] = { 0 };

	// Initialise item structure.
	lvItem.mask       = LVIF_TEXT;
	lvItem.iItem      = nItem;
	lvItem.iSubItem   = nSubItem;
	lvItem.pszText    = szText;
	lvItem.cchTextMax = sizeof(szText);

	// Get the item text.
	SendMessage(LVM_GETITEMTEXT, nItem, (LPARAM)&lvItem);

	return szText;
}

/******************************************************************************
** Method:		ItemData()
**
** Description:	Gets the item data for an item.
**
** Parameters:	nItem	The item whose data it is to fetch.
**
** Returns:		The item data.
**
*******************************************************************************
*/

LPARAM CListView::ItemData(int nItem) const
{
	LVITEM lvItem = { 0 };

	// Initialise item structure.
	lvItem.mask  = LVIF_PARAM;
	lvItem.iItem = nItem;

	ListView_GetItem(m_hWnd, &lvItem);

	return lvItem.lParam;
}

/******************************************************************************
** Method:		InsertColumn()
**
** Description:	Inserts a column into a listview in report mode.
**
** Parameters:	iPos		The zero-based position of the column.
**				pszName		The columns name.
**				iWidth		The width of the column in pixels.
**				iFormat		The text alignment of the items.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListView::InsertColumn(int iPos, const char* pszName, int iWidth, int iFormat)
{
	LVCOLUMN lvColumn = { 0 };

    lvColumn.mask     = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
    lvColumn.fmt      = iFormat;
    lvColumn.cx       = iWidth;
    lvColumn.pszText  = (char*) pszName;
    lvColumn.iSubItem = iPos;

	ListView_InsertColumn(m_hWnd, iPos, &lvColumn);
}

/******************************************************************************
** Method:		InsertColumns()
**
** Description:	Inserts a number of columns into a listview in report mode.
**
** Parameters:	pColumns	The array of column definitions.
**				nColumns	The number of columns to insert.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListView::InsertColumns(const LVColumn* pColumns, int nColumns)
{
	for (int i = 0; i < nColumns; i++)
		InsertColumn(i, pColumns[i].pszName, pColumns[i].nWidth, pColumns[i].nFormat);
}

/******************************************************************************
** Method:		ImageList()
**
** Description:	Sets the image list for the control from an ImageList object.
**
** Parameters:	nType		The type of image list (small/normal/state).
**				oImageList	The image list.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListView::ImageList(uint nType, const CImageList& oImageList)
{
	ASSERT(oImageList.Handle() != NULL);
	ASSERT(oImageList.Owner()  == false);

	ListView_SetImageList(m_hWnd, oImageList.Handle(), nType);
}

/******************************************************************************
** Method:		ImageList()
**
** Description:	Sets the image list for the control from a bitmap in the
**				resource file.
**
** Parameters:	nType		The type of image list (small/normal/state).
**				nRscID		The ID of the bitmap resource.
**				nImgWidth	The width of each image.
**				crMask		The colour used for the mask.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListView::ImageList(uint nType, uint nRscID, int nImgWidth, COLORREF crMask)
{
	CImageList oImageList;

	// Load the image list.
	oImageList.LoadRsc(nRscID, nImgWidth, crMask);

	ImageList(nType, oImageList);
}

/******************************************************************************
** Method:		StringWidth()
**
** Description:	Get the width of a string in pixels.
**
** Parameters:	nChars		The string length in characters.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

int CListView::StringWidth(int nChars) const
{
	// Create a string of 'X's.
	char* pszString = new char[nChars+1];

	memset(pszString, 'X', nChars);
	pszString[nChars] = '\0';

	int iWidth = StringWidth(pszString);

	delete[] pszString;

	return iWidth;
}

/******************************************************************************
** Methods:		FindItem()
**
** Description:	Finds an item either by text value or by lParam member.
**
** Parameters:	pszText		Text item to find.
**				lData		LPARAM data to find.
**				pData		LPARAM data to find.
**				bPartial	Extact or partial find?
**				nStart		The item to start from.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

int CListView::FindItem(const char* pszText, bool bPartial, int nStart) const
{
	ASSERT(pszText != NULL);

	LVFINDINFO oInfo = { 0 };

	oInfo.flags  = LVFI_STRING;
	oInfo.flags |= (bPartial) ? LVFI_PARTIAL : 0;
	oInfo.psz    = pszText;

	return ListView_FindItem(m_hWnd, nStart, &oInfo);
}

int CListView::FindItem(LPARAM lData, int nStart) const
{
	LVFINDINFO oInfo = { 0 };

	oInfo.flags  = LVFI_PARAM;
	oInfo.lParam = lData;

	return ListView_FindItem(m_hWnd, nStart, &oInfo);
}

int CListView::FindItem(const void* pData, int nStart) const
{
	LVFINDINFO oInfo = { 0 };

	oInfo.flags  = LVFI_PARAM;
	oInfo.lParam = (LPARAM)pData;

	return ListView_FindItem(m_hWnd, nStart, &oInfo);
}

/******************************************************************************
** Methods:		FindAllItems()
**
** Description:	Finds all items by lParam member.
**
** Parameters:	pszText		Text item to find.
**				lData		LPARAM data to find.
**				pData		LPARAM data to find.
**				bPartial	Extact or partial find?
**				vItems		The array of items found.
**
** Returns:		The number of items found.
**
*******************************************************************************
*/

uint CListView::FindAllItems(const void* pData, CUIntArray& vItems) const
{
	int n = -1;

	while ((n = FindItem(pData, n)) != LB_ERR)
		vItems.Add(n);

	return vItems.Size();
}

/******************************************************************************
** Methods:		RestoreSel()
**
** Description:	Restores the selection provided. If there was no selection,
**				then it selects the first item. If the item no longer exists,
**				it sets it to the last item.
**
** Parameters:	iItem	The item to select, or LB_ERR, if there was none.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListView::RestoreSel(int nItem)
{
	int nCount = ItemCount();

	// Handle no selection, or invalid selection.
	nItem = (nItem == LB_ERR) ? 0 : nItem;
	nItem = (nItem >= nCount) ? (nCount-1) : nItem;

	Select(nItem);
}
