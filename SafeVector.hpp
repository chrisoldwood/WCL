////////////////////////////////////////////////////////////////////////////////
//! \file   SafeVector.hpp
//! \brief  The SafeVector class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_SAFEVECTOR_HPP
#define WCL_SAFEVECTOR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A Wrapper Facade for a 1-dimension SAFEARRAY.

template <typename T>
class SafeVector : public Core::NotCopyable
{
public:
	//! Default constructor.
	SafeVector();

	//! Construction of a fixed size array.
	explicit SafeVector(size_t nSize, VARTYPE eVarType = VT_VARIANT);

	//! Take ownership of a existing SAFEARRAY.
	explicit SafeVector(SAFEARRAY* pSafeArray, VARTYPE eVarType = VT_VARIANT);

	//! Destructor.
	~SafeVector();

	//
	// Properties.
	//

	//! Get the size of the vector.
	size_t Size() const;

	//
	// Methods.
	//

	// The iterator types.
	typedef T* iterator;
	typedef const T* const_iterator;

	//! Get an iterator to the start of the vector.
	iterator begin();

	//! Get an iterator to one past the end of the vector.
	iterator end();

	//! Take ownership of the SAFEARRAY.
	SAFEARRAY* Detach();
	
private:
	//
	// Members.
	//
	size_t		m_nSize;		//!< The size of the vector.
	SAFEARRAY*	m_pSafeArray;	//!< The underlying SAFEARRAY.
	T*			m_pData;		//!< The SAFEARRAY underlying storage.

	//
	// Internal methods.
	//

	//! Unlock the underlying storage.
	void Unlock();

	//! Release the underlying SAFEARRAY.
	void Release();
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

template <typename T>
inline SafeVector<T>::SafeVector()
	: m_nSize(0)
	, m_pSafeArray(nullptr)
	, m_pData(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction of a fixed size array.

template <typename T>
inline SafeVector<T>::SafeVector(size_t nSize, VARTYPE eVarType)
	: m_nSize(0)
	, m_pSafeArray(nullptr)
	, m_pData(nullptr)
{
	// Allocate the storage for the vector.
	SAFEARRAY* pSafeArray = ::SafeArrayCreateVector(eVarType, 0, nSize);

	if (pSafeArray == nullptr)
		throw WCL::ComException(E_OUTOFMEMORY, TXT("Failed to allocate a SAFEARRAY"));

	T* pData = nullptr;

	// Lock the storage immediately for access.
	HRESULT hr = ::SafeArrayAccessData(pSafeArray, reinterpret_cast<void**>(&pData));

	if (FAILED(hr))
	{
		::SafeArrayDestroy(pSafeArray);
		throw WCL::ComException(hr, TXT("Failed to lock the SAFEARRAY for access"));
	}

	// Update state.
	m_nSize      = nSize;
	m_pSafeArray = pSafeArray;
	m_pData      = pData;
}

////////////////////////////////////////////////////////////////////////////////
//! Take ownership of a existing SAFEARRAY.

template <typename T>
inline SafeVector<T>::SafeVector(SAFEARRAY* pSafeArray, VARTYPE eVarType)
	: m_nSize(0)
	, m_pSafeArray(nullptr)
	, m_pData(nullptr)
{
	VARTYPE eArrayType;

	// Check the value type.
	HRESULT hr = ::SafeArrayGetVartype(pSafeArray, &eArrayType);

	if (FAILED(hr))
	{
		::SafeArrayDestroy(pSafeArray);
		throw WCL::ComException(hr, TXT("Failed to get the SAFEARRAY value type"));
	}

	if (eArrayType != eVarType)
	{
		::SafeArrayDestroy(pSafeArray);
		throw WCL::ComException(E_INVALIDARG, TXT("The SAFEARRAY does not contain the correct value type"));
	}

	// Check the number of dimensions.
	UINT nDims = ::SafeArrayGetDim(pSafeArray);

	if (nDims != 1)
	{
		::SafeArrayDestroy(pSafeArray);
		throw WCL::ComException(E_INVALIDARG, TXT("The SAFEARRAY does not contain a single dimension"));
	}

	LONG lLowerBound;
	LONG lUpperBound;

	// Get the lower and upper bounds.
	hr = ::SafeArrayGetLBound(pSafeArray, 1, &lLowerBound);

	if (FAILED(hr))
	{
		::SafeArrayDestroy(pSafeArray);
		throw WCL::ComException(hr, TXT("Failed to get the SAFEARRAY lower bound"));
	}

	hr = ::SafeArrayGetUBound(pSafeArray, 1, &lUpperBound);

	if (FAILED(hr))
	{
		::SafeArrayDestroy(pSafeArray);
		throw WCL::ComException(hr, TXT("Failed to get the SAFEARRAY upper bound"));
	}

	T* pData = nullptr;

	// Lock the storage immediately for access.
	hr = ::SafeArrayAccessData(pSafeArray, reinterpret_cast<void**>(&pData));

	if (FAILED(hr))
	{
		::SafeArrayDestroy(pSafeArray);
		throw WCL::ComException(hr, TXT("Failed to lock the SAFEARRAY for access"));
	}

	// Update state.
	m_nSize      = lUpperBound - lLowerBound + 1;
	m_pSafeArray = pSafeArray;
	m_pData      = pData;
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template <typename T>
inline SafeVector<T>::~SafeVector()
{
	Release();

	ASSERT(m_nSize == 0);
	ASSERT(m_pSafeArray == nullptr);
	ASSERT(m_pData == nullptr);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the size of the vector.

template <typename T>
inline size_t SafeVector<T>::Size() const
{
	return m_nSize;
}

////////////////////////////////////////////////////////////////////////////////
//! Get an iterator to the start of the vector.

template <typename T>
inline typename SafeVector<T>::iterator SafeVector<T>::begin()
{
	ASSERT(m_pData != nullptr);

	return m_pData;
}

////////////////////////////////////////////////////////////////////////////////
//! Get an iterator to one past the end of the vector.

template <typename T>
inline typename SafeVector<T>::iterator SafeVector<T>::end()
{
	ASSERT(m_pData != nullptr);

	return m_pData+m_nSize;
}

////////////////////////////////////////////////////////////////////////////////
//! Take ownership of the SAFEARRAY.

template <typename T>
inline SAFEARRAY* SafeVector<T>::Detach()
{
	Unlock();

	SAFEARRAY* pSafeArray = m_pSafeArray;

	// Reset members.
	m_nSize      = 0;
	m_pSafeArray = nullptr;

	return pSafeArray;
}

////////////////////////////////////////////////////////////////////////////////
//! Unlock the underlying storage.

template <typename T>
inline void SafeVector<T>::Unlock()
{
	if (m_pData != nullptr)
	{
		ASSERT(m_pSafeArray != nullptr);

		::SafeArrayUnaccessData(m_pSafeArray);

		m_pData = nullptr;
	}
}


////////////////////////////////////////////////////////////////////////////////
//! Release the underlying SAFEARRAY. This also unlocks the storage first if
//! required.

template <typename T>
inline void SafeVector<T>::Release()
{
	Unlock();

	// Free the storage.
	if (m_pSafeArray != nullptr)
	{
		::SafeArrayDestroy(m_pSafeArray);

		m_nSize      = 0;
		m_pSafeArray = nullptr;
	}
}

//namespace WCL
}

#endif // WCL_SAFEVECTOR_HPP
