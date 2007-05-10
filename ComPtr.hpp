////////////////////////////////////////////////////////////////////////////////
//! \file   ComPtr.hpp
//! \brief  The ComPtr class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef COMPTR_HPP
#define COMPTR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <guiddef.h>
#include <objbase.h>
#include <atlconv.h>

namespace WCL
{

// Forward declarations.
template <typename T>
class ComPtr;

template <typename T>
T** AttachTo(ComPtr<T>& ptr);

////////////////////////////////////////////////////////////////////////////////
//! A smart-pointer type for use with COM objects and interfaces.

template <typename T>
class ComPtr
{
public:
	//! Default constructor.
	ComPtr();

	//! Construction from an existing interface pointer.
	explicit ComPtr(T* pInterface, bool bAddRef = false);

	//! Construction by creating an object of the CLSID.
	explicit ComPtr(const CLSID& rCLSID);

	//! Copy constructor.
	ComPtr(const ComPtr<T>& oPtr);

	//! Destructor.
	~ComPtr();

	//
	// Operators.
	//

	//! Assignment operator.
	ComPtr& operator=(const ComPtr<T>& oPtr);

	//! Pointer dereference operator.
	T& operator*() const;

	//! Pointer-to-member operator.
	const T* operator->() const;

	//! Pointer-to-member operator.
	T* operator->();

	//! Not operator.
    bool operator!() const;

	//
	// Methods.
	//

	//! Access owned interface.
	T* Get() const;

	//! Access owned pointer as a reference.
	T& GetRef() const;

	//! Release the interface.
	void Release();
	
private:
	//
	// Members.
	//
	T*	m_pInterface;		//!< The interface.

	//! Allow attachment via an output parameter.
	friend T** AttachTo<>(ComPtr<T>& ptr);
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

template <typename T>
inline ComPtr<T>::ComPtr()
	: m_pInterface(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from an existing interface pointer.

template <typename T>
inline ComPtr<T>::ComPtr(T* pInterface, bool bAddRef)
	: m_pInterface(pInterface)
{
	if (bAddRef)
	{
		ASSERT(m_pInterface != nullptr);

		m_pInterface->AddRef();
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Construction by creating an object of the CLSID.

template <typename T>
inline ComPtr<T>::ComPtr(const CLSID& rCLSID)
	: m_pInterface(nullptr)
{
	IID oIID = __uuidof(T);

	// Create the object.
	HRESULT hr = ::CoCreateInstance(rCLSID, nullptr, CLSCTX_ALL, oIID, reinterpret_cast<LPVOID*>(&m_pInterface));

	if (FAILED(hr))
	{
		USES_CONVERSION;

		const size_t MAX_GUID_CHARS = 38;
		wchar_t szBuffer[MAX_GUID_CHARS+1];

		// Convert the CLSID to a string.		
		if (::StringFromGUID2(rCLSID, szBuffer, MAX_GUID_CHARS+1) == 0)
			throw std::logic_error("Invalid buffer size passed to StringFromGUID2()");

		CString strCLSID = W2T(szBuffer);

		// Convert the IID to a string.		
		if (::StringFromGUID2(oIID, szBuffer, MAX_GUID_CHARS+1) == 0)
			throw std::logic_error("Invalid buffer size passed to StringFromGUID2()");

		CString strIID = W2T(szBuffer);

		throw ComException(hr, CString::Fmt("Failed to create a COM object of class %s or obtain the interface %s", strCLSID, strIID));
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Copy constructor.

template <typename T>
inline ComPtr<T>::ComPtr(const ComPtr<T>& oPtr)
	: m_pInterface(oPtr.m_pInterface)
{
	if (m_pInterface != nullptr)
		m_pInterface->AddRef();
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template <typename T>
inline ComPtr<T>::~ComPtr()
{
	Release();
}

////////////////////////////////////////////////////////////////////////////////
//! Assignment operator.

template <typename T>
inline ComPtr<T>& ComPtr<T>::operator=(const ComPtr<T>& oPtr)
{
	// Check for self-assignment.
	if ( (this != &oPtr) && (this->m_pInterface != oPtr.m_pInterface) )
	{
		Release();

		m_pInterface = oPtr.m_pInterface;

		if (m_pInterface != nullptr)
			m_pInterface->AddRef();
	}

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//! Pointer dereference operator. Returns the currently owned interface.

template <typename T>
inline T& ComPtr<T>::operator*() const
{
	return *m_pInterface;
}

////////////////////////////////////////////////////////////////////////////////
//! Pointer-to-member operator. Returns the currently owned interface.

template <typename T>
inline const T* ComPtr<T>::operator->() const
{
	return m_pInterface;
}

////////////////////////////////////////////////////////////////////////////////
//! Pointer-to-member operator. Returns the currently owned interface.

template <typename T>
inline T* ComPtr<T>::operator->()
{
	return m_pInterface;
}

////////////////////////////////////////////////////////////////////////////////
//! Not operator. Tests for a NULL pointer.

template <typename T>
bool ComPtr<T>::operator!() const
{
	return (m_pInterface == nullptr);
}

////////////////////////////////////////////////////////////////////////////////
//! Access owned interface. Returns the currently owned interface.

template <typename T>
inline T* ComPtr<T>::Get() const
{
	return m_pInterface;
}

////////////////////////////////////////////////////////////////////////////////
//! Access owned pointer as a reference.

template <typename T>
inline T& ComPtr<T>::GetRef() const
{
	return *m_pInterface;
}

////////////////////////////////////////////////////////////////////////////////
//! Release the interface.

template <typename T>
inline void ComPtr<T>::Release()
{
	if (m_pInterface != nullptr)
	{
		m_pInterface->Release();
		m_pInterface = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Helper function to gain access to the internal member so that it can be
//! passed as an output parameter, e.g. LoadTypeLib().

template <typename T>
inline T** AttachTo(ComPtr<T>& ptr)
{
	return &ptr.m_pInterface;
}

//namespace WCL
}

#endif // COMPTR_HPP
