////////////////////////////////////////////////////////////////////////////////
//! \file   SeTranslator.cpp
//! \brief  The SeTranslator class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "SeTranslator.hpp"
#include "StructuredException.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor. Install our handler.

SeTranslator::SeTranslator()
	: m_lpfnOldTranslator(nullptr)
{
#ifdef _MSC_VER
	m_lpfnOldTranslator = _set_se_translator(Translate);
#endif
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor. Re-installs the old handler.

SeTranslator::~SeTranslator()
{
#ifdef _MSC_VER
	_se_translator_function lpfn = _set_se_translator(m_lpfnOldTranslator);

	ASSERT(lpfn == Translate);

	DEBUG_USE_ONLY(lpfn);
#endif
}

////////////////////////////////////////////////////////////////////////////////
//! Install our translator function. The method returns the previous translator
//! function and assumes that we never want to uninstall it.

_se_translator_function SeTranslator::Install()
{
#ifdef _MSC_VER
	return _set_se_translator(Translate);
#else
	return nullptr;
#endif
}

////////////////////////////////////////////////////////////////////////////////
//! The translator function.

void SeTranslator::Translate(uint nCode, _EXCEPTION_POINTERS* pInfo)
{
	throw StructuredException(nCode, pInfo);
}

//namespace WCL
}
