////////////////////////////////////////////////////////////////////////////////
//! \file   ComPtr.hpp
//! \brief  The ComPtr class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_COMPTR_HPP
#define WCL_COMPTR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "IFacePtr.hpp"
#include "ComException.hpp"
#include <objbase.h>
#include <Core/AnsiWide.hpp>
#include <Core/BadLogicException.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A smart-pointer type for use with COM objects and interfaces. This IFacePtr
//! derived class adds the ability to create objects via their CLSIDs as well
//! as managing the lifetimes of COM interfaces.

template <typename T>
class ComPtr : public IFacePtr<T>
{
public:
	//! Default constructor.
	ComPtr();

	//! Construction from an existing interface pointer.
	explicit ComPtr(T* pInterface, bool bAddRef = false);

	//! Construction by creating an object of the CLSID.
	explicit ComPtr(const CLSID& rCLSID); // throw(ComException)

	//! Copy constructor.
	ComPtr(const ComPtr& rhs);

	//! Aquire a different interface for another COM object.
	template <typename U>
	explicit ComPtr(const IFacePtr<U>& rhs); // throw(ComException)

	//! Destructor.
	~ComPtr();

	//
	// Operators.
	//

	//! Assignment operator.
	ComPtr& operator=(const ComPtr& rhs);

	//! Aquire a different interface for another COM object.
	template <typename U>
	ComPtr& operator=(const IFacePtr<U>& rhs);

	//
	// Methods.
	//

	//! Create an instance of the object.
	void CreateInstance(const CLSID& rCLSID); // throw(ComException)

	//! Aquire a different interface for another COM object.
	template <typename U>
	void QueryInterface(const IFacePtr<U>& rhs); // throw(ComException)

private:
	//
	// Members.
	//

	//! Maximum number of characters in a GUID string.
	static const size_t MAX_GUID_CHARS = 38;
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

template <typename T>
inline ComPtr<T>::ComPtr()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from an existing interface pointer.

template <typename T>
inline ComPtr<T>::ComPtr(T* pInterface, bool bAddRef)
	: IFacePtr<T>(pInterface, bAddRef)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction by creating an object of the CLSID.

template <typename T>
inline ComPtr<T>::ComPtr(const CLSID& rCLSID)
	: IFacePtr<T>(nullptr)
{
	CreateInstance(rCLSID);
}

////////////////////////////////////////////////////////////////////////////////
//! Copy constructor.

template <typename T>
inline ComPtr<T>::ComPtr(const ComPtr& rhs)
	: IFacePtr<T>(rhs)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Aquire a different interface for another COM object.

template <typename T> template <typename U>
inline ComPtr<T>::ComPtr(const IFacePtr<U>& rhs)
{
	QueryInterface(rhs);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template <typename T>
inline ComPtr<T>::~ComPtr()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Assignment operator.

template <typename T>
inline ComPtr<T>& ComPtr<T>::operator=(const ComPtr& rhs)
{
	IFacePtr<T>::operator=(rhs);

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//! Aquire a different interface for another COM object.

template <typename T> template <typename U>
inline ComPtr<T>& ComPtr<T>::operator=(const IFacePtr<U>& rhs)
{
	QueryInterface(rhs);

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//! Create an instance of the object.

template <typename T>
inline void ComPtr<T>::CreateInstance(const CLSID& rCLSID)
{
	// Release the current interface.
	this->Release();

	const IID& oIID = IFaceTraits<T>::uuidof();

	// Create the object.
	HRESULT hr = ::CoCreateInstance(rCLSID, nullptr, CLSCTX_ALL, oIID, reinterpret_cast<LPVOID*>(&this->m_pPointer));

	if (FAILED(hr))
	{
		wchar_t szBuffer[MAX_GUID_CHARS+1];

		// Convert the CLSID to a string.
		if (::StringFromGUID2(rCLSID, szBuffer, MAX_GUID_CHARS+1) == 0)
			throw Core::BadLogicException(TXT("Invalid buffer size passed to StringFromGUID2()"));

		CString strCLSID = W2T(szBuffer);

		// Convert the IID to a string.
		if (::StringFromGUID2(oIID, szBuffer, MAX_GUID_CHARS+1) == 0)
			throw Core::BadLogicException(TXT("Invalid buffer size passed to StringFromGUID2()"));

		CString strIID = W2T(szBuffer);

		throw ComException(hr, CString::Fmt(TXT("Failed to create a COM object of class %s or obtain the interface %s"), strCLSID.c_str(), strIID.c_str()));
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Aquire a different interface for another COM object.

template <typename T> template <typename U>
inline void ComPtr<T>::QueryInterface(const IFacePtr<U>& rhs)
{
	// Release the current interface.
	this->Release();

	const IID& oIID = IFaceTraits<T>::uuidof();

	HRESULT hr = rhs.get()->QueryInterface(oIID, reinterpret_cast<LPVOID*>(&this->m_pPointer));

	if (FAILED(hr))
	{
		wchar_t szBuffer[MAX_GUID_CHARS+1];

		// Convert the IID to a string.
		if (::StringFromGUID2(oIID, szBuffer, MAX_GUID_CHARS+1) == 0)
			throw Core::BadLogicException(TXT("Invalid buffer size passed to StringFromGUID2()"));

		CString strIID = W2T(szBuffer);

		throw ComException(hr, CString::Fmt(TXT("Failed to obtain the interface %s"), strIID.c_str()));
	}
}

//namespace WCL
}

#endif // WCL_COMPTR_HPP
