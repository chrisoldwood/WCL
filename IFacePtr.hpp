////////////////////////////////////////////////////////////////////////////////
//! \file   IFacePtr.hpp
//! \brief  The IFacePtr class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef CORE_IFACEPTR_HPP
#define CORE_IFACEPTR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace Core
{

// Forward declarations.
template <typename T>
class IFacePtr;

template <typename T>
T** AttachTo(IFacePtr<T>& ptr);

////////////////////////////////////////////////////////////////////////////////
//! A smart-pointer type for use with COM interfaces. This class can only be
//! used to manage the lifetime of COM interfaces, to create COM objects use
//! the ComPtr<T> class in the Windows C++ Library.

template <typename T>
class IFacePtr : public SmartPtr<T>
{
public:
	//! Default constructor.
	IFacePtr();

	//! Construction from an existing interface pointer.
	explicit IFacePtr(T* pInterface, bool bAddRef = false);

	//! Copy constructor.
	IFacePtr(const IFacePtr<T>& oPtr);

	//! Destructor.
	~IFacePtr();

	//
	// Operators.
	//

	//! Assignment operator.
	IFacePtr& operator=(const IFacePtr<T>& oPtr);

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
	: SmartPtr<T>(pInterface)
{
	if (bAddRef)
	{
		ASSERT(m_pPointer != nullptr);

		m_pPointer->AddRef();
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Copy constructor.

template <typename T>
inline IFacePtr<T>::IFacePtr(const IFacePtr<T>& oPtr)
	: SmartPtr<T>(oPtr.m_pPointer)
{
	if (m_pPointer != nullptr)
		m_pPointer->AddRef();
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
inline IFacePtr<T>& IFacePtr<T>::operator=(const IFacePtr<T>& oPtr)
{
	// Check for self-assignment.
	if ( (this != &oPtr) && (this->m_pPointer != oPtr.m_pPointer) )
	{
		Release();

		m_pPointer = oPtr.m_pPointer;

		if (m_pPointer != nullptr)
			m_pPointer->AddRef();
	}

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//! Release the interface.

template <typename T>
inline void IFacePtr<T>::Release()
{
	if (m_pPointer != nullptr)
	{
		m_pPointer->Release();
		m_pPointer = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Take ownership of the interface.

template <typename T>
inline T* IFacePtr<T>::Detach()
{
	T* pPointer = m_pPointer;
	m_pPointer = nullptr;

	return pPointer;
}

////////////////////////////////////////////////////////////////////////////////
//! Access the underlying pointer member. This is used by the AttachTo() friend
//! function to access the underlying SmartPtr<T> member variable.

template <typename T>
inline T** IFacePtr<T>::GetPtrMember()
{
	return &m_pPointer;
}

////////////////////////////////////////////////////////////////////////////////
//! Helper function to gain access to the internal member so that it can be
//! passed as an output parameter, without overloading the & operator.
//! e.g. LoadTypeLib(..., AttachTo(p)).

template <typename T>
inline T** AttachTo(IFacePtr<T>& ptr)
{
	return ptr.GetPtrMember();
}

//namespace Core
}

#endif // CORE_IFACEPTR_HPP
