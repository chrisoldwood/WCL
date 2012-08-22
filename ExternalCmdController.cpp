////////////////////////////////////////////////////////////////////////////////
//! \file   ExternalCmdController.cpp
//! \brief  The ExternalCmdController class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ExternalCmdController.hpp"
#include "ResourceString.hpp"
#include <Core/StringUtils.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

ExternalCmdController::ExternalCmdController()
	: m_commands()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a set of commands.

ExternalCmdController::ExternalCmdController(const std::vector<IUiCommandPtr>& commands)
{
	typedef std::vector<IUiCommandPtr>::const_iterator CommandIterator;

	for (CommandIterator it = commands.begin(); it != commands.end(); ++it)
	{
		const IUiCommandPtr& command = *it;

		m_commands[command->id()] = command;
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ExternalCmdController::~ExternalCmdController()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Register a new set of commands. This will add new command mappings and
//! replace any existing ones for the same ID.

void ExternalCmdController::registerCommands(const std::vector<IUiCommandPtr>& commands)
{
	typedef std::vector<IUiCommandPtr>::const_iterator CommandIterator;

	for (CommandIterator it = commands.begin(); it != commands.end(); ++it)
	{
		const IUiCommandPtr& command = *it;

		m_commands[command->id()] = command;
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Execute a command.

void ExternalCmdController::Execute(uint command)
{
	Commands::iterator it = m_commands.find(command);

	if (it != m_commands.end())
		it->second->execute();
}

////////////////////////////////////////////////////////////////////////////////
//! Refresh the entire UI.

void ExternalCmdController::UpdateUI()
{
	for (Commands::iterator it = m_commands.begin(); it != m_commands.end(); ++it)
		it->second->updateUi();
}

////////////////////////////////////////////////////////////////////////////////
//! Draw the icon for a command.

void ExternalCmdController::DrawCmd(uint command, CDC& dc, const CRect& rect, bool enabled) const
{
	Commands::const_iterator it = m_commands.find(command);

	if (it != m_commands.end())
		it->second->drawIcon(dc, rect, enabled);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the hint string for a command.

CString ExternalCmdController::CmdHintStr(uint command) const
{
	Commands::const_iterator it = m_commands.find(command);

	if (it != m_commands.end())
		return it->second->hint().c_str();
	else
		return defaultHint(command).c_str();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the tool tip for a command.

CString ExternalCmdController::CmdToolTipStr(uint command) const
{
	Commands::const_iterator it = m_commands.find(command);

	if (it != m_commands.end())
		return it->second->toolTip().c_str();
	else
		return defaultToolTip(command).c_str();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the default hint for the command. The default hint comes from a resource
//! string with same ID as the command. It consists of all text up to, but not
//! including the newline that separates the hint & tool tip.

tstring ExternalCmdController::defaultHint(uint command)
{
	const tstring text = loadString(command);
	const size_t  index = text.find_first_of(TXT('\n'));

	if (index == tstring::npos)
		return text;

	const size_t count = index;

	return Core::left(text, count);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the default tool tip for the command. The default tip comes from a
//! resource string with same ID as the command. It consists of all text after,
//! the newline that separates the hint & tool tip strings.

tstring ExternalCmdController::defaultToolTip(uint command)
{
	const tstring text = loadString(command);
	const size_t  index = text.find_first_of(TXT('\n'));

	if (index == tstring::npos)
		return TXT("");

	const size_t count = text.length() - index - 1;

	return Core::right(text, count);
}

//namespace WCL
}
