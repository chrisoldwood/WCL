////////////////////////////////////////////////////////////////////////////////
//! \file   StructuredException.cpp
//! \brief  The StructuredException class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "StructuredException.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

StructuredException::StructuredException(uint nCode, _EXCEPTION_POINTERS* /*pInfo*/)
	: m_nCode(nCode)
{
	const tchar* pszCode = FormatCode(m_nCode);

	if (pszCode != nullptr)
		m_strErrorText.Format("Structured Exception: %s", pszCode);
	else 
		m_strErrorText.Format("Unknown Structured Exception: 0x%08X", nCode);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

StructuredException::~StructuredException()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Internal method to convert the exception code to a string. This returns
//! NULL if the exception code is not a standard one.

const tchar* StructuredException::FormatCode(uint nCode)
{
	switch (nCode)
	{
		case EXCEPTION_ACCESS_VIOLATION:			return "EXCEPTION_ACCESS_VIOLATION";
		case EXCEPTION_DATATYPE_MISALIGNMENT:		return "EXCEPTION_DATATYPE_MISALIGNMENT";
		case EXCEPTION_BREAKPOINT:					return "EXCEPTION_BREAKPOINT";
		case EXCEPTION_SINGLE_STEP:					return "EXCEPTION_SINGLE_STEP";
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:		return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
		case EXCEPTION_FLT_DENORMAL_OPERAND:		return "EXCEPTION_FLT_DENORMAL_OPERAND";
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:			return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
		case EXCEPTION_FLT_INEXACT_RESULT:			return "EXCEPTION_FLT_INEXACT_RESULT";
		case EXCEPTION_FLT_INVALID_OPERATION:		return "EXCEPTION_FLT_INVALID_OPERATION";
		case EXCEPTION_FLT_OVERFLOW:				return "EXCEPTION_FLT_OVERFLOW";
		case EXCEPTION_FLT_STACK_CHECK:				return "EXCEPTION_FLT_STACK_CHECK";
		case EXCEPTION_FLT_UNDERFLOW:				return "EXCEPTION_FLT_UNDERFLOW";
		case EXCEPTION_INT_DIVIDE_BY_ZERO:			return "EXCEPTION_INT_DIVIDE_BY_ZERO";
		case EXCEPTION_INT_OVERFLOW:				return "EXCEPTION_INT_OVERFLOW";
		case EXCEPTION_PRIV_INSTRUCTION:			return "EXCEPTION_PRIV_INSTRUCTION";
		case EXCEPTION_IN_PAGE_ERROR:				return "EXCEPTION_IN_PAGE_ERROR";
		case EXCEPTION_ILLEGAL_INSTRUCTION:			return "EXCEPTION_ILLEGAL_INSTRUCTION";
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:	return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
		case EXCEPTION_STACK_OVERFLOW:				return "EXCEPTION_STACK_OVERFLOW";
		case EXCEPTION_INVALID_DISPOSITION:			return "EXCEPTION_INVALID_DISPOSITION";
		case EXCEPTION_GUARD_PAGE:					return "EXCEPTION_GUARD_PAGE";
		case EXCEPTION_INVALID_HANDLE:				return "EXCEPTION_INVALID_HANDLE";
	}

	return nullptr;
}

//namespace WCL
}
