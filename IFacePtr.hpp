////////////////////////////////////////////////////////////////////////////////
//! \file   IFacePtr.hpp
//! \brief  The IFacePtr class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WCL_IFACEPTR_HPP
#define WCL_IFACEPTR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "IFaceTraits.hpp"

namespace WCL
{

// Forward declarations.
template <typename T>
class IFacePtr;

template <typename T>
T** AttachTo(IFacePtr<T>& ptr);

////////////////////////////////////////////////////////////////////////////////
//! A smart-pointer type for use with COM interfaces. This class can only be
//! used to manage the lifetime of COM interfaces, to create COM objects and
//! aquire other interfaces use the ComPtr<T> class.

template <typename T>
class IFacePtr : public Core::SmartPtr<T>
{
public:
	//! Default constructor.
	IFacePtr();

	//! Construction from an existing interface pointer.
	explicit IFacePtr(T* pInterface, bool bAddRef = false);

	//! Copy constructor.
	IFacePtr(const IFacePtr& oPtr);

	//! Destructor.
	~IFacePtr();

	//
	// Operators.
	//

	//! Assignment operator.
	IFacePtr& operator=(const IFacePtr& oPtr);

	//
	// Methods.
	//

	//! Release the interface.
	void Release();

	//! Take ownership of the interface.
	T* Detach();

private:
	//! Access the underlying pointer member.
	T** GetPtrMember();

	//! Allow attachment via an output parameter.
	friend T** AttachTo<>(IFacePtr<T>& ptr);
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

template <typename T>
inline IFacePtr<T>::IFacePtr()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from an existing interface pointer.

template <typename T>
inline IFacePtr<T>::IFacePtr(T* pInterface, bool bAddRef)
	: Core::SmartPtr<T>(pInterface)
{
	if ((this->m_pPointer != nullptr) && bAddRef)
		this->m_pPointer->AddRef();
}

////////////////////////////////////////////////////////////////////////////////
//! Copy constructor.

template <typename T>
inline IFacePtr<T>::IFacePtr(const IFacePtr& oPtr)
	: Core::SmartPtr<T>(oPtr.m_pPointer)
{
	if (this->m_pPointer != nullptr)
		this->m_pPointer->AddRef();
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template <typename T>
inline IFacePtr<T>::~IFacePtr()
{
	Release();
}

////////////////////////////////////////////////////////////////////////////////
//! Assignment operator.

template <typename T>
inline IFacePtr<T>& IFacePtr<T>::operator=(const IFacePtr& oPtr)
{
	// Check for self-assignment.
	if ( (this != &oPtr) && (this->m_pPointer != oPtr.m_pPointer) )
	{
		Release();

		this->m_pPointer = oPtr.m_pPointer;

		if (this->m_pPointer != nullptr)
			this->m_pPointer->AddRef();
	}

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//! Release the interface.

template <typename T>
inline void IFacePtr<T>::Release()
{
	if (this->m_pPointer != nullptr)
	{
		this->m_pPointer->Release();
		this->m_pPointer = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Take ownership of the interface.

template <typename T>
inline T* IFacePtr<T>::Detach()
{
	T* pPointer = this->m_pPointer;

	this->m_pPointer = nullptr;

	return pPointer;
}

////////////////////////////////////////////////////////////////////////////////
//! Access the underlying pointer member. This is used by the AttachTo() friend
//! function to access the underlying SmartPtr<T> member variable.

template <typename T>
inline T** IFacePtr<T>::GetPtrMember()
{
	return &this->m_pPointer;
}

////////////////////////////////////////////////////////////////////////////////
//! Helper function to gain access to the internal member so that it can be
//! passed as an output parameter, without overloading the & operator.
//! e.g. LoadTypeLib(..., AttachTo(p)).

template <typename T>
inline T** AttachTo(IFacePtr<T>& ptr)
{
	ASSERT(*ptr.GetPtrMember() == nullptr);

	return ptr.GetPtrMember();
}

////////////////////////////////////////////////////////////////////////////////
//! Query the object for a new interface.

template<typename I>
HRESULT QueryInterface(IUnknown* object, I** iface)
{
	ASSERT(object != nullptr);
	ASSERT(iface != nullptr);

	return object->QueryInterface(IFaceTraits<I>::uuidof(), reinterpret_cast<void**>(iface));
}

////////////////////////////////////////////////////////////////////////////////
//! Query the object for a new interface.

template<typename O, typename I>
HRESULT QueryInterface(IFacePtr<O>& object, IFacePtr<I>& iface)
{
	return QueryInterface<I>(object.get(), AttachTo(iface));
}

//namespace WCL
}

#endif // WCL_IFACEPTR_HPP
