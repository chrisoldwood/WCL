////////////////////////////////////////////////////////////////////////////////
//! \file   ResourceString.cpp
//! \brief  Utility functions for handling strings in module resources.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ResourceString.hpp"
#include <Core/NotImplException.hpp>
#include <WCL/Module.hpp>
#include <Core/ArrayPtr.hpp>

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Load a string from the specified module.

tstring loadString(HMODULE module, uint resourceId)
{
	typedef Core::ArrayPtr<tchar> BufferPtr;
	
	const size_t DEFAULT_LENGTH = 256;

	size_t    length = DEFAULT_LENGTH;
	BufferPtr buffer(new tchar[length+1]);

	for (;;)
	{
		const int bufsize = length+1;
		const int copied  = ::LoadString(module, resourceId, buffer.get(), bufsize);

		if (copied == 0)
			return TXT("");

		if (static_cast<size_t>(copied) != length)
			return buffer.get();

		length *= 2;
		buffer.reset(new tchar[length+1]);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Load a string from the application module resources.

tstring loadString(uint resourceId)
{
	HMODULE module = CModule::This().Handle();

	return loadString(module, resourceId);
}

//namespace WCL
}
