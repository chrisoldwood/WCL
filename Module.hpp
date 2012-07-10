/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MODULE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CModule class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_MODULE_HPP
#define WCL_MODULE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Path.hpp"
#include "WinMain.hpp"
#include "DllMain.hpp"

/******************************************************************************
**
** This class holds the instance handle of an EXE or DLL module.
**
*******************************************************************************
*/

class CModule /*: private NotCopyable*/
{
public:
	//
	// Constructors/Destructor.
	//
	CModule();
	CModule(HINSTANCE hInstance);
	~CModule();

	//
	// Member access.
	//
	HINSTANCE Handle() const;

	// Global access to the object.
	static CModule& This();

	//
	// Methods.
	//

	//! Get the full path to the module.
	CPath Path() const;

protected:
	//
	// Members.
	//
	HINSTANCE	m_hInstance;

	friend int WCL::winMain(HINSTANCE hInstance, LPSTR lpszCmdLine, int nCmdShow);
	friend BOOL WCL::dllMain(HINSTANCE hInst, DWORD dwReason);

private:
	// NotCopyable.
	CModule(const CModule&);
	CModule& operator=(const CModule&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HINSTANCE CModule::Handle() const
{
	return m_hInstance;
}

#endif // WCL_MODULE_HPP
