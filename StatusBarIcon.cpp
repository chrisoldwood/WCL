/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATUSBARICON.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CStatusBarIcon class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StatusBarIcon.hpp"
#include "TransparentBmp.hpp"
#include "DC.hpp"

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Size of icon.
const int ICON_SIZE = 16;

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

CStatusBarIcon::CStatusBarIcon()
	: m_pBitmap(NULL)
	, m_nIndex(0)
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

CStatusBarIcon::~CStatusBarIcon()
{
}

/******************************************************************************
** Method:		GetClassParams()
**
** Description:	Template method to get the window class data.
**
** Parameters:	rParams		The class structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBarIcon::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CStatusBarPanel::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
	rParams.lpszClassName = TXT("StatusBarIcon");
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

void CStatusBarIcon::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CStatusBarPanel::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = TXT("StatusBarIcon");
	rParams.rcPos.Set(0, 0, (2*BORDER_SIZE)+ICON_SIZE, (2*BORDER_SIZE)+ICON_SIZE);
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the panel border.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBarIcon::OnPaint(CDC& rDC)
{
	// Icon to paint?
	if (m_pBitmap != NULL)
	{
		int nSize = m_pBitmap->Size().cy;

		// Calculate source and destination rectangles.
		CRect rcSrc(nSize*m_nIndex, 0, (nSize*m_nIndex)+nSize, nSize);
		CRect rcDst(BORDER_SIZE, BORDER_SIZE, BORDER_SIZE+nSize, BORDER_SIZE+nSize);

		// Draw it.
		rDC.BitBlt(*m_pBitmap, rcSrc, rcDst);
	}

	// Draw border last.
	CStatusBarPanel::OnPaint(rDC);
}

/******************************************************************************
** Method:		ClearIcon()
**
** Description:	Remove the icon.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBarIcon::ClearIcon(bool bForcePaint)
{
	// Ignore, if already cleared.
	if (m_pBitmap == NULL)
		return;

	m_pBitmap = NULL;
	m_nIndex  = 0;

	Invalidate();

	if (bForcePaint)
		Update();
}

/******************************************************************************
** Method:		SetIcon()
**
** Description:	Set the icon bitmap and image index.
**				NB: The icons are assumed to be square (Height x Height).
**
** Parameters:	pBitmap		The bitmap.
**				nIndex		The image index.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatusBarIcon::SetIcon(const CTransparentBmp& oBitmap, uint nIndex, bool bForcePaint)
{
	ASSERT(nIndex >= 0);

	// Ignore, if same image.
	if ( (m_pBitmap == &oBitmap) && (m_nIndex == nIndex) )
		return;

	m_pBitmap = &oBitmap;
	m_nIndex  = nIndex;

	Invalidate();

	if (bForcePaint)
		Update();
}
