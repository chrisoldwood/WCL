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
	static int FindDomains  (CStrArray& astrDomains);
	static int FindComputers(CStrArray& astrComputers);
	static int FindComputers(const char* pszDomain, CStrArray& astrComputers);
	
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
