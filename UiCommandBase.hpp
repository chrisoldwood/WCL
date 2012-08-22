////////////////////////////////////////////////////////////////////////////////
//! \file   UiCommandBase.hpp
//! \brief  The UiCommandBase class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_UICOMMANDBASE_HPP
#define WCL_UICOMMANDBASE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "IUiCommand.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The default implementation for the IUiCommand interface.

class UiCommandBase : public IUiCommand
{
public:
	//! Construction from the ID.
	UiCommandBase(uint id);

	//
	// IUiCommand properties.
	//

	//! Get the unique ID of the command.
	virtual uint id() const;

	//! Get the hint for the command.
	virtual tstring hint() const;

	//! Get the tool tip for the command.
	virtual tstring toolTip() const;

	//
	// IUiCommand methods.
	//

	//! Execute the command.
	virtual void execute();

	//! Refresh the UI for the command.
	virtual void updateUi();
	
	//! Draw the icon for a command.
	virtual void drawIcon(CDC& dc, const CRect& rect, bool enabled) const;

public:
	//! Make abstract.
	virtual ~UiCommandBase() = 0 {};

private:
	//
	// Members.
	//
	uint	m_id;	//!< The command ID.
};

//namespace WCL
}

#endif // WCL_UICOMMANDBASE_HPP
