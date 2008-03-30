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

////////////////////////////////////////////////////////////////////////////////
// Primitive types.

//! GMT based time_t used internally.
typedef time_t seconds_t;

//! Count of days.
typedef time_t days_t;

////////////////////////////////////////////////////////////////////////////////
// Constants.

const seconds_t SECS_PER_MIN  = 60;
const seconds_t SECS_PER_HOUR = 60 * 60;
const seconds_t SECS_PER_DAY  = 60 * 60 * 24;

////////////////////////////////////////////////////////////////////////////////
// General definitions.

//! Specfifier used to export functions.
#define EXPORT		__declspec(dllexport)

//! Specifier used on Window callback functions.
#define WINDOWPROC	CALLBACK

//! Specifier used on Dialog callback functions.
#define DIALOGPROC	CALLBACK

//! Helper for specifying Read and Write access.
#define GENERIC_READWRITE	(GENERIC_READ | GENERIC_WRITE)

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
