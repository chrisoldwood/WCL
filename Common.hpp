////////////////////////////////////////////////////////////////////////////////
//! \file   Common.hpp
//! \brief  Wrapper to include the most common WCL library headers.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_COMMON_HPP
#define WCL_COMMON_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
// Library documentation
//
//! \namespace WCL
//! \brief     The Windows C++ Library namespace.

////////////////////////////////////////////////////////////////////////////////
// Standard headers.

#include <Core/Common.hpp>		// Core library common headers.
#include <windows.h>			// Standard Windows header.
#include <windowsx.h>			// Additional Windows types and macros.

////////////////////////////////////////////////////////////////////////////////
// Library headers.

#include "WCLTypes.hpp"
#include "String.hpp"

#endif // WCL_COMMON_HPP
