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
	rParams.dwStyle     |= WS_BORDER | LVS_SINGLESEL;
}

/******************************************************************************
** Method:		AddItem()
**
** Description:	Adds a new item to the listview.
**
** Parameters:	pszText		The items label.
**				lData		Item data.
**				nImage		The index of the image list image.
**
** Returns:		The index of the item or -1 on error.
**
*******************************************************************************
*/

int CListView::AddItem(const char* pszText, LPARAM lData, int nImage)
{
	LVITEM lvItem;

	memset(&lvItem, 0, sizeof(lvItem));

	// Initialise item structure.
	lvItem.mask    = LVIF_TEXT | LVIF_PARAM;
	lvItem.iItem   = ListView_GetItemCount(m_hWnd);
	lvItem.pszText = (char*) pszText;
	lvItem.iImage  = nImage;
	lvItem.lParam  = lData;

	// Image specified?
	if (nImage != -1)
		lvItem.mask |= LVIF_IMAGE;

	return ListView_InsertItem(m_hWnd, &lvItem);
}

/******************************************************************************
** Method:		AddItem()
**
** Description:	Adds a new item to the listview.
**
** Parameters:	pszText		The items label.
**				pData		Item data.
**				nImage		The index of the image list image.
**
** Returns:		The index of the item or -1 on error.
**
*******************************************************************************
*/

int CListView::AddItem(const char* pszText, const void* pData, int nImage)
{
	return AddItem(pszText, (LPARAM)pData, nImage);
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

LPARAM CListView::ItemData(int nItem)
{
	LVITEM lvItem;

	memset(&lvItem, 0, sizeof(lvItem));

	// Initialise item structure.
	lvItem.mask    = LVIF_PARAM;
	lvItem.iItem   = nItem;

	ListView_GetItem(m_hWnd, &lvItem);

	return lvItem.lParam;
}

/******************************************************************************
** Method:		ItemPtr()
**
** Description:	Gets the item data for an item.
**
** Parameters:	nItem	The item whose data it is to fetch.
**
** Returns:		The item data.
**
*******************************************************************************
*/

void* CListView::ItemPtr(int nItem)
{
	return (void*) ItemData(nItem);
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
	LVCOLUMN lvColumn;

	memset(&lvColumn, 0, sizeof(lvColumn));

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
** Description:	Sets the image list for the control from a bitmap in the
**				resource file.
**
** Parameters:	iRscID		The ID of the bitmap resource.
**				nImgWidth	The width of each image.
**				crMask		The colour used for the mask.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CListView::ImageList(uint iRscID, int nImgWidth, COLORREF crMask)
{
	// Load the image list.
	HIMAGELIST hImgList = ImageList_LoadBitmap(CModule::This().Handle(), MAKEINTRESOURCE(iRscID), nImgWidth, 0, crMask);
	ASSERT(hImgList != NULL);

	ListView_SetImageList(m_hWnd, hImgList, LVSIL_NORMAL);
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

int CListView::StringWidth(int nChars)
{
	// Create a string of 'X's.
	char* pszString = new char[nChars+1];

	memset(pszString, 'X', nChars);
	pszString[nChars] = '\0';

	int iWidth = StringWidth(pszString);

	delete[] pszString;

	return iWidth;
}
