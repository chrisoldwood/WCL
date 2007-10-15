////////////////////////////////////////////////////////////////////////////////
//! \file   SeTranslator.hpp
//! \brief  The SeTranslator class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_SETRANSLATOR_HPP
#define WCL_SETRANSLATOR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! The RAII style class used to install and uninstall the Structured Exception
//! translator function.

class SeTranslator
{
public:
	//! Default constructor.
	SeTranslator();

	//! Destructor.
	~SeTranslator();

	//! Install the translator function.
	static _se_translator_function Install();

private:
	//
	// Members.
	//
	_se_translator_function	m_lpfnOldTranslator;	//!< The old translator function.

	//! The translator function.
	static void Translate(uint nCode, _EXCEPTION_POINTERS* pInfo);
};

//namespace WCL
}

#endif // WCL_SETRANSLATOR_HPP
