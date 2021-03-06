////////////////////////////////////////////////////////////////////////////////
//! \file   ICmdController.hpp
//! \brief  The ICmdController interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_ICMDCONTROLLER_HPP
#define WCL_ICMDCONTROLLER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

// Forward declarations.
class CDC;
class CRect;

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The controller used to execute commands and update the UI.

class ICmdController
{
public:
	//! Destructor.
	virtual ~ICmdController() {};

	//! Execute a command.
	virtual void Execute(uint command) = 0;

	//! Refresh the entire UI.
	virtual void UpdateUI() = 0;

	//! Draw the icon for a command.
	virtual void DrawCmd(uint command, CDC& dc, const CRect& rect, bool enabled) const = 0;

	//! Get the hint string for a command.
	virtual CString CmdHintStr(uint command) const = 0;

	//! Get the tool tip for a command.
	virtual CString CmdToolTipStr(uint command) const = 0;
};

//namespace WCL
}

#endif // WCL_ICMDCONTROLLER_HPP
