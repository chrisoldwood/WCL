/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SYSINFO.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CSysInfo class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <lmcons.h>

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
	char  szName[MAX_COMPUTERNAME_LENGTH+1] = { 0 };
	DWORD dwSize = sizeof(szName);

	::GetComputerName(szName, &dwSize);
	
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
	char  szName[UNLEN+1] = { 0 };
	DWORD dwSize = sizeof(szName);

	::GetUserName(szName, &dwSize);
	
	return szName;
}
