////////////////////////////////////////////////////////////////////////////////
//

#include "stdafx.h"
#include <tchar.h>
#include <WCL/SeTranslator.hpp>
#include <WCL/StructuredException.hpp>

////////////////////////////////////////////////////////////////////////////////
//

void TestStructuredException()
{
	WCL::SeTranslator oSeTranslator;

	try
	{
		char* p = nullptr;

		*p = '\0';
	}
	catch (const WCL::StructuredException& e)
	{
		std::tcout << e.what() << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////////////
//

void TestString()
{
	std::tcout << CString::Fmt("%s", "Hello World") << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
//	TestStructuredException();

	TestString();
	
	return EXIT_SUCCESS;
}
