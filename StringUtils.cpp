////////////////////////////////////////////////////////////////////////////////
//! \file   StringUtils.cpp
//! \brief  String utility functions for Windows specific types.
//! \author Chris Oldwood

#include "Common.hpp"
#include "StringUtils.hpp"
#include <Core/Tokeniser.hpp>
#include <Core/ParseException.hpp>
#include "Rect.hpp"

namespace WCL
{

//namespace WCL
}

namespace Core
{

////////////////////////////////////////////////////////////////////////////////
//! Format a rectangle into a string.

template<>
tstring format(const CRect& value)
{
	return Core::fmt(TXT("%ld,%ld,%ld,%ld"), value.left, value.top, value.right, value.bottom);
}

////////////////////////////////////////////////////////////////////////////////
//! Parse a rectangle from a string.

template<>
CRect parse(const tstring& buffer)
{
	Core::Tokeniser::Tokens tokens;

	if (Core::Tokeniser::split(buffer, TXT(","), tokens) != 4)
		throw Core::ParseException(Core::fmt(TXT("Failed to parse the rectangle: '%s'"), buffer.c_str()));

	int left   = Core::parse<int>(tokens[0]);
	int top    = Core::parse<int>(tokens[1]);
	int right  = Core::parse<int>(tokens[2]);
	int bottom = Core::parse<int>(tokens[3]);

	return CRect(left, top, right, bottom);
}

//namespace Core
}
