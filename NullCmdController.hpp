////////////////////////////////////////////////////////////////////////////////
//! \file   NullCmdController.hpp
//! \brief  The NullCmdController class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_NULLCMDCONTROLLER_HPP
#define WCL_NULLCMDCONTROLLER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "ICmdController.hpp"
#include <Core/NotImplException.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A Null Object implementation of a command controller. This can be used by
//! simple dialog based apps that do not need command support.

class NullCmdController : public ICmdController /*, private NotCopyable*/
{
public:
	//! Default constructor.
	NullCmdController();

	//! Destructor.
	virtual ~NullCmdController();

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

private:
	// NotCopyable.
	NullCmdController(const NullCmdController&);
	NullCmdController& operator=(const NullCmdController&);
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

inline NullCmdController::NullCmdController()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

inline NullCmdController::~NullCmdController()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Execute a command.

inline void NullCmdController::Execute(uint /*command*/)
{
	throw Core::NotImplException(TXT("NullCmdController does not implement Execute()"));
}

////////////////////////////////////////////////////////////////////////////////
//! Refresh the entire UI.

inline void NullCmdController::UpdateUI()
{
	throw Core::NotImplException(TXT("NullCmdController does not implement UpdateUI()"));
}

////////////////////////////////////////////////////////////////////////////////
//! Draw the icon for a command.

inline void NullCmdController::DrawCmd(uint /*command*/, CDC& /*dc*/, const CRect& /*rect*/, bool /*enabled*/) const
{
	throw Core::NotImplException(TXT("NullCmdController does not implement DrawCmd()"));
}

////////////////////////////////////////////////////////////////////////////////
//! Get the hint string for a command.

inline CString NullCmdController::CmdHintStr(uint /*command*/) const
{
	throw Core::NotImplException(TXT("NullCmdController does not implement CmdHintStr()"));

	//return TXT("");
}

////////////////////////////////////////////////////////////////////////////////
//! Get the tool tip for a command.

inline CString NullCmdController::CmdToolTipStr(uint /*command*/) const
{
	throw Core::NotImplException(TXT("NullCmdController does not implement CmdToolTipStr()"));

	//return TXT("");
}

//namespace WCL
}

#endif // WCL_NULLCMDCONTROLLER_HPP
