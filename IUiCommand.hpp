////////////////////////////////////////////////////////////////////////////////
//! \file   IUiCommand.hpp
//! \brief  The IUiCommand interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_IUICOMMAND_HPP
#define WCL_IUICOMMAND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/SharedPtr.hpp>

// Forward declarations.
class CDC;
class CRect;

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A user interface command. These commands are usually exposed as menu items
//! and toolbar buttons and dispatched by implementations of ICmdController.

class IUiCommand
{
public:
	//
	// Properties.
	//

	//! Get the unique ID of the command.
	virtual uint id() const = 0;

	//! Get the hint for the command.
	virtual tstring hint() const = 0;

	//! Get the tool tip for the command.
	virtual tstring toolTip() const = 0;

	//
	// Methods.
	//

	//! Execute the command.
	virtual void execute() = 0;

	//! Refresh the UI for the command.
	virtual void updateUi() = 0;

	//! Draw the icon for a command.
	virtual void drawIcon(CDC& dc, const CRect& rect, bool enabled) const = 0;

public:
	//! Make abstract.
	virtual ~IUiCommand() /*= 0*/ {};
};

//! The default smart-pointer type.
typedef Core::SharedPtr<IUiCommand> IUiCommandPtr;

//namespace WCL
}

#endif // WCL_IUICOMMAND_HPP
