/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NETFINDER.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CNetFinder class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "NetFinder.hpp"
#include "StrArray.hpp"
#include <malloc.h>

// Add .lib to linker.
#pragma comment(lib, "mpr")

/******************************************************************************
** Method:		FindDomains()
**
** Description:	Finds all domains on the network.
**
** Parameters:	astrDomains	The return buffer for the domain names.
**
** Returns:		The number of domains found.
**
*******************************************************************************
*/

size_t CNetFinder::FindDomains(CStrArray& astrDomains)
{
	FindDomains(NULL, astrDomains);

	return astrDomains.Size();
}

/******************************************************************************
** Method:		FindDomains()
**
** Description:	Internal method to do the work of finding all domains.
**
** Parameters:	pNetRsc			The network container to enumerate.
**				astrDomains		The return buffer for the domain names.
**
** Returns:		The result of the last call.
**
*******************************************************************************
*/

DWORD CNetFinder::FindDomains(NETRESOURCE* pNetRsc, CStrArray& astrDomains)
{
	DWORD  dwResult = NO_ERROR;
	HANDLE hEnum    = NULL;

	// Start the enumeration.
	if ((dwResult = ::WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, pNetRsc, &hEnum)) == NO_ERROR)
	{
		DWORD        dwBufSize  = 16384;
		NETRESOURCE* pTmpNetRsc = static_cast<NETRESOURCE*>(alloca(dwBufSize));

		// For all resources...
		while ((dwResult == NO_ERROR) || (dwResult == ERROR_MORE_DATA))
		{
			DWORD dwCount = 1;

			if ((dwResult = ::WNetEnumResource(hEnum, &dwCount, pTmpNetRsc, &dwBufSize)) == NO_ERROR)
			{
				// If a domain add it to the list.
				if (pTmpNetRsc->dwDisplayType == RESOURCEDISPLAYTYPE_DOMAIN)
				{
					astrDomains.Add(pTmpNetRsc->lpRemoteName);
				}
				// If a container, enumerate it.
				else if (pTmpNetRsc->dwUsage & RESOURCEUSAGE_CONTAINER)
				{
					FindDomains(pTmpNetRsc, astrDomains);
				}
			}
		}

		// Enumeration succesful.
		if (dwResult == ERROR_NO_MORE_ITEMS)
			dwResult = NO_ERROR;

		::WNetCloseEnum(hEnum);
	}

	return dwResult;
}

/******************************************************************************
** Method:		FindComputers()
**
** Description:	Finds all computers on the network.
**
** Parameters:	astrComputers	The return buffer for the computer names.
**
** Returns:		The number of computers found.
**
*******************************************************************************
*/

size_t CNetFinder::FindComputers(CStrArray& astrComputers)
{
	FindComputers(static_cast<NETRESOURCE*>(nullptr), astrComputers);

	return astrComputers.Size();
}

/******************************************************************************
** Method:		FindComputers()
**
** Description:	Finds all computers in the given domain.
**
** Parameters:	pszDomain		The domain to search.
**				astrComputers	The return buffer for the computer names.
**
** Returns:		The number of computers found.
**
*******************************************************************************
*/

size_t CNetFinder::FindComputers(const tchar* pszDomain, CStrArray& astrComputers)
{
	NETRESOURCE oNetRsc = { 0 };

	oNetRsc.dwScope       = RESOURCE_GLOBALNET;
	oNetRsc.dwType        = RESOURCETYPE_ANY;
	oNetRsc.dwDisplayType = RESOURCEDISPLAYTYPE_DOMAIN;
	oNetRsc.dwUsage       = RESOURCEUSAGE_CONTAINER;
	oNetRsc.lpLocalName   = TXT("");
	oNetRsc.lpRemoteName  = const_cast<tchar*>(pszDomain);
	oNetRsc.lpComment     = TXT("");
	oNetRsc.lpProvider    = TXT("");

	FindComputers(&oNetRsc, astrComputers);

	return astrComputers.Size();
}

/******************************************************************************
** Method:		FindComputers()
**
** Description:	Internal method to do the work of finding all computers.
**
** Parameters:	pNetRsc			The network container to enumerate.
**				astrComputers	The return buffer for the computer names.
**
** Returns:		The result of the last call.
**
*******************************************************************************
*/

DWORD CNetFinder::FindComputers(NETRESOURCE* pNetRsc, CStrArray& astrComputers)
{
	DWORD  dwResult = NO_ERROR;
	HANDLE hEnum    = NULL;

	// Start the enumeration.
	if ((dwResult = ::WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, pNetRsc, &hEnum)) == NO_ERROR)
	{
		DWORD        dwBufSize  = 16384;
		NETRESOURCE* pTmpNetRsc = static_cast<NETRESOURCE*>(alloca(dwBufSize));

		// For all resources...
		while ((dwResult == NO_ERROR) || (dwResult == ERROR_MORE_DATA))
		{
			DWORD dwCount = 1;

			if ((dwResult = ::WNetEnumResource(hEnum, &dwCount, pTmpNetRsc, &dwBufSize)) == NO_ERROR)
			{
				// If a computer add it to the list.
				if (pTmpNetRsc->dwDisplayType == RESOURCEDISPLAYTYPE_SERVER)
				{
					astrComputers.Add(pTmpNetRsc->lpRemoteName);
				}
				// If a container, enumerate it.
				else if (pTmpNetRsc->dwUsage & RESOURCEUSAGE_CONTAINER)
				{
					FindComputers(pTmpNetRsc, astrComputers);
				}
			}
		}

		// Enumeration succesful.
		if (dwResult == ERROR_NO_MORE_ITEMS)
			dwResult = NO_ERROR;

		::WNetCloseEnum(hEnum);
	}

	return dwResult;
}
