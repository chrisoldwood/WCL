////////////////////////////////////////////////////////////////////////////////
//! \file   ContextMenu.hpp
//! \brief  The ContextMenu class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_CONTEXTMENU_HPP
#define WCL_CONTEXTMENU_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "PopupMenu.hpp"

// Forward declarations.
class CFrameWnd;

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A menu used to invoke context dependent commands. This is usually used when
//! right-clicking on an object in a view.

class ContextMenu : public CPopupMenu
{
public:
	//! Construction from the menu resource ID.
	ContextMenu(uint resourceId);

	//! Destructor.
	virtual ~ContextMenu();
	
	//
	// Methods.
	//

	//! Display the context menu and invoke the selected command.
	void display(const CFrameWnd& appWnd) const;

	//
	// Class methods.
	//

	//! Display the context menu and invoke the selected command.
	static void display(uint resourceId, const CFrameWnd& appWnd);
};

//namespace WCL
}

#endif // WCL_CONTEXTMENU_HPP
