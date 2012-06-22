////////////////////////////////////////////////////////////////////////////////
//! \file   VariantVector.hpp
//! \brief  The VariantVector class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_VARIANTVECTOR_HPP
#define WCL_VARIANTVECTOR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "ComException.hpp"
#include <Core/Scoped.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! A Wrapper Facade for a 1-dimension SAFEARRAY.

template <typename T>
class VariantVector : public Core::NotCopyable
{
public:
	//! Default constructor.
	VariantVector();

	//! Construction of a fixed size array.
	explicit VariantVector(size_t nSize, VARTYPE eVarType = VT_VARIANT);

	//! Take ownership of an existing SAFEARRAY.
	explicit VariantVector(SAFEARRAY* pSafeArray, VARTYPE eVarType = VT_VARIANT, bool bOwner = true);

	//! Destructor.
	~VariantVector();

	//
	// Properties.
	//

	//! Get the size of the vector.
	size_t Size() const;

	//
	// Operators.
	//

	//! Access the element at the given index.
	const T& operator[](size_t index) const;

	//! Access the element at the given index.
	T& operator[](size_t index);

	//
	// Methods.
	//

	// The iterator types.
	typedef T* iterator;
	typedef const T* const_iterator;

	//! Get an iterator to the start of the vector.
	const_iterator begin() const;

	//! Get an iterator to the start of the vector.
	iterator begin();

	//! Get an iterator to one past the end of the vector.
	const_iterator end() const;

	//! Get an iterator to one past the end of the vector.
	iterator end();

	//! Take ownership of the SAFEARRAY.
	SAFEARRAY* Detach();
	
private:
	//! The RAII type used to manage the SAFEARRAY.
	typedef Core::Scoped<SAFEARRAY*> SafeArrayPtr;

	//
	// Members.
	//
	size_t		m_nSize;		//!< The size of the vector.
	SAFEARRAY*	m_pSafeArray;	//!< The underlying SAFEARRAY.
	bool		m_bOwner;		//!< Flag to signal ownership of the underlying SAFEARRAY.
	T*			m_pData;		//!< The SAFEARRAY underlying storage.

	//
	// Internal methods.
	//

	//! Unlock the underlying storage.
	void Unlock();

	//! Release the underlying SAFEARRAY.
	void Release();

