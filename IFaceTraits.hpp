////////////////////////////////////////////////////////////////////////////////
//! \file   IFaceTraits.hpp
//! \brief  The IFaceTraits class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_IFACETRAITS_HPP
#define WCL_IFACETRAITS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <basetyps.h>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Interface traits used to workaround compilers which do not support the
//! __uuidof() extension. If the compiler doesn't support the extension you need
//! to specialise the template for each interface type.

// Visual C++
#ifdef _MSC_VER

template <typename T>
struct IFaceTraits
{
	//! Get the GUID for the interface.
	static const IID& uuidof()
	{
		return __uuidof(T);
	}
};

// GCC etc.
#else

template<typename T>
struct IFaceTraits;

////////////////////////////////////////////////////////////////////////////////
//! Declare the traits for a COM interface.
//! NB: Remember to use an #ifdef guard around the macro for non-MS compilers.

#define WCL_DECLARE_IFACETRAITS(iface, iid)		\
namespace WCL									\
{												\
template<>										\
struct IFaceTraits<iface>						\
{												\
	static const IID& uuidof()					\
	{	return iid;	}							\
};												\
}

#endif

//namespace WCL
}

#endif // WCL_IFACETRAITS_HPP
