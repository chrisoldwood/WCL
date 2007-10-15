/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CMDBMP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CCmdBitmap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CMDBMP_HPP
#define CMDBMP_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Bitmap.hpp"

// Forward declarations.
class CRect;
class CDC;

/******************************************************************************
** 
** The class used to store the visual representation (enabled and disabled) of
** all commands. It is used by the toolbar buttons and menu to draw the command
** icons.
**
*******************************************************************************
*/

class CCmdBitmap
{
public:
	//
	// Constructors/Destructor.
	//
	CCmdBitmap();
	~CCmdBitmap();

	void LoadRsc(uint iRscID);

	//
	// Methods.
	//
	void DrawCmd(uint iIndex, CDC& rDC, const CRect& rDst, bool bEnabled) const;

protected:
	//
	// Members.
	//
	uint	m_iCmdSize;
	CBitmap	m_EnabledBmp;
	CBitmap	m_DisabledBmp;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //CMDBMP_HPP
