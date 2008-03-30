////////////////////////////////////////////////////////////////////////////////
//! \file   PtrTest.hpp
//! \brief  The classes used in unit testing of the smart pointer classes..
//! \author Chris Oldwood

////////////////////////////////////////////////////////////////////////////////
//! The test interface.

class IPtrTest
{
public:
	virtual ulong AddRef() = 0;
	virtual ulong Release() = 0;
	virtual void  Run() = 0;
};

////////////////////////////////////////////////////////////////////////////////
//! The test concrete class.

class PtrTest : public IPtrTest
{
public:
	PtrTest()
		: m_nRefCount(1)
	{ }

	virtual ulong AddRef()
	{
		return ++m_nRefCount;
	}

	virtual ulong Release()
	{
		if (--m_nRefCount == 0)
			delete this;
		return m_nRefCount;
	}

	virtual void Run()
	{ }

	ulong m_nRefCount;
};

////////////////////////////////////////////////////////////////////////////////
//! The test derived concrete class.

class Derived : public PtrTest
{
};

////////////////////////////////////////////////////////////////////////////////
//! The test unrelated concrete class.

class Unrelated
{
};
