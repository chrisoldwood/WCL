/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SYSINFO.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CSysInfo class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SYSINFO_HPP
#define SYSINFO_HPP

/******************************************************************************
** 
** A class of static methods to get system information.
**
*******************************************************************************
*/

class CSysInfo
{
public:
	//
	// Methods.
	//
	static CString ComputerName();
	static CString UserName();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // SYSINFO_HPP
