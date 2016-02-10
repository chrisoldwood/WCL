/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		COMCTL32.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CComCtl32 class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef COMCTL32_HPP
#define COMCTL32_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Library.hpp"

/******************************************************************************
**
** Helper class used to interrogate and initialise COMCTL32.DLL.
**
*******************************************************************************
*/

class CComCtl32
{
public:
	//
	// Constructors/Destructor.
	//
	CComCtl32();
	~CComCtl32();

	//
	// Methods.
	//
	bool IsLoaded() const;
	bool GetVersion(DWORD& dwMajor, DWORD& dwMinor);
	bool Initialise(DWORD dwICC);

protected:
	//
	// Members.
	//
	CLibrary m_oDLL;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline bool CComCtl32::IsLoaded() const
{
	return m_oDLL.IsLoaded();
}

#endif // COMCTL32_HPP
