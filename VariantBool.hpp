////////////////////////////////////////////////////////////////////////////////
//! \file   VariantBool.hpp
//! \brief  Helper functions for dealing with the COM VARIANT_BOOL type.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_VARIANTBOOL_HPP
#define WCL_VARIANTBOOL_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! Convert a C++ bool to a VARIANT_BOOL.

inline VARIANT_BOOL ToVariantBool(bool bValue)
{
	return (bValue) ? VARIANT_TRUE : VARIANT_FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//! Query if a VARIANT_BOOL is equivalent to 'true'.

inline bool IsTrue(VARIANT_BOOL bValue)
{
	return (bValue == VARIANT_TRUE) ? true : false;
}

////////////////////////////////////////////////////////////////////////////////
//! Query if a VARIANT_BOOL is equivalent to 'false'.

inline bool IsFalse(VARIANT_BOOL bValue)
{
	return (bValue != VARIANT_TRUE) ? true : false;
}

#endif // WCL_VARIANTBOOL_HPP
