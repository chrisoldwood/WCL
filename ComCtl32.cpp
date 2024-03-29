/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		COMCTL32.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CComCtl32 class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ComCtl32.hpp"
#include <shlwapi.h>
#include <commctrl.h>

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) // GCC 4.2+
// missing initializer for member 'X'
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
#if (__GNUC__ >= 8) // GCC 8+
// error: cast between incompatible function types
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif

/******************************************************************************
**
** Local types.
**
*******************************************************************************
*/

typedef HRESULT (CALLBACK* DLLGETVERSIONPROC)(DLLVERSIONINFO*);
typedef BOOL    (CALLBACK* INITCOMCTLSEXPROC)(INITCOMMONCONTROLSEX*);

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CComCtl32::CComCtl32()
	: m_oDLL(TXT("COMCTL32.DLL"))
{
	m_oDLL.Load();
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CComCtl32::~CComCtl32()
{
	m_oDLL.Free();
}

/******************************************************************************
** Method:		GetVersion()
**
** Description:	Get the major/minor version number.
**
** Parameters:	dwMajor		The return buffer for the major version.
**				dwMinor		The return buffer for the minor version.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CComCtl32::GetVersion(DWORD& dwMajor, DWORD& dwMinor)
{
	ASSERT(IsLoaded());

	bool bOK = false;

	// Get the DLLs version info function.
	DLLGETVERSIONPROC pfnDllGetVersion = reinterpret_cast<DLLGETVERSIONPROC>(m_oDLL.GetProcAddress("DllGetVersion"));

	if (pfnDllGetVersion != nullptr)
	{
		DLLVERSIONINFO oVerInfo = { 0 };

		oVerInfo.cbSize = sizeof(oVerInfo);

		// Query the version info.
		HRESULT hResult = pfnDllGetVersion(&oVerInfo);

		if (SUCCEEDED(hResult))
		{
			// Extract the major and minor version numbers.
			dwMajor = oVerInfo.dwMajorVersion;
			dwMinor = oVerInfo.dwMinorVersion;
			bOK     = true;
		}
	}

	return bOK;
}

/******************************************************************************
** Method:		Initialise()
**
** Description:	Initialise the requested classes.
**
** Parameters:	dwICC	The class list (See InitCommonControlsEx()).
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CComCtl32::Initialise(DWORD dwICC)
{
	ASSERT(IsLoaded());

	bool bOK = false;

	// Get the DLLs Initialise function.
	INITCOMCTLSEXPROC pfnInitCommonControlsEx = reinterpret_cast<INITCOMCTLSEXPROC>(m_oDLL.GetProcAddress("InitCommonControlsEx"));

	if (pfnInitCommonControlsEx != nullptr)
	{
		INITCOMMONCONTROLSEX oInitInfo = { 0 };

		oInitInfo.dwSize = sizeof(INITCOMMONCONTROLSEX);
		oInitInfo.dwICC  = dwICC;

		if (pfnInitCommonControlsEx(&oInitInfo))
			bOK = true;
	}

	return bOK;
}
