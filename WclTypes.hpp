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

////////////////////////////////////////////////////////////////////////////////
// Definitions.

//! Specfifier used to export functions.
#define EXPORT		__declspec(dllexport)

//! Specifier used on Window callback functions.
#define WINDOWPROC	CALLBACK

//! Specifier used on Dialog callback functions.
#define DIALOGPROC	CALLBACK

//! Helper for specifying Read and Write access.
#define GENERIC_READWRITE	(GENERIC_READ | GENERIC_WRITE)

#endif // WCL_WCLTYPES_HPP