	//! Helper function for destroying a SAFEARRAY as a Scoped<SAFEARRAY*>.
	static void DestroySafeArray(SAFEARRAY* pSafeArray);
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

template <typename T>
inline VariantVector<T>::VariantVector()
	: m_nSize(0)
	, m_pSafeArray(nullptr)
	, m_bOwner(false)
	, m_pData(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction of a fixed size array.

template <typename T>
inline VariantVector<T>::VariantVector(size_t nSize, VARTYPE eVarType)
	: m_nSize(0)
	, m_pSafeArray(nullptr)
	, m_bOwner(false)
	, m_pData(nullptr)
{
	// Allocate the storage for the vector.
	SafeArrayPtr safeArray(::SafeArrayCreateVector(eVarType, 0, static_cast<ULONG>(nSize)), DestroySafeArray);

	if (safeArray.get() == nullptr)
		throw WCL::ComException(E_OUTOFMEMORY, TXT("Failed to allocate a SAFEARRAY"));

	T* pData = nullptr;

	// Lock the storage immediately for access.
	HRESULT hr = ::SafeArrayAccessData(safeArray.get(), reinterpret_cast<void**>(&pData));

	if (FAILED(hr))
		throw WCL::ComException(hr, TXT("Failed to lock the SAFEARRAY for access"));

	// Update state.
	m_nSize      = nSize;
	m_pSafeArray = safeArray.detach();
	m_bOwner     = true;
	m_pData      = pData;
}

////////////////////////////////////////////////////////////////////////////////
//! Take ownership of an existing SAFEARRAY.

template <typename T>
inline VariantVector<T>::VariantVector(SAFEARRAY* pSafeArray, VARTYPE eVarType, bool bOwner)
	: m_nSize(0)
	, m_pSafeArray(nullptr)
	, m_bOwner(false)
	, m_pData(nullptr)
{
	// Temporarily manage input SAFEARRAY, if the new owner.
	SafeArrayPtr safeArray(DestroySafeArray);

	if (bOwner)
		safeArray.attach(pSafeArray);

	VARTYPE eArrayType;

	// Check the value type.
	HRESULT hr = ::SafeArrayGetVartype(pSafeArray, &eArrayType);

	if (FAILED(hr))
		throw WCL::ComException(hr, TXT("Failed to get the SAFEARRAY value type"));

	if (eArrayType != eVarType)
		throw WCL::ComException(E_INVALIDARG, TXT("The SAFEARRAY does not contain the correct value type"));

	// Check the number of dimensions.
	UINT nDims = ::SafeArrayGetDim(pSafeArray);

	if (nDims != 1)
		throw WCL::ComException(E_INVALIDARG, TXT("The SAFEARRAY does not contain a single dimension"));

	LONG lLowerBound;
	LONG lUpperBound;

	// Get the lower and upper bounds.
	hr = ::SafeArrayGetLBound(pSafeArray, 1, &lLowerBound);

	if (FAILED(hr))
		throw WCL::ComException(hr, TXT("Failed to get the SAFEARRAY lower bound"));

	hr = ::SafeArrayGetUBound(pSafeArray, 1, &lUpperBound);

	if (FAILED(hr))
		throw WCL::ComException(hr, TXT("Failed to get the SAFEARRAY upper bound"));

	T* pData = nullptr;

	// Lock the storage immediately for access.
	hr = ::SafeArrayAccessData(pSafeArray, reinterpret_cast<void**>(&pData));

	if (FAILED(hr))
		throw WCL::ComException(hr, TXT("Failed to lock the SAFEARRAY for access"));

	// Update state.
	m_nSize      = lUpperBound - lLowerBound + 1;
	m_pSafeArray = (bOwner) ? safeArray.detach() : pSafeArray;
	m_bOwner     = bOwner;
	m_pData      = pData;
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template <typename T>
inline VariantVector<T>::~VariantVector()
{
	Release();

	ASSERT(m_nSize == 0);
	ASSERT(m_pSafeArray == nullptr);
	ASSERT(m_bOwner == false);
	ASSERT(m_pData == nullptr);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the size of the vector.

template <typename T>
inline size_t VariantVector<T>::Size() const
{
	return m_nSize;
}

////////////////////////////////////////////////////////////////////////////////
//! Access the element at the given index.

template <typename T>
inline const T& VariantVector<T>::operator[](size_t index) const
{
	ASSERT(index < Size());
	ASSERT(m_pData != nullptr);

	return *(m_pData+index);
}

////////////////////////////////////////////////////////////////////////////////
//! Access the element at the given index.

template <typename T>
inline T& VariantVector<T>::operator[](size_t index)
{
	ASSERT(index < Size());
	ASSERT(m_pData != nullptr);

	return *(m_pData+index);
}

////////////////////////////////////////////////////////////////////////////////
//! Get an iterator to the start of the vector.

template <typename T>
inline typename VariantVector<T>::const_iterator VariantVector<T>::begin() const
{
	ASSERT(m_pData != nullptr);

	return m_pData;
}

////////////////////////////////////////////////////////////////////////////////
//! Get an iterator to the start of the vector.

template <typename T>
inline typename VariantVector<T>::iterator VariantVector<T>::begin()
{
	ASSERT(m_pData != nullptr);

	return m_pData;
}

////////////////////////////////////////////////////////////////////////////////
//! Get an iterator to one past the end of the vector.

template <typename T>
inline typename VariantVector<T>::const_iterator VariantVector<T>::end() const
{
	ASSERT(m_pData != nullptr);

	return m_pData+m_nSize;
}

////////////////////////////////////////////////////////////////////////////////
//! Get an iterator to one past the end of the vector.

template <typename T>
inline typename VariantVector<T>::iterator VariantVector<T>::end()
{
	ASSERT(m_pData != nullptr);

	return m_pData+m_nSize;
}

////////////////////////////////////////////////////////////////////////////////
//! Take ownership of the SAFEARRAY.

template <typename T>
inline SAFEARRAY* VariantVector<T>::Detach()
{
	Unlock();

	SAFEARRAY* pSafeArray = m_pSafeArray;

	// Reset members.
	m_nSize      = 0;
	m_pSafeArray = nullptr;
	m_bOwner     = false;

	return pSafeArray;
}

////////////////////////////////////////////////////////////////////////////////
//! Unlock the underlying storage.

template <typename T>
inline void VariantVector<T>::Unlock()
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
inline void VariantVector<T>::Release()
{
	Unlock();

	// Free the storage.
	if (m_pSafeArray != nullptr)
	{
		if (m_bOwner)
			::SafeArrayDestroy(m_pSafeArray);

		m_nSize      = 0;
		m_pSafeArray = nullptr;
		m_bOwner     = false;
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Helper function for destroying a SAFEARRAY as a Scoped<SAFEARRAY*>.

template <typename T>
inline void VariantVector<T>::DestroySafeArray(SAFEARRAY* pSafeArray)
{
	::SafeArrayDestroy(pSafeArray);
}

//namespace WCL
}

#endif // WCL_VARIANTVECTOR_HPP
