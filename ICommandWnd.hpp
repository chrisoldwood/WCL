////////////////////////////////////////////////////////////////////////////////
//! \file   ICommandWnd.hpp
//! \brief  The ICommandWnd interface declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_ICOMMANDWND_HPP
#define WCL_ICOMMANDWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A window that is used to invoke application commands. This is usually the
//! main application window.

class ICommandWnd
{
public:
	//! Handle updates to any command states.
	virtual void OnCommandsUpdated() = 0;
	
protected:
	//! Protected destructor.
	virtual ~ICommandWnd() = 0 {}; 
};

//namespace WCL
}

#endif // WCL_ICOMMANDWND_HPP
