////////////////////////////////////////////////////////////////////////////////
//! \file   AutoCom.hpp
//! \brief  The AutoCom class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_AUTOCOM_HPP
#define WCL_AUTOCOM_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "ComException.hpp"

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! An RAII style class for initialising and uninitialising COM.

class AutoCom
{
public:
	//! Default constructor.
	AutoCom();

	//! Constructor to initialise COM.
	AutoCom(DWORD dwFlags); // throw(ComException)

	//! Destructor.
	~AutoCom();

	//
	// Properties.
	//

	//! Query if COM is initialised.
	bool IsInitialised() const;

	//
	// Methods.
	//

	//! Manually initialise COM.
	void Initialise(DWORD dwFlags); // throw(ComException)

	//! Manually uninitialise COM.
	void Uninitialise();

private:
	//
	// Members.
	//
	bool	m_bInitialised;		//!< Flag to control uninitialisation.
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

inline AutoCom::AutoCom()
	: m_bInitialised(false)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Constructor to initialise COM.

inline AutoCom::AutoCom(DWORD dwFlags)
	: m_bInitialised(false)
{
	Initialise(dwFlags);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

inline AutoCom::~AutoCom()
{
	if (m_bInitialised)
		Uninitialise();
}

////////////////////////////////////////////////////////////////////////////////
//! Query if COM is initialised.

inline bool AutoCom::IsInitialised() const
{
	return m_bInitialised;
}

////////////////////////////////////////////////////////////////////////////////
//! Manually initialise COM.

inline void AutoCom::Initialise(DWORD dwFlags)
{
	ASSERT(!m_bInitialised);

	// Initialise COM.
	HRESULT hr = ::CoInitializeEx(nullptr, dwFlags);

	if (FAILED(hr))
		throw WCL::ComException(hr, TXT("Failed to initialise COM"));

	// Update state.
	m_bInitialised = true;
}

////////////////////////////////////////////////////////////////////////////////
//! Manually uninitialise COM.

inline void AutoCom::Uninitialise()
{
	ASSERT(m_bInitialised);

	// Uninitialise COM.
	::CoUninitialize();

	// Update state.
	m_bInitialised = false;
}

//namespace WCL
}

#endif // WCL_AUTOCOM_HPP
