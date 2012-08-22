////////////////////////////////////////////////////////////////////////////////
//! \file   ContextMenu.cpp
//! \brief  The ContextMenu class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ContextMenu.hpp"
#include "App.hpp"
#include "Point.hpp"
#include "FrameWnd.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Construction from the menu resource ID.

ContextMenu::ContextMenu(uint resourceId)
	: CPopupMenu(resourceId)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ContextMenu::~ContextMenu()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Display the context menu and invoke the selected command.

void ContextMenu::display(const CFrameWnd& appWnd) const
{
	const CPoint position(CApp::This().m_MainThread.CurrentMsg().pt);

	const uint command = TrackMenu(appWnd, position);

	if (command != 0)
		appWnd.PostCommand(command);
}

////////////////////////////////////////////////////////////////////////////////
//! Display the context menu and invoke the selected command.

void ContextMenu::display(uint resourceId, const CFrameWnd& appWnd)
{
	const ContextMenu menu(resourceId);

	menu.display(appWnd);
}

//namespace WCL
}
