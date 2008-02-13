/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDIFRAME.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CSDIFrame class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SDIFRAME_HPP
#define SDIFRAME_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "FrameWnd.hpp"

// Forward declarations.
class CView;

/******************************************************************************
** 
** This is the base class for an SDI applications' main window.
**
*******************************************************************************
*/

class CSDIFrame : public CFrameWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CSDIFrame(uint iIconID);
	virtual	~CSDIFrame();

	//
	// Methods.
	//
	void View(CView* pView);

	void UpdateTitle();

protected:
	//
	// Members.
	//
	CView*	m_pView;	// The only doc view.

	// Child window IDs.
	enum
	{
		IDC_VIEW = 100
	};

	//
	// Message processors (Overriden from the base class).
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual void OnResize(int iFlag, const CSize& rNewSize);
	virtual void OnDropFile(int nFile, const tchar* pszPath);
	virtual void OnDestroy();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //SDIFRAME_HPP
