////////////////////////////////////////////////////////////////////////////////
//! \file   TestIFaceTraits.hpp
//! \brief  The IFaceTraits used for the COM based tests.
//! \author Chris Oldwood

#ifndef _MSC_VER
#include <ocidl.h>
WCL_DECLARE_IFACETRAITS(IUnknown, IID_IUnknown);
WCL_DECLARE_IFACETRAITS(IClassFactory, IID_IClassFactory);
WCL_DECLARE_IFACETRAITS(IMalloc, IID_IMalloc);
WCL_DECLARE_IFACETRAITS(IErrorLog, IID_IErrorLog);
WCL_DECLARE_IFACETRAITS(IErrorInfo, IID_IErrorInfo);
#endif
