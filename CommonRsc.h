////////////////////////////////////////////////////////////////////////////////
//! \file   CommonRsc.h
//! \brief  Wrapper include file for the basic Resource file defintions.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_COMMONRSC_H
#define WCL_COMMONRSC_H

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef  APSTUDIO_INVOKED
//! Hide the following symbols from the resource editor.
#define APSTUDIO_HIDDEN_SYMBOLS
#endif

#include <Core/WinTargets.hpp>
#include <winresrc.h>

#ifdef APSTUDIO_INVOKED
//! Stop hiding symbols.
#undef APSTUDIO_HIDDEN_SYMBOLS
#endif

////////////////////////////////////////////////////////////////////////////////
// System Menu hints.

#define	IDS_SYS_RESTORE					61728
#define	IDS_SYS_MOVE					61456
#define	IDS_SYS_SIZE					61440
#define	IDS_SYS_MINIMIZE				61472
#define	IDS_SYS_MAXIMIZE				61488
#define	IDS_SYS_CLOSE					61536
#define	IDS_SYS_SWITCH					61744

#endif // WCL_COMMONRSC_H
