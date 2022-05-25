////////////////////////////////////////////////////////////////////////////////
//! \file   WCLTypes.hpp
//! \brief  Windows C++ library common types and macros.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_WCLTYPES_HPP
#define WCL_WCLTYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
// Internal primitive types.

//! GMT based time_t used internally.
typedef time_t Seconds;

//! Count of days.
typedef time_t Days;

////////////////////////////////////////////////////////////////////////////////
// Windows API types.

//! The position within a stream.
typedef unsigned __int64 StreamPos;

#ifdef _WIN64
//! The ID of a timer.
typedef UINT_PTR TimerID;
#else
//! The ID of a timer.
typedef UINT TimerID;
#endif

//! The virtual code or character code of a key.
typedef WORD KeyCode;

//! The full state of a virtual key.
typedef DWORD KeyState;

//! The virtual key flags defined by the MK_* constants.
typedef uint KeyFlags;

//! The resize flags defined by the SIZE_* constants.
typedef int ResizeFlags;

//! The scrollbar flags defined by the SB_* constants.
typedef uint ScrollbarFlags;

#ifdef _WIN64
//! The ID of a child control.
typedef UINT_PTR ControlID;
#else
//! The ID of a child control.
typedef UINT ControlID;
#endif

#ifdef _WIN64
//! The handle or ID of an object.
typedef UINT_PTR HandleOrID;
#else
//! The handle or ID of an object.
typedef UINT HandleOrID;
#endif

#ifdef _WIN64
//! The result type of a DLGPROC.
typedef INT_PTR DlgResult;
#else
//! The result type of a DLGPROC.
typedef BOOL DlgResult;
#endif

////////////////////////////////////////////////////////////////////////////////
// Constants.

const Seconds SECS_PER_MIN  = 60;
const Seconds SECS_PER_HOUR = 60 * 60;
const Seconds SECS_PER_DAY  = 60 * 60 * 24;

//namespace WCL
}

////////////////////////////////////////////////////////////////////////////////
// General definitions.

//! Specifier used to export functions.
#define EXPORT		__declspec(dllexport)

//! Specifier used on Window callback functions.
#define WINDOWPROC	CALLBACK

//! Specifier used on Dialog callback functions.
#define DIALOGPROC	CALLBACK

//! Helpers for specifying Read and Write access.
#define GENERIC_NONE		0
#define GENERIC_READWRITE	(GENERIC_READ | GENERIC_WRITE)

//! Helper for specifying a clipboard format.
#define CF_NONE		0

////////////////////////////////////////////////////////////////////////////////
// Text handling types and definitions.

//! The storage format for a chunk of text.
enum TextFormat
{
	ANSI_TEXT,		//! ANSI text. Assume 1 byte per character.
	UNICODE_TEXT,	//! Unicode text. Assume 2 bytes per character + optional 0xFFFE header.
};

#ifdef ANSI_BUILD
//! The build independent clipboard text format.
# define CF_TCHAR_TEXT	CF_TEXT
#else
//! The build independent clipboard text format.
# define CF_TCHAR_TEXT	CF_UNICODETEXT
#endif

#endif // WCL_WCLTYPES_HPP
