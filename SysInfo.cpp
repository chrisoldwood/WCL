/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SYSINFO.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CSysInfo class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "SysInfo.hpp"
#include <lmcons.h>
#include "Win32Exception.hpp"

/******************************************************************************
** Method:		ComputerName()
**
** Description:	Gets the name of the computer.
**
** Parameters:	None.
**
** Returns:		The name.
**
*******************************************************************************
*/

CString CSysInfo::ComputerName()
{
	tchar szName[MAX_COMPUTERNAME_LENGTH+1] = { 0 };
	DWORD dwSize = MAX_COMPUTERNAME_LENGTH;

	if (::GetComputerName(szName, &dwSize) == 0)
		throw WCL::Win32Exception(::GetLastError(), TXT("Failed to retrieve the name of the computer"));
	
	return szName;
}

/******************************************************************************
** Method:		UserName()
**
** Description:	Gets the name of the user.
**
** Parameters:	None.
**
** Returns:		The name.
**
*******************************************************************************
*/

CString CSysInfo::UserName()
{
	tchar szName[UNLEN+1] = { 0 };
	DWORD dwSize = UNLEN;

	if (::GetUserName(szName, &dwSize) == 0)
		throw WCL::Win32Exception(::GetLastError(), TXT("Failed to retrieve the name of the user"));
	
	return szName;
}
