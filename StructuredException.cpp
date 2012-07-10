////////////////////////////////////////////////////////////////////////////////
//! \file   StructuredException.cpp
//! \brief  The StructuredException class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "StructuredException.hpp"
#include <Core/StringUtils.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

StructuredException::StructuredException(uint nCode, _EXCEPTION_POINTERS* /*pInfo*/)
	: m_nCode(nCode)
{
	const tchar* pszCode = FormatCode(m_nCode);

	if (pszCode != nullptr)
		m_details = Core::fmt(TXT("Structured Exception: %s"), pszCode);
	else
		m_details = Core::fmt(TXT("Unknown Structured Exception: 0x%08X"), nCode);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

StructuredException::~StructuredException() throw()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Internal method to convert the exception code to a string. This returns
//! NULL if the exception code is not a standard one.

const tchar* StructuredException::FormatCode(uint nCode)
{
	switch (nCode)
	{
		case EXCEPTION_ACCESS_VIOLATION:			return TXT("EXCEPTION_ACCESS_VIOLATION");
		case EXCEPTION_DATATYPE_MISALIGNMENT:		return TXT("EXCEPTION_DATATYPE_MISALIGNMENT");
		case EXCEPTION_BREAKPOINT:					return TXT("EXCEPTION_BREAKPOINT");
		case EXCEPTION_SINGLE_STEP:					return TXT("EXCEPTION_SINGLE_STEP");
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:		return TXT("EXCEPTION_ARRAY_BOUNDS_EXCEEDED");
		case EXCEPTION_FLT_DENORMAL_OPERAND:		return TXT("EXCEPTION_FLT_DENORMAL_OPERAND");
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:			return TXT("EXCEPTION_FLT_DIVIDE_BY_ZERO");
		case EXCEPTION_FLT_INEXACT_RESULT:			return TXT("EXCEPTION_FLT_INEXACT_RESULT");
		case EXCEPTION_FLT_INVALID_OPERATION:		return TXT("EXCEPTION_FLT_INVALID_OPERATION");
		case EXCEPTION_FLT_OVERFLOW:				return TXT("EXCEPTION_FLT_OVERFLOW");
		case EXCEPTION_FLT_STACK_CHECK:				return TXT("EXCEPTION_FLT_STACK_CHECK");
		case EXCEPTION_FLT_UNDERFLOW:				return TXT("EXCEPTION_FLT_UNDERFLOW");
		case EXCEPTION_INT_DIVIDE_BY_ZERO:			return TXT("EXCEPTION_INT_DIVIDE_BY_ZERO");
		case EXCEPTION_INT_OVERFLOW:				return TXT("EXCEPTION_INT_OVERFLOW");
		case EXCEPTION_PRIV_INSTRUCTION:			return TXT("EXCEPTION_PRIV_INSTRUCTION");
		case EXCEPTION_IN_PAGE_ERROR:				return TXT("EXCEPTION_IN_PAGE_ERROR");
		case EXCEPTION_ILLEGAL_INSTRUCTION:			return TXT("EXCEPTION_ILLEGAL_INSTRUCTION");
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:	return TXT("EXCEPTION_NONCONTINUABLE_EXCEPTION");
		case EXCEPTION_STACK_OVERFLOW:				return TXT("EXCEPTION_STACK_OVERFLOW");
		case EXCEPTION_INVALID_DISPOSITION:			return TXT("EXCEPTION_INVALID_DISPOSITION");
		case EXCEPTION_GUARD_PAGE:					return TXT("EXCEPTION_GUARD_PAGE");
		case EXCEPTION_INVALID_HANDLE:				return TXT("EXCEPTION_INVALID_HANDLE");
		default:									ASSERT_FALSE();
	}

	return TXT("EXCEPTION_???");
}

//namespace WCL
}
