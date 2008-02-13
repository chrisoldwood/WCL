/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NETFINDER.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CNetFinder class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef NETFINDER_HPP
#define NETFINDER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** Class used to enumerate network resources.
**
*******************************************************************************
*/

class CNetFinder
{
public:
	//
	// Methods.
	//
	static size_t FindDomains  (CStrArray& astrDomains);
	static size_t FindComputers(CStrArray& astrComputers);
	static size_t FindComputers(const tchar* pszDomain, CStrArray& astrComputers);
	
protected:
	//
	// Members.
	//

	//
	// Internal methods.
	//
	static DWORD FindDomains  (NETRESOURCE* pNetRsc, CStrArray& astrDomains);
	static DWORD FindComputers(NETRESOURCE* pNetRsc, CStrArray& astrComputers);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // NETFINDER_HPP
