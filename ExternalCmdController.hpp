////////////////////////////////////////////////////////////////////////////////
//! \file   ExternalCmdController.hpp
//! \brief  The ExternalCmdController class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_EXTERNALCMDCONTROLLER_HPP
#define WCL_EXTERNALCMDCONTROLLER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "ICmdController.hpp"
#include "IUiCommand.hpp"
#include <map>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A command controller that dispatches to commands that are implemented as
//! separate command objects.

class ExternalCmdController : public ICmdController /*, private NotCopyable*/
{
public:
	//! Default constructor.
	ExternalCmdController();

	//! Construction from a set of commands.
	ExternalCmdController(const std::vector<IUiCommandPtr>& commands);

	//! Destructor.
	virtual ~ExternalCmdController();
	
	//
	// Methods.
	//

	//! Register a new set of commands.
	void registerCommands(const std::vector<IUiCommandPtr>& commands);

	//
	// ICmdController methods.
	//

	//! Execute a command.
	virtual void Execute(uint command);

	//! Refresh the entire UI.
	virtual void UpdateUI();

	//! Draw the icon for a command.
	virtual void DrawCmd(uint command, CDC& dc, const CRect& rect, bool enabled) const;

	//! Get the hint string for a command.
	virtual CString CmdHintStr(uint command) const;

	//! Get the tool tip for a command.
	virtual CString CmdToolTipStr(uint command) const;

	//
	// Class methods.
	//

	//! Get the default hint for the command.
	static tstring defaultHint(uint command);

	//! Get the tool tip for the command.
	static tstring defaultToolTip(uint command);

private:
	//! A map of command ID to command.
	typedef std::map<uint, IUiCommandPtr> Commands;

	//
	// Members.
	//
	Commands	m_commands;		//!< The map of command ID to command object.

private:
	// NotCopyable.
	ExternalCmdController(const ExternalCmdController&);
	ExternalCmdController& operator=(const ExternalCmdController&);
};

//! Begin the definition of a command table.
#define WCL_DEFINE_EXTCMD_TABLE		std::vector<WCL::IUiCommandPtr> commands;

//! Create an entry in the command table.
#define WCL_EXTCMD_ENTRY(cmd)		commands.push_back(WCL::IUiCommandPtr((cmd)));

//! Complete the definition of a command table.
#define WCL_END_EXTCMD_TABLE		registerCommands(commands);

//namespace WCL
}

#endif // WCL_EXTERNALCMDCONTROLLER_HPP
