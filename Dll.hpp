/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DLL.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDll class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_DLL_HPP
#define WCL_DLL_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Module.hpp"
#include "DllMain.hpp"

/******************************************************************************
** 
** This is base class from which the dll component class is derived.
**
*******************************************************************************
*/

class CDll
{
public:
	//
	// Constructors/Destructor.
	//
	CDll();
	virtual ~CDll();
	
	//! Check if the dll singleton is valid.
	static bool IsValid();
	
	//! Global access to the dll singleton.
	static CDll& This();

	//
	// Members.
	//
	CModule		m_Module;			//! The component.

protected:
	//
	// Members.
	//

	//
	// DllMain template methods.
	// (Overriden in the derived class).
	//
	virtual	void OnLoad();
	virtual	void OnUnload();
	virtual	void OnThreadAttached();
	virtual	void OnThreadDetached();	

private:
	//
	// Startup and shutdown methods.
	// (Called from DllMain).
	//
	void Load();
	void Unload();
	void ThreadAttached();
	void ThreadDetached();	

	friend BOOL WCL::dllMain(HINSTANCE hInst, DWORD dwReason);

	//
	// Class members.
	//

	//! The singleton DLL component object.
	static CDll* g_pThis;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // WCL_DLL_HPP
